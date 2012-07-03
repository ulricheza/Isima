#/bin/sh

LISTE=`ls $HOME/../`

for i in $LISTE
do
   if [ -f /home/etud/$i/online.cat ]
   then 
      echo " $i == `cat /home/etud/$i/pseudo.cat`"
   fi

done