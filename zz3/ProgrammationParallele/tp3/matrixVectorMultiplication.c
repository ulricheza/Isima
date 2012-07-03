/*
 * @author  : Daniel PETISME
 * @file    : matrixVectorMultiplication.c
 * @version : 1.0
 * @brief   : the aim of this project is to parallelize a matrix-vector
 *            multiplication computation using the MPI C library
 */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

//The End label
#define END 1234

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
		printf("%d", inVector[i]);
		if ((i + 1) != inSize) {
			printf(", ");
		}
	}

	printf("]\n");
}

/**
 * @fn display a matrix
 *
 * @param inMatrix the matrix to display
 * @param inNbRow the matrix's number of rows
 * @param inNbRow the matrix's number of columns
 */
void printMatrix(int ** inMatrix, int inNbRow, int inNbColumn) {

	int i, j;
	for (i = 0; i < inNbRow; i++) {
		printVector(inMatrix[i], inNbColumn);

	}
}

/**
 * @fn compute the scalar product between to vectors
 *
 * @param inVectorRow the row vector
 * @param inVectorColumn the column vector
 * @param inSize the row and column vectors sizes
 *
 * @return the computation result
 */
int scalarProduct(int * inVectorRow, int * inVectorColumn, int inSize) {

	int i;
	int product = 0;

	for (i = 0; i < inSize; i++) {
		product += inVectorRow[i] * inVectorColumn[i];
	}

	return product;
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
 * @param inNbRows the matrix number of lines
 * @param inNbColumns the matrix number of columns
 *
 * @return the pointer to the memory area
 */
int ** initMatrix(int inNbRows, int inNbColumns) {
	int ** matrix;

	matrix = NULL;

	if (inNbRows > 0 && inNbColumns > 0) {
		matrix = (int**) malloc(inNbRows * sizeof(int *));
		if (matrix != NULL) {
			int i;

			for (i = 0; i < inNbRows; i++) {
				matrix[i] = initVector(inNbColumns);
			}
		}
	}

	if (matrix == NULL) {
		printf("Matrix allocation problem - initMatrix");
		exit(0);
	}

	return matrix;
}
/**
 * @fn executed by the master process
 *
 * @param inNbSlaves how many slaves, the master manage
 * @param inLabel the master-slaves shared label to communicate
 *
 * @brief The master :
 *  -init the matrix and the vector
 *  -broadcast the vector
 *  -distribute a line to each slave
 *  -Then it's waiting for results
 *  	-each time it receives a new result it tries to distribute a new row
 *			-if no more rows are availables, it sends the END label
 *			-else it sends a new row
 */
void master(int inNbSlaves, int inLabel) {

	int i, j;
	int cpt;
	int nbTotalRows;
	int nbDistributedRows;
	int nbRowsWaiting;
	int vectorSize;
	int * mappingSlavesRows;
	int * vector;
	int * result;
	int ** matrix;

	/* -- Init -- */
	mappingSlavesRows = initVector(inNbSlaves);

	//The vector
	vectorSize = 10;
	vector = initVector(vectorSize);
	//Fill the vector

	cpt = 10;
	for (i = 0; i < 10; i++) {
		vector[i] = cpt++;
	}
	printf("The vector : \n");
	printVector(vector, vectorSize);

	result = initVector(vectorSize);

	//The matrix
	nbTotalRows = 10;
	matrix = initMatrix(nbTotalRows, vectorSize);
	//Fill the matrix
	cpt = 1;
	for (i = 0; i < nbTotalRows; i++) {
		for (j = 0; j < vectorSize; j++) {
			matrix[i][j] = cpt++;
		}
	}

	printf("The matrix : \n");
	printMatrix(matrix, nbTotalRows, vectorSize);

	/* -- Broadcast the vector -- */
	//Send the vector to all the slaves and its size
	MPI_Bcast(&vectorSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(vector, vectorSize, MPI_INT, 0, MPI_COMM_WORLD);

	/* -- distribute a line to each slave --*/
	nbDistributedRows = 0;
	//Send the first lines of the Matrix
	for (i = 1; i < inNbSlaves; i++) {
		printf("I will send this row to the slave %d\n", i);
		printVector(matrix[i - 1], vectorSize);
		MPI_Send(matrix[i - 1], vectorSize, MPI_INT, i, inLabel, MPI_COMM_WORLD);
		nbDistributedRows++;

		//We map the slave with its row parameter
		mappingSlavesRows[i] = i - 1;
	}

	/* -- Waiting for results -- */
	nbRowsWaiting = nbDistributedRows;

	while (nbRowsWaiting > 0) {
		int resultFragment;
		MPI_Status status;
		int slave;

		printf("Progress : %d/%d, Waiting : %d\n", nbDistributedRows,
				nbTotalRows, nbRowsWaiting);

		MPI_Recv(&resultFragment, 1, MPI_INT, MPI_ANY_SOURCE, inLabel,
				MPI_COMM_WORLD, &status);
		slave = status.MPI_SOURCE;
		printf("I've received the resul %d from slave#%d\n", resultFragment,
				slave);

		//mappingSlavesRows[slave] gives the row computed by this slave
		result[mappingSlavesRows[slave]] = resultFragment;

		//decrement the total line waiting
		nbRowsWaiting--;

		/* -- Try to distribute a new row -- */
		if (nbDistributedRows < nbTotalRows) {
			MPI_Send(matrix[nbDistributedRows], vectorSize, MPI_INT, slave,
					inLabel, MPI_COMM_WORLD);

			printf("I will send this row to the slave %d\n", slave);
			printVector(matrix[nbDistributedRows], vectorSize);

			mappingSlavesRows[slave] = nbDistributedRows;
			nbDistributedRows++;
			nbRowsWaiting++;
		} else {
			printf("Sorry slave#%d, no more rows to distribute\n", slave);
			MPI_Send(vector, vectorSize, MPI_INT, slave, END, MPI_COMM_WORLD);
		}
	}

	/* -- Printing the result vector -- */
	printf("The result vector is :\n");
	printVector(result, vectorSize);

	//Cleaning
	free(vector);
	free(result);
	free(mappingSlavesRows);

	for (i = 0; i < nbTotalRows; i++) {
		free(matrix[i]);
	}
	free(matrix);

}

/**
 * @fn executed by the slaves processes
 *
 * @param inMyRank the slave Id
 * @param inLabel the master-slaves shared label to communicate
 *
 * @brief The slave :
 * -Receives the vector
 * -Then, it's waiting for matrix's rows
 *  -if is not the END label then
 *  	-computes the scalar product
 *  	-sends the results to the master
 *  -else
 *  	-Game Over
 *
 */
void slave(int inMyRank, int inLabel) {

	int i;
	int product;
	int vectorSize;
	MPI_Status status;
	int * vector;
	int * row;

	//Beginning
	printf("Slave#%d, I'm waiting for the vector\n", inMyRank);

	/* -- Receive the vector -- */
	//Receive the vector and its size
	MPI_Bcast(&vectorSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	vector = initVector(vectorSize);
	row = initVector(vectorSize);

	MPI_Bcast(vector, vectorSize, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Slave#%d, I received the vector : \n", inMyRank);
	printVector(vector, vectorSize);

	/* -- waiting for rows -- */
	//Receive the first row
	MPI_Recv(row, vectorSize, MPI_INT, 0, inLabel, MPI_COMM_WORLD, &status);
	printf("Slave#%d, I received the row : \n", inMyRank);
	printVector(row, vectorSize);

	//if is not the END label
	while (status.MPI_TAG != END) {

		//compute the scalar product
		product = scalarProduct(vector, row, vectorSize);
		printf("Slave#%d, The scalar product is : %d\n", inMyRank, product);

		//Send the computed result
		MPI_Send(&product, 1, MPI_INT, 0, inLabel, MPI_COMM_WORLD);

		//Get the next row
		printf("Slave#%d, I'm waiting for a new line\n", inMyRank);
		MPI_Recv(row, vectorSize, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD,
				&status);
		printf("Slave#%d, I received the row : \n", inMyRank);
		printVector(row, vectorSize);

	}

	//Game  Over
	printf("Slave#%d, I'm done. Bye\n", inMyRank);

	//Cleaning
	free(vector);
	free(row);

}

int main(int argc, char ** argv) {

	/**
	 * MPI Variables
	 */
	int rank, size;
	int label = 666;
	double start, finish;
	MPI_Status status;

	/**
	 * MPI INIT
	 */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Start chrono
	start = MPI_Wtime();

	if (rank == 0) {
		/**
		 * Master
		 */
		master(size, label);

	} else {
		slave(rank, label);
		/**
		 * Slave
		 */

	}

	//Stop chrono
	finish = MPI_Wtime();

	if (rank == 0) {
		printf("Execution time = %f s\n", finish - start);
	}

	MPI_Finalize();

	return 0;
}

