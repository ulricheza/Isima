#!/bin/sh

#ajout de ligne a partir de fichier temporaire

TMP="toto.$$"

echo "rentrer une addresse valable"
read LIGNE

while [ ! "$LIGNE" = "" ]
do
   echo "$LIGNE" >> $TMP
   read LIGNE
done

cat $TMP >> tel.dat
rm $TMP
