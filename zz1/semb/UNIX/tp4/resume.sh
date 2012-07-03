#!/bin/bash

i=0
while [ $i -le 10 ]
do 
   i=$(($i + 1))
   echo "i = $i"
done


#------------------
i= 0
while [ $i -lt 10 ] do 
   i= $i + 1
   echo "$i"
done

#------------------

lpr -P i102pc1 $1   #a changer en fonction de la salle 

#le spammeur pour mail, pour des raisons pratiques on utilisera la commande echo 

for i in `cat Listedenom`
   do
      echo "mail -s \"Votre sujet de TP\" $i < FichierSujetTP"
      echo sleep 1
   done


