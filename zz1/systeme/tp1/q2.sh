#!/bin/sh

echo "affichage di fichier complet"
cat tel.dat
echo "affichage des noms seulement"
cat tel.dat | cut -d ";" -f 1 | cut -d " " -f 2
