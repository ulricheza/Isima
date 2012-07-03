Maxime ESCOURBIAC
Jean-Christophe SEPTIER

TP de developpement .NET

Realisation d'un Serveur de messagerie interne ainsi que le client associe


Specification:

Serveur:
-Stockage des messages et des utilisateurs par serialisation
-Gestion des messages prive & public
-Reception des nouveaux messages (ecrit apres la derniere reception de nouveaux messages)
-Le changement de login.
-Persistance des donnees via serialization (choix expliqué plus tard)

Client:
-Connexion et deconnexion
-Interface de creation de comptes
-Interface d'ecriture de message
-Lecture des messages par un view
-Utilisation d'un TreeView pour acceder aux messages.
-Serialisation des proportions de l'interface principale

Choix de la serialisation pour la persistance:

On a choisi cette methode par rapport aux variables Session et application car elle presente plusieurs avantages:
- Une vraie persistance des données meme en cas de crash du serveur.
- La manipulation d'une instance de chat n'est pas plus difficile et perilleuse.
- la possibite de d'effectuer des sauvegardes regulieres.

Cependant elle presente deux inconvenients:
- Une rapidite de reponse plus faible
- Un risque de saturation du serveur

Mais, dans le cadre de ce mini-projet,il nous est pas demande de gerer une application gerant un nombre imposant
de connection simultanee donc cette methode est largement suffisant pour son utilisation.
Si le projet devrait etre deploye a plus grande echelle, il serait necessaire de remplacer la serialisation
par un systeme de base de donnee pour gerer l'affluence.
