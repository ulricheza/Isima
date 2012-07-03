#tp2 d'initiation a UNIX

#Maxime Escourbiac
#15/10/2009

#modification des droits d'accées

echo "modification des droits d'acces du dossier principal"
cd $HOME
cd ..
chmod a+rwx escourbi
echo "verification"
ls -l | grep escourbi
#---------------------
echo " creation d'un fichier et donne les droit de lecture au groupe"
cd $HOME
touch toto1
chmod g+r toto1
echo "verification"
ls -l | grep toto1
#--------------------
echo "suppresion de toto1 et remise de la sécurité sur le repertoire principal"
rm toto1
cd ..
chmod go-rwx escourbi
echo "verification"
ls -l | grep escourbi

