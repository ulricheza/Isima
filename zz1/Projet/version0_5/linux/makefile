#makefile pour tout les compilateurs

#compilateur
CC = gcc
#options de compilation
OPT = -lpthread 
#liste des fichiers objets
OBJ = core.o jeu2p.o network.o
#regle de production finale tp:
battle_navy : $(OBJ)
	$(CC) $(OBJ) -o battle_navy $(OPT)
#regle de production de chaque fichier
core.o : core.h
	$(CC) -c core.c $(OPT)
network.o : network.h
	$(CC) -c network.c $(OPT)
jeu2p.o : jeu2p.h
	$(CC) -c jeu2p.c $(OPT)
clean : 
	rm *.o

