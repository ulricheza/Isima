gfortran -c fct.f90
gfortran -c fonction.f90
gfortran -c gc.f90
gfortran -c tp4pp.f90
gfortran fct.o fonction.o gc.o tp4pp.o -o tp4
rm *.o
rm *.mod

