#/bin/sh

#on salue trois gens desire lorsque il se connecte 
# marche si il ya connection multiple

SALUT1=1
SALUT2=1
SALUT3=1
NOM1="saintmar"
NOM2="septier"
NOM3="bernard"
while :
do
   if [ $SALUT1 = 1 ];then
      echo " *******`cat /home/etud/$NOM1/pseudo.cat` tu vas bien?*********" >> /tmp/conv.cat
   fi
   if [ $SALUT2 = 1 ];then
       echo " *******`cat /home/etud/$NOM2/pseudo.cat` tu vas bien?*********" >> /tmp/conv.cat
   fi
   if [ $SALUT3 = 1 ];then
       echo " *******`cat /home/etud/$NOM3/pseudo.cat` tu vas bien?*********" >> /tmp/conv.cat
   fi
   if [ -f /home/etud/$NOM1/pseudo.cat ]
   then
      SALUT1=0
   else
      SALUT1=1
   fi
   if [ -f /home/etud/$NOM2/pseudo.cat ]
   then
      SALUT2=0
   else
      SALUT2=1
   fi
   if [ -f /home/etud/$NOM3/pseudo.cat ]
   then
      SALUT3=0
   else
      SALUT3=1
   fi
done