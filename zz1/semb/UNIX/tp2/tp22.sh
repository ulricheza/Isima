#tp2 d'initiation a UNIX

#Maxime Escourbiac
#15/10/2009

#redirection input-output


echo "redirection sur le fichier toto de la commande ls"
ls >> toto
cat toto
#---------------------------
echo " utilisation de >>"
pwd > toto
cat toto
#---------------------------
echo " utilisation de ls comme fonction de recherche"
ls toto titi
echo " on redirige la sortie d'erreurs vers erreurs.txt"
ls toto titi 2> erreurs.txt
cat erreurs.txt
#---------------------------
echo " creation d'un fichier entree "
echo "coucou" >> entree
echo "les" >> entree
echo "zz1" >> entree
grep coucou < entree

rm erreurs.txt
rm toto
rm entree