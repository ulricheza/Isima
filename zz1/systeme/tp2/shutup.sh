#/bin/sh

#coupe l'ecoute du fichier /tmp/conv.cat

kill -9 `ps aux | grep $USER | grep "tail" |grep -v "grep" | cut -c 8-15`


#erase du fichier online.cat

rm $HOME/online.cat