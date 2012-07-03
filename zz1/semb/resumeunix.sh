# Maxime ESCOURBIAC
# ZZ1
# Memo sur les differentes commande en UNIX vue durant les semaines bloquees

# Les commandes de deplacement dans l'aborescense

cd <repertoire>       ::: le repertoire devient le repertoire courant

ls                    ::: affiche les fichiers et repertoires du repertoire
courant
    -l                ::: affiche des infos complementaire (droits notamment)
    -a                ::: affiche les dossiers et fichiers cachés (ex: .bashrc)

pwd                   ::: affiche le chemin du repertoire courant

mkdir                 ::: creer un repertoire

rmdir                 ::: supprime un repetoire ssi il est vide

cp <source> <destination> ::: copie le fichier source dans destination

mv <source> <destination> ::: deplace le fichier source dans destination

rm                    ::: supprime un fichier
    -r                ::: supprime un repertoire non vide
    -i                ::: demande confirmation avant de supprimer

#la commande essentielle!!!

man <fonction>        ::: affiche le manuel de la fonction

#commande de gestion de compte

passwd                ::: permet de changer le pass de la session

#commande relative aux fichiers

touch <fichier>       ::: creer un fichier vide

cat <fichier>         ::: affiche le contenu de fichier

more <fichier>        ::: affiche le fichier page par page

less <fichier>        ::: affiche le fichier dans un 'terminal' a part

tail <fichier>        ::: affiche la fin du fichier 
    -n                ::: affiche les n dernieres lignes


#commande relative a VI    fichier de configuration .exrc
#mode commande
:w                    ::: sauvegarde le fichier
:q!                   ::: quitte vi
:wq                   ::: quitte & sauvegarde le fichier
:/<motif>             ::: recherche <motif>
.                     ::: derniere commande
u                     ::: annuler

#mode edition
i                     ::: mode insertion
a                     ::: mode append
r                     ::: mode replace
yy                    ::: copier
dd                    ::: couper
P                     ::: coller

#commande pour l'imprimante

lp,lpr                       ::: envoie un job a l\'imprimante
        -P <printer name>
        -# <nbre exemplaire>
lpstat,lpq                   ::: statue liste d\'attente de l\'imprimante
lprm,cancel                  ::: annule un job en cours

#commande sur les droits d'accées 

chown            ::: change de proprietaire 
chgrp            ::: change de groupe
chmod  u+rwx     ::: change les droits du fichier
       g-
       o=
       a
       755       ::: u=7 g=5 o=5 (read=4 write=2 execute=1)

#commande sur les liens

ln <source> <destination>  ::: lien physique
   -s                      ::: lien symbolique

#commande sur les processus

ps                         ::: affiche les processus lié au terminal
     -aux                  ::: affiche tous les processus
     -l                    ::: affiche les processus lié au terminal avec des
                               infos supplementaire
top                        ::: affiche tous les processus en temps reel (% du
                               cpu)
<commande>&                ::: lance le programme en arriere-plan
fg                         ::: met le programme en premier plan
   %pid
kill -n° <PID>             ::: tue le programme PID (n° entre 1 et 9) 9 kill
obligatoirement
     %job                  ::: Pour les processus en arriere plan

#commande sur les redirections

<commande> > <fichier>     ::: met le resultat de la commande dans le fichier
(ECRASE)
#variante
(<c1>;<c2>;...)>  <fichier>::: permet de rajouter plusieurs resultats 
<commande> >> <fichier>    ::: rajoute en fin de fichier le resultat commande
1>                         ::: idem mais redirige que la sortie standard
2>                         ::: idem mais redirige la sortie d\'erreur (pensez au
                               /dev/null pour le neant)
<commande> < <fichier>     ::: met fichier en entree de la commande

<commande1> | <commande2>  ::: redirige la sortie de commande1 vers l\'entree de
commande2

#commande annexe
nohup <commande>                                ::: desactive le lien de parenté
                                                    avec le terminal
find <repertoire> -name <nom> -print <options>  ::: permet de chercher nom dans
                                                    le repertoire (recurssif)
which <commande>                                ::: donne le chemin de la
                                                    commande
nice +n <commande>&                             ::: donne une valeur de priorité
                                                    a la commande
at <heure>                                      ::: permet d\'executer un script
                                                    a une heure donnee
#ex: 
at 00:59
at> echo "Bonjour"
at> <EOT>
#fin exemple
cron                                            ::: equivalent de scheduler sous
                                                    windows (file: crontab)

#commande sur le reseau
ssh <serveur>                       ::: ouvre une connexion ssh avec le serveur
    -l <login>                      ::: pour specifier un login
    -X                              ::: permet d\'exporter l\'ecran
telnet                              ::: equivalent au ssh mais en clair

#transfert de fichiers
ftp, sftp, scp                      ::: permet de transferer des fichiers
                                        avec differents protocole
#commande de ftp
binary <fichier>                    ::: converti un fichier binaire
ascii  <fichier>                    ::: converti en ascii

#parcours en mode local   
lcd    ::: local change directory
put    ::: pour upload un fichier
mput   ::: pour upload plusieurs fichier
#parcours sur la machine distante
cd     ::: cd
ls     ::: ls
get    ::: telecharger un fichier
mget   ::: telecharger plusieurs fichiers

#commande mail
mail -s "sujet" <adresse>             ::: ouvre une interface pour mailer
                          < <fichier> ::: joind un fichier

#commande tar 
tar -cfv <destination> <source>       ::: regroupe des fichiers
     j                                ::: compresse en tar.gz
    -xfv                              ::: degroupe des fichiers
     j                                ::: decompresse le tar.gz

#explications rapide sur les scripts

#!/bin/bash  
explique quel bash on va utiliser

#les chaines
'chaine' == aucun caractere est remplacé
"chaine" == les caracteres sont evalués a part \ 
`date`   == evalue la fonction `` 

#variables speciales
./toto parametre1 parametre2
  $0      $1       $2

$# ::: nombre de parametre
$* ::: liste entiere

#exemple pour un alias a modifier dans le .bashrc

alias -x rm="rm -i"