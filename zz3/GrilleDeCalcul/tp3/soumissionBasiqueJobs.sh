#! /bin/sh

echo "------Nom Pc------------------"
hostname

echo "------Info Processeur---------"
cat /proc/cpuinfo

echo "------Info Memoire------------"
cat /proc/meminfo

echo "------Repertoire courant------"
ls

echo "------Processus---------------"
ps aux

