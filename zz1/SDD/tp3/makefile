#makefile pour tout les compilateurs

#compilateur
CC = gcc
#options de compilation
OPT = -Wall -ansi -pedantic -g
#liste des fichiers objets 
OBJ = pile.o tp3.o
#regle de production finale tp:
tp3 : $(OBJ)
	$(CC) $(OBJ) -o tp3
#regle de production de chaque fichier
pile.o : pile.h
	$(CC) -c pile.c $(OPT)
tp3.o : tp3.h
	$(CC) -c tp3.c $(OPT)
clean : 
	rm *.o 

