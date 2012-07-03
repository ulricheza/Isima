#!/bin/sh

if [ -f ./menu.txt ] ; then
   rm menu.txt
fi

CARUSR=`echo "$USER" | wc -m`
CARUSR=`expr $CARUSR + 28 `
ESPNAME=""
while [ "$CARUSR" -gt 0 ] ; do
   CARUSR=`expr $CARUSR - 1 `
   ESPNAME="$ESPNAME "
done 

CARPWD=`pwd | wc -m`
CARPWD=`expr 37 - $CARPWD `
ESPPWD=""
while [ "$CARPWD" -gt 0 ] ; do
   CARPWD=`expr $CARPWD - 1 `
   ESPPWD="$ESPPWD "
done 

echo "|------------------------------------------------------------|" >> menu.txt
echo "|      Bonjour: $USER$ESPNAME|" >> menu.txt
echo "| Repertoire par defaut: `pwd`$ESPPWD|" >> menu.txt
echo "|                                                            |" >> menu.txt
if [ ! -f "$HOME/zz1/systeme/tp3/.no_D" ] ; then
   echo "| D) Afficher l'espace disque occupe                         |" >> menu.txt 
fi
if [ ! -f "$HOME/zz1/systeme/tp3/.no_F" ] ; then
   echo "| F) fixer le repertoire par defaut                          |" >> menu.txt
fi
if [ ! -f "$HOME/zz1/systeme/tp3/.no_C" ] ; then
   echo "| C) Creer un repertoire                                     |" >> menu.txt
fi
if [ ! -f "$HOME/zz1/systeme/tp3/.no_E" ] ; then
  echo "| E) Editer un texte                                         |" >> menu.txt
fi
if [ ! -f "$HOME/zz1/systeme/tp3/.no_M" ] ; then
   echo "| M) Envoyer un mail                                         |" >> menu.txt
fi
if [ ! -f "$HOME/zz1/systeme/tp3/.no_S" ] ; then
   echo "| S) Envoyer un fichier par mail                             |" >> menu.txt
fi
echo "| Q) Se deconnecter                                          |" >> menu.txt
echo "| Votre choix (D,F,C,E,M,S,Q) ?                              |" >> menu.txt
echo "-------------------------------------------------------------|" >> menu.txt



MENU="A"

while [ ! "$MENU" = "Q" ] ; do
   cat $HOME/zz1/systeme/tp3/menu.txt
   read MENU
   case "$MENU" in
      D) quota -u
      ;;
      F) echo "chemin du repertoire?"
         read DIR
         cd "$DIR"
         echo " repertoire courant : `pwd`"
      ;;
      C) echo "chemin du repertoire a creer?"
         read DIR
         mkdir "$DIR"
      ;;
      E) echo "chemin du fichier a editer?"
         read DIR
         vi "$DIR"
      ;;
      Q) echo "au revoir"
      ;;
      M) echo "destinataire?"
         read DEST
         echo "sujet?"
         read SUJET
         mail -s "$SUJET" "$DEST"
      ;;
      S) echo "destinataire?"
         read DEST
         echo "sujet?"
         read SUJET
         echo "fichier a joindre?"
         read FIC
         mail -s "$SUJET" "$DEST" < "$FIC"
      ;;
      *) echo "entree non reconnu"
      ;;
   esac
done