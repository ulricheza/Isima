#makefile pour tout les compilateurs

#compilateur
CC = gcc
#options de compilation
OPT = -Wall -ansi -pedantic
#liste des fichiers objets 
OBJ = garbage.o agenda.o
#regle de production finale tp:
gest_agenda : $(OBJ)
	$(CC) $(OBJ) -o gest_agenda
#regle de production de chaque fichier
garbage.o : garbage.h
	$(CC) -c garbage.c $(OPT)
agenda.o : agenda.h
	$(CC) -c agenda.c $(OPT)
clean : 
	rm *.o 

