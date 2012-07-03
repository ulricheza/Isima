#!/bin/sh

#test si le fichier pseudo a deja ete cree

if [ -f "$HOME/pseudo.cat" ]
then
   echo "`cat $HOME/pseudo.cat` vient de se connecter" >> /tmp/conv.cat
   touch $HOME/online.cat
   chmod 777 $HOME/online.cat
fi
