#!/bin/bash

#le spammeur pour mail, pour des raisons pratiques on utilisera la commande echo 

for i in `cat Listedenom`
   do
      echo "mail -s \"Votre sujet de TP\" $i < FichierSujetTP"
      echo sleep 1
   done


