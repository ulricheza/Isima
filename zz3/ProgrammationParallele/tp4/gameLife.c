/*
 * @author  : Daniel PETISME
 * @file    : gameLife.c
 * @version : 1.0
 * @brief   : the aim of this project is to parallelize the Conway's
 *            Game of life
 */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

//The End label
#define END 1234

typedef enum {EMPTY, ALIVE, DEAD, STATES_NUMBER} cell_state_t;
/* Algorithme :
 *
 * Initialisation de la matrice
 *
 * Tant que !Fin faire
 *    Pour chaque cellule faire
 *       On envoi a un esclave la matrice 3x3 centre sur la cellule
 *       L'esclave fait evoluer la cellule
 *       L'esclave envoi la nouvel etat de la cellule
 *    Fin
 *
 *    Le maitre compare l'ancienne matrice et la nouvelle et determine la fin
 *    de l'algo
 *
 *    Le maitre met a jour la matrice si necessaire
 *Fin
 */

/**
 * @fn display a vector
 *
 * @param inVector the vector to display
 * @param inSize the vector's size
 */
void printVector(int * inVector, int inSize) {
	int i;

	printf("[");
	for (i = 0; i < inSize; i++) {
      char currentState;

      switch(inVector[i]){
         case EMPTY:
            currentState = '.';
         break;
         case ALIVE:
            currentState = 'o';
         break;
         case DEAD:
            currentState = 'x';
         break;
      }

      printf("%c", currentState);
		if ((i + 1) != inSize) {
			printf(" ");
		}
	}

	printf("]\n");
}

/**
 * @fn display a matrix
 *
 * @param inMatrix the matrix to display
 * @param inSize the matrix's size
 */
void printMatrix(int ** inMatrix, int inSize) {

	int i, j;
	for (i = 0; i < inSize; i++) {
		printVector(inMatrix[i], inSize);

	}
}

/**
 * @fn generate a state for a cell
 *
 * @return a state between EMPTY, ALIVE
 */

cell_state_t generateRandomState(){

   return rand()% STATES_NUMBER;
}

void initWorld(int ** inWorld, int inSize){

   int i, j;

   for(i = 0; i < inSize; i++){
      for(j = 0; j < inSize; j++){
         inWorld[i][j] = generateRandomState();
      }
   }

}

/**
 * @fn memory allocation for a vector
 *
 * @param inVectorSize the size wanted of the vector
 *
 * @return the pointer to the memory area
 */
int * initVector(int inVectorSize) {

	int * vector;

	vector = NULL;
	if (inVectorSize > 0) {
		vector = (int *) malloc(inVectorSize * sizeof(int));
	}

	if (vector == NULL) {
		printf("Vector allocation problem - initVector");
		exit(0);
	}
	return vector;
}


/**
 * @fn memory allocation for a matrix
 *
 * @param inSize the matrix size
 *
 * @return the pointer to the memory area
 */
int ** initMatrix(int inSize) {

   int    i,j;
	int ** matrix;

	matrix = NULL;

	if (inSize > 0 && inSize > 0) {
		matrix = (int**) malloc(inSize * sizeof(int *));
		if (matrix != NULL) {
			int i;

			for (i = 0; i < inSize; i++) {
				matrix[i] = initVector(inSize);
			}
		}
	}

	if (matrix == NULL) {
		printf("Matrix allocation problem - initMatrix");
		exit(0);
	}else{

      for(i = 0; i < inSize; i++){
            for(j = 0; j < inSize; j++){
               matrix[i][j] = 0;
         }
      }
   }

	return matrix;
}


/**
 * @fn test if the world is stable
 *
 * @param inOldWorld the old world
 * @param inNewWorld the new computed world
 * @param inSize the world's size
 *
 * @return 1 if the world is stable else 0
 */

int isStable(int ** inOldWorld, int ** inNewWorld, int inSize){

   int i,j;
   int stable = 1;

   for(i = 0; i < inSize; ++i){
      for(j = 0; j < inSize; j++){

         if(inOldWorld[i][j] != inNewWorld[i][j]){
            stable = 0;
            break;
         }
      }
   }

   return stable;

}

cell_state_t nextState(cell_state_t inCurrentState, int * inNeiborhood, int inSize){

   int i, j;
   int emptyCells, aliveCells, deadCells;

   cell_state_t nextCellState = inCurrentState;

   emptyCells = aliveCells = deadCells = 0;

   for(i = 0; i < inSize; i++){
         switch(inNeiborhood[i]){
            case EMPTY:
               emptyCells++;
            break;
            case ALIVE:
               aliveCells++;
            break;
            case DEAD:
               deadCells++;
            break;
      }
   }

   if(inCurrentState == EMPTY && aliveCells == 3){
      nextCellState = ALIVE;
   }
   else if(inCurrentState == ALIVE){

    if(aliveCells == 2 || aliveCells == 3){
      nextCellState = ALIVE;
    }
    else if(aliveCells < 2){
      nextCellState = DEAD;
    }
    else if(aliveCells > 3){
      nextCellState = DEAD;
    }
   }

   return nextCellState;

}

/**
 * @fn executed by the master process
 *
 * @param inNbSlaves how many slaves, the master manage
 * @param inLabel the master-slaves shared label to communicate
 *
 * @brief The master :
 *  -init the world
 *  -while the world is not stable
 *  -for each cell in the world
 *  -split the world in 3x3 sub-matrixes with the current cell in the center
 *  -send the sub matrix to slaves
 *  -gather the results
 */
void master(int inNbSlaves, int inLabel) {

   int    i, j;
   int    top, left, down, right;
   int    worldSize;
   int    cptSlaves;
  	int    nbTotalCells;
	int    nbDistributedCells;
   int    nbCellsWaiting;
   int    neibordhoodSize;
   int *  mappingSlavesCells;
   int *  neibordhood;
   int ** oldWorld;
   int ** newWorld;
   int ** tmp;


   /*Init*/
   neibordhoodSize = 8;
   worldSize = 10;
   nbTotalCells = worldSize * worldSize;
   nbDistributedCells = 0;
   nbCellsWaiting = 0;

   oldWorld = initMatrix(worldSize);
   newWorld = initMatrix(worldSize);
   neibordhood = initVector(neibordhoodSize);
   mappingSlavesCells = initVector(inNbSlaves);

   initWorld(oldWorld, worldSize);
   printMatrix(oldWorld, worldSize);

   //Sending the subMatrix size
   MPI_Bcast(&neibordhoodSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

   while(!isStable(oldWorld, newWorld, worldSize)){
      i = 0;
      j = 0;

      //Spliting the world
      for(cptSlaves = 1; cptSlaves < inNbSlaves; cptSlaves++)
      {
            top = i - 1;
            down = i + 1;
            left = j - 1;
            right = j + 1;
             if(i == 0){
               top = worldSize - 1;
             }
             if(i == worldSize - 1){
                down = 0;
             }
             if(j == 0)
             {
               left = worldSize - 1;
             }
             if(j == worldSize - 1){
                right = 0;
             }

               neibordhood[0] = oldWorld[top][left];
               neibordhood[1] = oldWorld[top][j];
               neibordhood[2] = oldWorld[top][right];
               neibordhood[3] = oldWorld[i][left];
               neibordhood[4] = oldWorld[i][right];
               neibordhood[5] = oldWorld[down][left];
               neibordhood[6] = oldWorld[down][j];
               neibordhood[7] = oldWorld[down][right];

               MPI_Send(&oldWorld[i][j], 1, MPI_INT, cptSlaves, inLabel, MPI_COMM_WORLD);
               MPI_Send(neibordhood, neibordhoodSize, MPI_INT, cptSlaves, inLabel, MPI_COMM_WORLD);

               mappingSlavesCells[i] =  i * worldSize + j;

               i++;
               if(i % worldSize == 0){
                  i = 0;
                  j++;
               }

               nbDistributedCells++;
         }

         /* -- Waiting for results -- */
         nbCellsWaiting = nbDistributedCells;

         while (nbCellsWaiting > 0) {
            cell_state_t state;
            MPI_Status status;
            int slave;
            int i, j;
            int index;

            MPI_Recv(&state, 1, MPI_INT, MPI_ANY_SOURCE, inLabel,
               MPI_COMM_WORLD, &status);

            slave = status.MPI_SOURCE;
            index = mappingSlavesCells[slave];
            i = index / worldSize;
            j = index % worldSize;

            newWorld[i][j] = state;

            /* -- Try to distribute a new Cell -- */
         if (nbDistributedCells < nbTotalCells) {
               top = i - 1;
               down = i + 1;
               left = j - 1;
               right = j + 1;
                if(i == 0){
                  top = worldSize - 1;
                }
                if(i == worldSize - 1){
                   down = 0;
                }
                if(j == 0)
                {
                  left = worldSize - 1;
                }
                if(j == worldSize - 1){
                   right = 0;
                }

                  neibordhood[0] = oldWorld[top][left];
                  neibordhood[1] = oldWorld[top][j];
                  neibordhood[2] = oldWorld[top][right];
                  neibordhood[3] = oldWorld[i][left];
                  neibordhood[4] = oldWorld[i][right];
                  neibordhood[5] = oldWorld[down][left];
                  neibordhood[6] = oldWorld[down][j];
                  neibordhood[7] = oldWorld[down][right];

                  MPI_Send(&oldWorld[i][j], 1, MPI_INT, slave, inLabel, MPI_COMM_WORLD);
                  MPI_Send(neibordhood, neibordhoodSize, MPI_INT, slave, inLabel, MPI_COMM_WORLD);

                  mappingSlavesCells[i] =  i * worldSize + j;

                  i++;
                  if(i % worldSize == 0){
                     i = 0;
                     j++;
                  }

                  nbDistributedCells++;
                  nbCellsWaiting++;
         }
         else{
            MPI_Send(neibordhood, neibordhoodSize, MPI_INT, slave, END, MPI_COMM_WORLD);
         }
      }

      tmp = oldWorld;
      oldWorld = newWorld;
      newWorld = tmp;
   }



   /*Cleaning*/
   for (i = 0; i < worldSize; i++) {
		free(oldWorld[i]);
	}
	free(oldWorld);

   for (i = 0; i < worldSize; i++) {
		free(newWorld[i]);
	}
	free(newWorld);

   free(mappingSlavesCells);
   free(neibordhood);
}

/**
 * @fn executed by the slaves processes
 *
 * @param inMyRank the slave Id
 * @param inLabel the master-slaves shared label to communicate
 *
 * @brief The slave :
 * -Receive a 3x3 matrix
 * -compute the next cell state
 * -send back the result to the master
 */
void slave(int inMyRank, int inLabel) {

   int            neibordhoodSize;
   int          * neibordhood;
   cell_state_t   state;
   MPI_Status     status;


   //Receive the neihbordhood size of each cell
   MPI_Bcast(&neibordhoodSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
   neibordhood = initVector(neibordhoodSize);

   //Receive the current state
   MPI_Recv(&state, 1, MPI_INT, 0, inLabel, MPI_COMM_WORLD, &status);
   //Receive a subMatrix
   MPI_Recv(neibordhood, neibordhoodSize, MPI_INT, 0, inLabel, MPI_COMM_WORLD, &status);
printf("neibordhood\n", neibordhoodSize);

   //if is not the END label
	while (status.MPI_TAG != END) {
      state = nextState(state, neibordhood, neibordhoodSize);

      //Send the computed result
		MPI_Send(&state, 1, MPI_INT, 0, inLabel, MPI_COMM_WORLD);

      //Get a new cell
      MPI_Recv(neibordhood, neibordhoodSize, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD,
				&status);
   }

   free(neibordhood);
}

int main (int argc, char ** argv){

/**
	 * MPI Variables
	 */
	int rank, size;
	int label = 666;

   /**
	 * MPI INIT
	 */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

   if (rank == 0) {
		/**
		 * Master
		 */
		master(size, label);

	} else {
      /**
		 * Slave
		 */
		slave(rank, label);
	}

   return 0;
}
