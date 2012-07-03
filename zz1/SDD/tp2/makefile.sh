gcc -c file.c -Wall -ansi -pedantic
gcc -c pile.c -Wall -ansi -pedantic
gcc -c pilefile.c -Wall -ansi -pedantic
gcc file.o pile.o pilefile.o -o tp2 -Wall -ansi -pedantic
rm *.o
rm *~