#makefile pour tout les compilateurs

#compilateur
CC = gcc
#options de compilation
OPT = -Wall -ansi -pedantic
#liste des fichiers objets 
OBJ = tp62b.o
#regle de production finale tp:
tp62b : $(OBJ)
	$(CC) $(OBJ) -o tp62b
#regle de production de chaque fichier
tp62b.o : entete.h
	$(CC) -c tp62b.c $(OPT) 
