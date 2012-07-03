#!/bin/sh


#recherhe du nom passe en argument puis tri puis on enleve les doublons

if [ $# = 1 ]
   then
      grep $1 tel.dat | sort | uniq
   else
      echo "Probleme avec l'argument"
fi

