/*Maxime ESCOURBIAC
  Sebastien SAINT-MARTIN
  G1
  TP Base de donnees
*/

/*
TP1: Interrogation en SQL sous ORACLE
*/



/*Q1 Donner les categories attritbueesaux clients(enlever les doubles)*/

SELECT DISTINCT(Categorie)
FROM Clients;


/*Q2 Donner les clients de categories 'A'*/

SELECT NomClt
FROM Clients C
WHERE C.Categorie = 'A';


/*Q3 Donner le nombre de produit existant*/

SELECT COUNT(*)
FROM Produits;

/*Q4 Donner le nombre de produit vendues au client 1*/

SELECT COUNT(*)
FROM Clients C, Livraisons L
WHERE L.NumClt = C.NumClt AND C.NumClt = 1;

/*Q5 Donner les numeros des clients auxquels le produit 6 a �t� livr� avec une quantit� sup�rieure � 2*/

SELECT C.NumClt
FROM Clients C, Livraisons L
WHERE L.NumProduit = 6 and L.Quantite > 2 and C.NumClt = L.NumClt;

/*Q6 Donner le prix le plus eleve des produits*/

SELECT MAX(Prixbrut)
FROM Produits;

/*Q7 Donner le numero et le libell� du produit le plus cher*/

SELECT NumProduit,Libelle
FROM Produits
WHERE PrixBrut >= ALL (SELECT PrixBrut
                      FROM Produits);
 
/*Q8 Quels sont les noms des clients commencant par "Du"*/

SELECT distinct NomClt
FROM CLients
WHERE NomClt LIKE 'Du%';

/*Q9 Quels sont les clients qui ont ete livr�e d'un des deux produit, 5 ,6*/

SELECT NumClt
FROM Livraisons L
WHERE NumProduit = 5 OR NumProduit = 6;

/*Q10 Quel est le numero des clients qui ont �t� livr�s des numero 1 et 6*/

SELECT NumClt
FROM Livraisons L
WHERE NumProduit = 1
INTERSECT 
SELECT NumClt
FROM Livraisons L
WHERE NumProduit = 6;

/*Q11 Quels sont les noms et les categories des clients livree*/

SELECT C.NomClt , C.Categorie
FROM Clients C
WHERE C.Numclt IN (SELECT NumClt
                   FROM Livraisons
                   GROUP BY NumClt); 


SELECT DISTINCT C.NomClt , C.Categorie
FROM Clients C, Livraisons L
WHERE C.Numclt = L.Numclt;

/*Q12 Quels sont les produit bon march� qui ont ete livres a des client de categorie A*/

SELECT P.Libelle
FROM Produits P, Livraisons L
WHERE P.PrixBrut < 55 AND L.NumProduit = P.Numproduit AND L.NumClt IN (SELECT NumClt
                                                                       FROM Clients
                                                                       WHERE Categorie = 'A');

/*Q13 Quels sont les libelles des produits qui ont ete livres a Dupont */

SELECT P.Libelle
FROM Clients C, Livraisons L, Produits P
WHERE C.NomClt LIKE 'Dupont' AND C.NumClt = L.NumClt AND L.NumProduit = P.NumProduit
MINUS
SELECT P.Libelle
FROM Clients C, Livraisons L, Produits P
WHERE C.NomClt NOT LIKE 'Dupont' AND C.NumClt = L.NumClt AND L.NumProduit = P.NumProduit;

/*Q14 Quels sont les libelles des produit qui ont ete livre au client 3 et au client 5*/

SELECT P.Libelle
FROM Livraisons L , Produits P
WHERE L.NumClt = 3 AND P.NumProduit = L.NumProduit
INTERSECT 
SELECT P.Libelle
FROM Livraisons L, Produits P
WHERE L.NumClt = 5 AND P.NumProduit = L.NumProduit;

/*Q15 Donner pour chaque produit livre le nombre de fois ou il a ete livre(renommer la colonne en Nbre de Livraison)*/

SELECT L.Numproduit, COUNT(*) "Nbre de livraison"
FROM Produits P, Livraisons L
WHERE P.NumProduit = L.NumProduit
GROUP BY L.Numproduit;

/*Q16 Quels sont les numeros des clients auxquels on a livre tous les produits*/

SELECT L.NumClt
FROM Livraisons L
GROUP BY L.NumClt
HAVING COUNT(*) = (SELECT COUNT(*)
                FROM Produits);

/*Q17 Quels sont les numero de clients qui ont ete livre de tous les produits coutant moins de 50eur*/      

SELECT L.NumClt
FROM Livraisons L,Produits P
Where P.NumProduit = L.NumProduit AND P.PrixBrut < 50
GROUP BY L.NumClt
HAVING COUNT(*) = (SELECT COUNT(*)
                    FROM Produits
                    WHERE PrixBrut < 50);

/*Q18 Donner la quantite moyenne livree pour les produits faisant l'objet de plus de deux livraisons. trier les donn�es par ordre decroissant de numero*/

SELECT L.NumProduit, AVG(L.Quantite)
FROM Livraisons L
GROUP BY L.NumProduit
HAVING COUNT(*) >1
ORDER BY L.NumProduit DESC;

/*Q19 donner le nom du produit qui a ete le plus livre et le nombre de livraisons correspondants */

SELECT P.libelle, COUNT(*)"Nbre de livraisons" 
FROM Livraisons L, Produits P
WHERE P.NumProduit = L.NumProduit
GROUP BY L.Numproduit, P.libelle
HAVING COUNT(*) = (SELECT MAX(COUNT (*))
                   FROM Livraisons L
                   GROUP BY L.NumProduit);


/*Q20 Donner le chiffe d'affaire par produit*/

SELECT Libelle,SUM(CA)
FROM( SELECT P.Libelle, P.PrixBrut*SUM(L.Quantite)-(Cat.Reduction/100 * P.PrixBrut*SUM(L.Quantite)) "CA"
      FROM Livraisons L,Produits P, Clients C, CategoriesClt Cat
      WHERE P.NumProduit = L.NumProduit AND L.NumClt = C.NumClt AND C.Categorie=Cat.Classe
      GROUP BY L.Numproduit, P.Libelle, P.PrixBrut,Cat.Reduction)
GROUP BY Libelle;

/*Q21 Pour chaque client donner son numero son nom, et si il a commande la liste des produit et sa quantite*/

SELECT C.NomClt,C.NumClt,P.Libelle,L.Quantite
FROM Livraisons L,Produits P, Clients C
WHERE L.NumClt = C.NumClt AND L.NumProduit = P.NumProduit
UNION
SELECT C.NomClt,C.NumClt,'',NULL
FROM Livraisons L , Clients C
WHERE C.NumClt NOT IN (SELECT C.NumClt FROM Clients C,Livraisons L WHERE L.NumClt = C.NumClt);





