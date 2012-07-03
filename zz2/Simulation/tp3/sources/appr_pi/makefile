#!makefile

OPT = -Wall -ansi -pedantic -lm


calcul_pi:mt19937ar.o appr_pi.o
	gcc mt19937ar.o appr_pi.o -o calcul_pi $(OPT)
	
mt19937ar.o:mt19937ar.c
	gcc -c mt19937ar.c $(OPT)

appr_pi.o:appr_pi.c
	gcc -c appr_pi.c $(OPT)
	
clean:
	rm *.o
