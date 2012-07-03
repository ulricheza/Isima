#!makefile

OPT = -Wall -ansi -pedantic -lm -lpthread

all:flou


flou:flou.o imaio.o erreur.o
	gcc flou.o imaio.o erreur.o -o flou $(OPT)

flou.o:flou.c
	gcc -c flou.c $(OPT)
	
imaio.o:imaio.c
	gcc -c imaio.c $(OPT)

erreur.o:erreur.c
	gcc -c erreur.c $(OPT)

clean:
	rm *.o
	
