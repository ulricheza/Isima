gcc -c calcul.c
gcc -c affich_fonction.c
gcc calcul.o affich_fonction.o -o tp7 -lm -lX11
rm *.o 
rm *~
