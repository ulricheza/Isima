#Maxime Escourbiac
#tp d'initiation a UNIX
# 15/09/2009

echo " les differentes fonctions de grep"

echo " rechercher toutes les lignes qui commence par # dans le fichier stdlib.h"
grep '^#' /usr/include/stdlib.h
echo " rechercher toutes les lignes qui fini par ; dans le fichier stdlib.h"
grep ';$' /usr/include/stdlib.h
echo "recherche des lignes vides"
grep -n '^$' /usr/include/stdlib.h
#------------------------
echo " utilisation du find"
find /home/etud/escourbi/zz1/semb/UNIX/tp2 -name tp22.sh -print
#------------------------
echo "recherche desfichiers dans usr/bin qui contienne au moins caractere qui finisse par r"
ls /usr/bin | grep '....r$'
echo "recherche desfichiers dans usr/bin qui contienne 4 caractere qui finisse par r"
ls /usr/bin | grep '^....r$'
#------------------------
echo " recherche des fichiers commencant par a ou b ou c qui contiennent 4 caracteres et finit par r"
ls /usr/bin | grep '^[abc]...r'
#------------------------
echo " recherche des fichiers où les droit de groupe sont r-x"
ls -l /usr/bin | grep '^.......r-x'
#------------------------
echo " les commandes ps , fg , bg "
ps
nice -14 firefox& /
ps -l

