/*Tp1 de developpement de BDD*/
/*Maxime ESCOURBIAC Jean Christophe SEPTIER*/
/*ZZ2 F2*/

/*fichier SQL loader*/



/*creation de la table Auteur*/

CREATE TABLE Auteurs (
Num NUMBER(3,0) ,
Nom VARCHAR2(20),
Prenom VARCHAR2(20),
Pays VARCHAR2(3),
tel NUMBER(10,0));

/*creation de la table Ouvrage*/
CREATE TABLE Ouvrage (
Code NUMBER(3,0),
Titre VARCHAR2(50),
Prix NUMBER(5,2));

/*creation de la table  Auteur_ouvrage*/
CREATE TABLE Auteur_ouvrage (
Code_ouv NUMBER(3,0),
Num_aut NUMBER(3,0));

/*insertion des donnes de la table Auteurs a l'aide de SQL Loader*/
LOAD DATA FILE *
INTO TABLE Auteurs
FIELDS TERMINATED BY ","
(Num,Nom nullif Nom="null",Prenom nullif Prenom="null",Pays nullif Pays="null",tel nullif tel="null")
begindata
1,Dupont,Jacques,FR,0473151585
2,Durand,Marie,GB,null
3,Dupont,Pierre,null,null
3,Dupont,null,null,null

/*insertion des donnes dans la table Ouvrage*/
INSERT INTO Ouvrage VALUES(1,'Intro aux BDD',260);
INSERT INTO Ouvrage VALUES(2,'Journal de Bolivie',null);
INSERT INTO Ouvrage VALUES(3,'Homme aux sandales',null);

/*insertion des donnees dans la table Auteur_ouvrage*/
INSERT INTO Auteur_ouvrage VALUES(1,1);
INSERT INTO Auteur_ouvrage VALUES(2,2);
INSERT INTO Auteur_ouvrage VALUES(3,2);

/*Ajout des contraintes des clés primaires sur les trois relations*/

/*table ouvrage*/
ALTER TABLE Ouvrage
ADD CONSTRAINT CP_Ouvrage PRIMARY KEY(Code);

/*table Auteur_ouvrage*/
ALTER TABLE Auteur_ouvrage
ADD CONSTRAINT CP_Auteur_ouvrage PRIMARY KEY(Code_ouv,Num_aut); 

/*Table Auteurs*/
/*creationd e la table PK_violation*/

create table PK_violation(
row_id rowid, 
owner varchar2(30), 
table_name varchar2(30), 
constraint varchar2(30)); 


ALTER TABLE Auteurs
ADD CONSTRAINT CP_Auteurs PRIMARY KEY(Num) EXCEPTIONS INTO PK_violation;

/*retour*/
ADD CONSTRAINT CP_Auteurs PRIMARY KEY(Num) EXCEPTIONS INTO PK_violation
               *
ERREUR Ó la ligne 2 :
ORA-02437: impossible de valider (SCOTT.CP_AUTEURS) - violation de la clÚ
primaire


SQL> SELECT * from PK_violation
  2  ;

ROW_ID             OWNER                          TABLE_NAME
------------------ ------------------------------ ------------------------

CONSTRAINT
------------------------------
AAARbWAAEAAAAG9AAD SCOTT                          AUTEURS
CP_AUTEURS

AAARbWAAEAAAAG9AAC SCOTT                          AUTEURS
CP_AUTEURS
/*fin retour */

/*commande pour determiner l'erreur*/
SELECT *
FROM Auteurs 
WHERE ROWID in( SELECT ROW_ID
                FROM  PK_violation);
/*Retour*/
       NUM NOM                  PRENOM               PAY        TEL
---------- -------------------- -------------------- --- ----------
         3 Dupont               Pierre
         3 Dupont
/*fin retour*/

/*requete pour supprimer la ligne en trop */
DELETE FROM Auteurs
WHERE Num = 3 AND Prenom IS NULL; /* Attention IS NULL*/

ALTER TABLE Auteurs
ADD CONSTRAINT UPPER_type CHECK(Nom = UPPER(Nom));

ALTER TABLE Auteurs 
DROP CONSTRAINT CP_Auteurs;