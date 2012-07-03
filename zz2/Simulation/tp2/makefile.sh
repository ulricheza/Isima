gcc -c fonction.c -lm
gcc -c tp2.c -Wall -pedantic -ansi -lSDL
gcc fonction.o tp2.o -o tp2 -lm -lSDL
rm *.o 
rm *~