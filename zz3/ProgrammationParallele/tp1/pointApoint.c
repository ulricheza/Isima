#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	int rang, taille, dest=0, source, etiquette = 50;
	MPI_Status statut;
	char message[100];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	MPI_Comm_size(MPI_COMM_WORLD, &taille);
	if(rang != 0 )
	{
		sprintf( message, "Bonjour de la part de %d!" , rang );
		MPI_Send ( message, strlen(message) + 1, MPI_CHAR, dest, etiquette, MPI_COMM_WORLD );
	}
	else
	{
		for ( source = 1; source < taille ; source++ )
		{
			MPI_Recv ( message, 100 , MPI_CHAR, source, etiquette, MPI_COMM_WORLD, &statut );
			printf("%s\n", message );
		}
	}

	MPI_Finalize();
	return 0;
}