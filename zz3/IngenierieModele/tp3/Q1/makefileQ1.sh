CLHEP_DIR=/home/etud/escourbi/zz3/IngenierieModele/tp3
g++ -o testRandom testRandom.cc -I$CLHEP_DIR/Random/include -L$CLHEP_DIR/Random/lib -lCLHEP-Random-2.1.0.0 -static 
