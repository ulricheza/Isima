#!/bin/bash

#Maxime Escourbiac 
#tp 1 d'initiation unix

echo "hostname ==>"
hostname
#--------------------

echo "pwd ===>"
pwd
#--------------------
echo "whoami ===>"
whoami
#--------------------
echo "date===>"
date
#--------------------
echo "ls -a"
ls -a
#--------------------
echo "ls -l"
ls -l
#--------------------
echo "le repertoire unix1 va etre cree"
mkdir unix1
#--------------------
echo "un fichier lambda va etre cree dans unix1"
touch ./unix1/lambda 
#--------------------
echo "on rajoute du contenu dans lambda"
echo "101010010000011111110000010001010110" >> ./unix1/lambda
#--------------------
echo "on affiche le contenu de lambda"
cat ./unix1/lambda
#--------------------
echo "on va copier lambda dans le dossier principal du tp"
cp ./unix1/lambda ./
#--------------------
echo "verification"
ls
#--------------------
echo "on supprime le dossier unix1"
rm -r unix1
#--------------------
echo "on verifie"
ls -i -a -l
#--------------------
echo "on supprime lambda"
rm lambda
#--------------------
echo "on verifie"
ls -i -a -l
