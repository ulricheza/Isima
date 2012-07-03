#!/bin/sh

#lecture du nom a rechercher

read nom

#recherhe du nom puis tri puis on enleve les doublons

grep $nom tel.dat | sort | uniq

