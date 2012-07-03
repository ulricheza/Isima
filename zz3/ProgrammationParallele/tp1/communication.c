#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
	int rang, taille, dest=0, source, etiquette = 1, N = 4;
	MPI_Status statut;
	float tab[4] = {2.,4.,16.,25.};
	float rep;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	MPI_Comm_size(MPI_COMM_WORLD, &taille);
	if(rang == 0 )
	{
                for(dest = 0; dest < N ; ++dest)
		{
			MPI_Send ( &(tab[dest]), sizeof(float), MPI_FLOAT, dest+1, etiquette, MPI_COMM_WORLD );
		}
		for(dest = 0; dest < N ; ++dest)
		{
			MPI_Recv ( &(tab[dest]), sizeof(float) , MPI_FLOAT, dest+1, etiquette, MPI_COMM_WORLD, &statut );
		}

                printf("Tab[0] : %f \nTab[1] : %f \nTab[2] : %f \nTab[3] : %f \n",tab[0],tab[1],tab[2],tab[3]);
		
	}
	else
	{
		MPI_Recv ( &rep, sizeof(float), MPI_FLOAT, 0, etiquette, MPI_COMM_WORLD, &statut );
		rep = sqrt(rep);
		MPI_Send ( &rep, sizeof(float), MPI_FLOAT, 0, etiquette, MPI_COMM_WORLD );
	}

	MPI_Finalize();
	return 0;
}