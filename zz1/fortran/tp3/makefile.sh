gfortran -c fonction.f90
gfortran -c methodeqr.f90
gfortran -c tp3pp.f90
gfortran fonction.o methodeqr.o tp3pp.o -o tp3
rm *.mod
rm *.o

