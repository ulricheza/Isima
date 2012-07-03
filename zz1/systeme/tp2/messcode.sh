#!/bin/sh

#programme d'ecriture de message

read MESS

while [ ! -z "$MESS" ]
   do
      echo "`cat $HOME/pseudo.cat ` a ecrit le `date`"  >> /tmp/conv.cat
      echo "$MESS"| tr 'a-e' '0-5' >> /tmp/conv.cat
      read MESS
   done