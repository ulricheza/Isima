#makefile pour tout les compilateurs

#compilateur
CC = g++
#options de compilation
OPT = -lpthread -lSDLmain -lSDL -lfmod -lSDL_image -O2
#liste des fichiers objets
OBJ = core.o
#regle de production finale tp:
simu_sma : $(OBJ)
	$(CC) *.o -o simu_sma $(OPT)
#regle de production de chaque fichier
core.o : 
	$(CC) -c *.cpp
clean : 
	rm *.o

