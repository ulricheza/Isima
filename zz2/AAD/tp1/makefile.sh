g++ -c graphe.c -O3
g++ -c dijkstra.cpp -O3
g++ -c tp1.cpp -O3
g++ dijkstra.o graphe.o  tp1.o -o tp1 -O3
rm *.o
rm *~