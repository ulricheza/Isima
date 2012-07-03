#makefile pour tout les compilateurs

#compilateur
CC = gcc
#options de compilation
OPT = -lpthread -lSDLmain -lSDL -lfmod -lSDL_image -lSDL_ttf -O2
#liste des fichiers objets
OBJ = core.o jeu.o network.o graphisme.o
#regle de production finale tp:
battle_navy : $(OBJ)
	$(CC) $(OBJ) -o battle_navy $(OPT)
#regle de production de chaque fichier
core.o : core.h
	$(CC) -c core.c $(OPT)
network.o : network.h
	$(CC) -c network.c $(OPT)
graphisme.o : graphisme.h
	$(CC) -c graphisme.c $(OPT)
jeu.o : jeu.h
	$(CC) -c jeu.c $(OPT)
clean : 
	rm *.o
	rm *~

