/*Maxime Escourbiac                                     */
/*TP3: Creation d'une base de donnees sous ORACLE       */

/*1er Partie Creer les tables correspondantes en prenant*/
/* en compte les contraintes d integrite suivante       */

CREATE TABLE Fournisseur(
   NumFour number(1,0) constraint CP_Fournisseur primary key,
   NomFour varchar2(15) constraint name not null );
   
CREATE TABLE Article(
   NumArt number(1,0) constraint CP_Article primary key,
   Libelle varchar2(10),
   NumFour number(1,0) constraint CE_Article references Fournisseur(NumFour));
   
CREATE TABLE Client(
   NumClt number(2,0) constraint CP_Client primary key,
   NomCLT varchar2(15) constraint name not null,
   Adresse varchar2(30),
   NumTel char(14));

CREATE TABLE Commande(
   NumArt number(1,0) constraint CE_CommandeArt references Article(NumArt),
   NumClt number(2,0) constraint CE_CommandeClt references Client(NumClt),
   Quantite number(3,0) constraint Quantite not null
                                            check (Quantite > 0),
   primary key(NumArt,NumClt));
   
 
/*2ieme partie En choissisant un ordre d'insertion adapte remplir les differentes tables avec les n-uplet donnees ci-dessous*/

/*insertion des donnees fournisseurs*/

INSERT INTO Fournisseur VALUES(1,'Magouille');
INSERT INTO Fournisseur VALUES(2,'Rigolo');
INSERT INTO Fournisseur VALUES(3,'Sympa');
INSERT INTO Fournisseur VALUES(4,'Chouette');

/*insertion des donnees article*/

INSERT INTO Article VALUES(1,'Pomme',3);
INSERT INTO Article VALUES(2,'Poire',3);
INSERT INTO Article VALUES(3,'Fraise',1);
INSERT INTO Article VALUES(4,'Prune',2);

/*insertion des donnees client*/

INSERT INTO Client VALUES(10,'Picsou','Nice',NULL);
INSERT INTO Client VALUES(40,'Dingo','Clermont-Ferrand','04-73-42-58-12');
INSERT INTO Client VALUES(15,'Picsou','Nantes','02-40-12-15-65');
INSERT INTO Client VALUES(55,'Mickey','Brest','02-51-24-52-87');

/*insertion des donnees Commande*/

INSERT INTO Commande VALUES(1,15,10);
INSERT INTO Commande VALUES(3,40,35);
INSERT INTO Commande VALUES(2,40,42);
INSERT INTO Commande VALUES(3,15,12);
INSERT INTO Commande VALUES(2,55,80);
INSERT INTO Commande VALUES(1,10,60);

/*3ieme partie realiser les operations suivantes*/

/*Q1 inserer le n-uplet (1,'Pomme',5) dans la table article que se passe t'il pourquoi?*/

INSERT INTO Article VALUES(1,'Pomme',5);
/*reponse d'ORACLE*/
ORA-00001: violation de contrainte unique (SYSTEM.CP_ARTICLE)
/*Explication*/
/*Le message d'erreur provient de la premiere erreur due a la violation  de la contrainte primary key de NumArt (l'article 1 existe deja)*/
/*Deplu sil y a violation de la contrainte foreign key du numero de fournisseur car le fournisseur possedant le numero 5 n'existe pas*/

/*Q2 insere le n-uplet (1,55,0)  dans la table COmmande. Que se passe t-il pourquoi?*/

INSERT INTO Commande VALUES(1,55,0);
/*reponse d'ORACLE*/
ORA-02290: violation de contraintes (SYSTEM.SYS_C004043) de vérification
/*Explication*/
/*Lors de la creation de la table commande on a specifie via la commande check que la valeur de la quantite devait etre > 0 */
/*donc il y a violation de cette contrainte*/

/*Q3 insere le n-uplet (1,55,NULL)  dans la table COmmande. Que se passe t-il pourquoi?*/

INSERT INTO Commande VALUES(1,55,NULL);
/*reponse d'ORACLE*/
ORA-01400: impossible d insérer NULL dans ("SYSTEM"."COMMANDE"."QUANTITE");
/*Explication*/
/*Lors de la creation de la table commande on a specifie que la quantite devait etre precise (not null) */
/*donc il y a violation de cette contrainte*/

/*Q4 Supprimer le client 15 dans la table Client. Que se passe t'il pourquoi?*/

DELETE FROM Client
       WHERE NumClt = 15;
/*Reponse d'ORACLE*/
ORA-02292: violation de contrainte (SYSTEM.CE_COMMANDECLT) d intégrité - enregistrement fils existant
/*Explication*/
/*On ne peut pas supprimer ce client  car dans la table Commande il y a un cle etrangere (NumClt) qui depend de la table Client*/
/*Concretement il existe une commande adresse au client 15 donc on ne peut pas supprimer le client 15*/
/*Un solution serait de modifier la table commande et de rajouter la clause ON DELETE CASCADE sur la cle etrangere NumClt*/

/*Q5 Modifier les contraintes d'integrite definies sur la table Commande pour obtenir la suppression automatique des commandes d'un client lorsque celui ci est supprime de la table client*/
ALTER TABLE Commande
DROP CONSTRAINT CE_CommandeClt

ALTER TABLE Commande
MODIFY NumClt number(2,0) constraint CE_CommandeClt references Client(NumClt) ON DELETE CASCADE;

DELETE FROM Client
       WHERE NumClt = 15;
1 row(s) deleted.

/*Q6 Faire les modification pour permettre l'insertion du numero de telephone '02-23-65-87-12' du fournisseur 3 Que se passe t'il pour les autres fournisseurs*/
/*ajout de l'attribut*/
ALTER TABLE Fournisseur
ADD NumTel char(14);

/*insertion du numero de telephone du fournisseur */
UPDATE Fournisseur
SET NumTel = '02-23-65-87-12'
WHERE NumFour = 3;

/*verification de la table*/

SELECT *
FROM Fournisseur;

NUMFOUR	NOMFOUR	NUMTEL
1	Magouille	-
2	Rigolo	-
3	Sympa	02-23-65-87-12
4	Chouette	- 

/*Q7 Faire les modifications de structures pour reduire la longueur de NomFour a 6 caracteres prevoir la recuperation des valeur existantes en les tronquant a 6 caracteres*/

/*Rajout de la colonne */

ALTER TABLE Fournisseur
ADD NomFour2 varchar2(6) not null;

/*Recuperation des 6 premieres caracteres*/
UPDATE Fournisseur
SET NomFour2 =  (SELECT SUBSTR(NomFour,1,6)
                 FROM Fournisseur 
                 WHERE NumFour = 1)
WHERE NumFour = 1
;

UPDATE Fournisseur
SET NomFour2 =  (SELECT SUBSTR(NomFour,1,6)
                 FROM Fournisseur 
                 WHERE NumFour = 2)
WHERE NumFour = 2
;

UPDATE Fournisseur
SET NomFour2 =  (SELECT SUBSTR(NomFour,1,6)
                 FROM Fournisseur 
                 WHERE NumFour = 3)
WHERE NumFour = 3
;

UPDATE Fournisseur
SET NomFour2 =  (SELECT SUBSTR(NomFour,1,6)
                 FROM Fournisseur 
                 WHERE NumFour = 4)
WHERE NumFour = 4
;

/*Suppression de la colonne NomFour*/

ALTER TABLE Fournisseur
DROP COLUMN NomFour;

/*On renome la colonne NomFour2*/

ALTER TABLE Fournisseur
RENAME COLUMN NomFour2 TO NomFour;
 
/*Q8 Creer une vue de nom livraison regroupant les attributs NomClt, Libelle et Quantité pour tous les clients ayant un numero de telephone renseigne*/

CREATE VIEW Livraison as
   SELECT NomClt,Libelle, Quantite
   FROM Article A, Commande C, Client CL
   WHERE CL.NumTel IS NOT NULL AND CL.NumClt = C.NumClt AND A.NumArt = C.NumArt;

NOMCLT	LIBELLE	QUANTITE
Dingo	Fraise	35
Dingo	Poire	42
Mickey	Poire	80

/*Quatrieme Partie: Destruction des tables et vue crees*/

DROP VIEW Livraison;
DROP TABLE Commande;
DROP TABLE Article;
DROP TABLE Fournisseur;
DROP TABLE Client;
