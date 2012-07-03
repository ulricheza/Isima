#!/bin/sh

#Maxime Escourbiac
#zz1
#g1
#Question a rendre du TP1

PROG="netscape firefox konqueror"

for i in $PROG
do
   TMP=`ps -aux | grep $i | cut -c 9-15`
   kill -9 $TMP
done
