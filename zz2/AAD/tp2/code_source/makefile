#makefile pour tout les compilateurs

#compilateur
CC = g++
#options de compilation
OPT = -O3
#liste des fichiers objets 
OBJ = instance.o main.o
#regle de production finale tp:
tp2 : $(OBJ)
	$(CC) $(OBJ) -o tp2 -O3
#regle de production de chaque fichier
instance.o : instance.h
	$(CC) -c instance.cpp $(OPT)
main.o : main.h
	$(CC) -c main.cpp $(OPT)
clean : 
	rm *.o 
