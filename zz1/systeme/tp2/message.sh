#!/bin/sh

#programme d'ecriture de message

read MESS

while [ ! -z "$MESS" ]
   do
      echo "`cat $HOME/pseudo.cat` a ecrit le `date`" >> /tmp/conv.cat
      echo "$MESS" >> /tmp/conv.cat
      read MESS
   done