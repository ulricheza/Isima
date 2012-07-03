gfortran -c iteration.f90
gfortran -c fonction.f90
gfortran -c tp2pp.f90
gfortran iteration.o fonction.o tp2pp.o -o tp2
rm *.o
rm *.mod

