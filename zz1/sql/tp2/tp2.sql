!Tp1 bis bases de données
! Requetes simple de SQL

!Q1 Donner toutes les informations des pilotes

SELECT *
FROM PILOTE;

!Q2 Donner le nom et le adresses du pilote

SELECT PLNOM 'NOM',VILLE
FROM PILOTE;

!Q3 Selectionner l identificateur et le nom de chaque pilote

SELECT PLNUM,PLNOM
FROM PILOTE;

!Q4 Quelles sont les villes de départ des differents vols

SELECT DISTINCT LOCALISATION
FROM AVION;

!Q5 Selectionner les noms des pilotes qui habitent Paris

SELECT PLNOM
FROM PILOTE P
WHERE P.VILLE = 'PARIS';

!Q6 Selectionner les noms des pilotes qui gagne plus de 26000F

SELECT PLNOM
FROM PILOTE P
WHERE P.SALAIRE > 25000;

!Q7 Selectionner le nom des pilotes dont l adresse est inconnue

SELECT PLNOM
FROM PILOTE P
WHERE P.VILLE IS NULL;

!Q8 selectionner les avions de nom A310,A320,A330,A340

SELECT *
FROM AVION A
WHERE A.AVNOM = 'A310' OR A.AVNOM = 'A320' OR A.AVNOM = 'A330' OR A.AVNOM = 'A340';

!Q9 Quels sont les pilotes qui gagnent entre 20000F et 25000F

SELECT PLNOM
FROM PILOTE P
WHERE P.SALAIRE BETWEEN 20000 AND 25000;

!Q10 Quelles sont les capacites des avions de type Airbus

SELECT CAPACITE
FROM AVION A
WHERE A.AVNOM LIKE 'A%';

!Q11 Quels sont les noms des avions differents de A310,A320,A330,A340

v1:
SELECT AVNOM
FROM AVION
MINUS
SELECT AVNOM
FROM AVION A
WHERE A.AVNOM = 'A310' OR A.AVNOM = 'A320' OR A.AVNOM = 'A330' OR A.AVNOM = 'A340';

v2:
SELECT *
FROM AVION A
WHERE A.AVNOM <> 'A310' AND A.AVNOM <> 'A320' AND A.AVNOM <> 'A330' AND A.AVNOM <> 'A340';

!Q12 Quels sont les vols au depart de nice pour paris

SELECT VOLNUM
FROM VOL V
WHERE V.VILLEDEP = 'NICE' AND V.VILLEARR = 'PARIS';

!Q13 Quels sont les vols au depart d une ville et dont l heure d arrive a une date donnee par l utilisateur

SELECT *
FROM VOL V
WHERE V.VILLEDEP = 'PARIS' AND V.HEUREARR < 1800;  /*se renseigner sur les dates*/

!Q15 Trouver le nombre de vols au départ de Paris

SELECT COUNT(*)
FROM VOL V
WHERE V.VILLEDEP = 'PARIS';

!Q16 Trouver le nom des pilotes effectuant des vols au departde Paris sur un airbus

SELECT DISTINCT P.PLNOM
FROM PILOTE P, AVION A, VOL V
WHERE P.PLNUM = V.PLNUM AND V.VILLEDEP = 'PARIS' AND V.AVNUM IN (SELECT AVNUM
                                        FROM AVION A1
                                        WHERE A1.AVNOM LIKE 'A%');

!Q17 Quels sont les avions localisés dans la meme ville que l avion 3 

SELECT AVNUM
FROM AVION A
WHERE A.AVNUM <> 3 AND A.LOCALISATION IN (SELECT LOCALISATION
                                          FROM AVION A1									  
                                          WHERE A1.AVNUM = 3);

!Q18 Quels sont les pilotes qui ont un salaire plus eleve que la moyenne des salaires des pilotes

SELECT PLNOM
FROM PILOTE P
WHERE P.SALAIRE > (SELECT AVG(SALAIRE)
                   FROM PILOTE);

!Q19 Quels sont les noms des pilotes en service au depart de Paris

SELECT DISTINCT PLNOM
FROM PILOTE P, VOL V
WHERE V.VILLEDEP = 'PARIS' AND V.PLNUM = P.PLNUM;

!Q20 Quels sont les noms des pilotes nicois qui gagne plus que tous les pilotes parisiens

SELECT PLNOM
FROM PILOTE P
WHERE P.VILLE='NICE' AND P.SALAIRE > (SELECT MAX(SALAIRE)
                                      FROM PILOTE P1
                                      WHERE P1.VILLE = 'PARIS');

!Q21 Quels sont les noms des pilotes nicois qui gagne plus que au moins un pilote parisien
SELECT PLNOM
FROM PILOTE P
WHERE P.VILLE='NICE' AND P.SALAIRE > (SELECT MIN(SALAIRE)
                                      FROM PILOTE P1
                                      WHERE P1.VILLE = 'PARIS');

!Q22 Recherche les pilotes qui ont meme adresse et meme salaire que miranda

SELECT PLNOM
FROM PILOTE P
WHERE P.PLNOM <> 'MIRANDA' AND P.VILLE= (SELECT VILLE                
                                         FROM PILOTE P1
                                         WHERE P1.PLNOM = 'MIRANDA') AND P.SALAIRE = (SELECT SALAIRE
                                                                                      FROM PILOTE P2
                                                                                      WHERE P2.PLNOM = 'MIRANDA');

!Q23 Donner la liste des pilotes parisiens par ordre de salaire decroissant puis par ordre alphabetique des noms

SELECT PLNOM,SALAIRE
FROM PILOTE P
ORDER BY SALAIRE DESC , 1 ASC ;

!Q24 Quels est le nombre de vol effectue par pilote

SELECT DISTINCT PLNOM,COUNT (*)
FROM PILOTE P ,VOL V
WHERE V.PLNUM = P.PLNUM
GROUP BY V.PLNUM, P.PLNOM;

!Q25 Trouver les nombres de vol par pilote et par avion

SELECT PLNOM,AVNUM, COUNT (*)
FROM PILOTE P ,VOL V
WHERE V.PLNUM = P.PLNUM
GROUP BY V.PLNUM, V.AVNUM, P.PLNOM;

!Q26Donner le nombre de vol par pilote seulement si il est seulement superieur a 5

SELECT DISTINCT PLNOM,COUNT (*)
FROM PILOTE P ,VOL V
WHERE V.PLNUM = P.PLNUM
GROUP BY V.PLNUM, P.PLNOM
HAVING COUNT(*) > 5;

!Q27 Quels sont les avions de capacite superieure a 250 ou localise a paris

SELECT AVNUM
FROM AVION A
WHERE A.LOCALISATION = 'PARIS' OR A.CAPACITE > 250;

!Q28 Quels sont les pilotes qui pilotent les avions 2 et 4

SELECT PLNOM
FROM PILOTE P, VOL V
WHERE V.AVNUM = 2 AND V.PLNUM = P.PLNUM 
INTERSECT
SELECT PLNOM
FROM PILOTE P, VOL V
WHERE V.AVNUM = 4 AND V.PLNUM = P.PLNUM;

Quels sont les pilotes qui pilotent les avions 2 ou 4

SELECT DISTINCT PLNOM
FROM ( SELECT PLNOM
       FROM PILOTE P, VOL V
       WHERE V.AVNUM = 2 AND V.PLNUM = P.PLNUM 
       UNION
       SELECT PLNOM
       FROM PILOTE P, VOL V
       WHERE V.AVNUM = 4 AND V.PLNUM = P.PLNUM);

SELECT DISTINCT PLNOM
       FROM PILOTE P, VOL V
       WHERE (V.AVNUM = 2 OR V.AVNUM = 4) AND V.PLNUM = P.PLNUM ;

!Q29 Quels sont les pilotes qui conduisent l avion 2 mais pas le 4

SELECT PLNOM
FROM PILOTE P, VOL V
WHERE V.AVNUM = 2 AND V.PLNUM = P.PLNUM 
MINUS
SELECT PLNOM
FROM PILOTE P, VOL V
WHERE V.AVNUM = 4 AND V.PLNUM = P.PLNUM;

!Q30 Qui sont les pilotes qui pilotent tous les avions de la compagnie

SELECT PLNOM
FROM PILOTE P, VOL V
WHERE P.PLNUM = V.PLNUM
GROUP BY V.PLNUM,P.PLNOM
HAVING COUNT (DISTINCT AVNUM) = (SELECT COUNT(*)
                                 FROM AVION);

 
   Qui sont les pilotes qui pilotent tous les avions de type A310

SELECT PLNOM
FROM PILOTE P, VOL V, AVION A
WHERE P.PLNUM = V.PLNUM AND A.AVNOM = 'A310' AND V.AVNUM = A.AVNUM
GROUP BY V.PLNUM,P.PLNOM
HAVING COUNT (DISTINCT V.AVNUM) = (SELECT COUNT(*)
                                 FROM AVION A1
                                 WHERE A1.AVNOM = 'A310');

!Q31 Lister les noms et numeros des avions autres que boeing qui sont conduits par tous les pilotes ayant un salaire sup au salaire des pilotes clermontois



SELECT AVNOM, AVNUM
FROM AVION A, PILOTE P, VOL V
WHERE A.AVNOM NOT LIKE 'B%' AND P.PLNUM = V.PLNUM AND A.AVNUM = V.AVNUM AND P.SALAIRE > (SELECT AVG(SALAIRE)
                                                                                         FROM PILOTE P1
																	                     WHERE P1.VILLE = 'CLERMONT');
																						 
!Q32 Lister les paires de numero de pilotes

Requetes non comprises
