#!/bin/sh

#creation de la liste des fichiers
LISTE=`ls`

for i in $LISTE
 do
   echo " $i `ls -l | grep $i | cut -d " " -f 1` "
 done

