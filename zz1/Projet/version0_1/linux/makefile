#makefile pour tout les compilateurs

#compilateur
CC = gcc
#options de compilation
OPT = -Wall -ansi -pedantic
#liste des fichiers objets
OBJ = core.o jeu1p.o
#regle de production finale tp:
battle_navy : $(OBJ)
	$(CC) $(OBJ) -o battle_navy
#regle de production de chaque fichier
core.o : core.h
	$(CC) -c core.c $(OPT)
jeu1p.o : jeu1p.h
	$(CC) -c jeu1p.c $(OPT)
clean : 
	rm *.o

