drop table CategoriesClt cascade constraints;
drop table Clients cascade constraints;
drop table Produits cascade constraints;
drop table Livraisons cascade constraints;
drop table Composition cascade constraints;


create table CategoriesClt(
  Classe char(1) constraint CP_Categories primary key,
  Reduction number(2,0) constraint Reduc not null 
     check ( Reduction <> 0));


create table Produits(
  NumProduit number(5,0) constraint CP_Produits 
      primary key,
  Libelle varchar2(20),
  PrixBrut number(5,0) constraint Prix 
     check ( PrixBrut <> 0));


create table Livraisons(
  NumProduit number(5,0) constraint CE_Produits 
     references Produits(NumProduit),
  NumClt number(5,0) constraint CE_Client 
     references Clients(NumClt),
  Quantite number(6,0) constraint Qte_Com NOT NULL
     check (Quantite > 0),
  constraint CP_Livraisons 
     primary key (NumProduit, NumClt));


create table Composition(
  NumProCompose number(5,0) constraint CE1_Produits 
     references Produits(NumProduit),
  NumProComposant number(5,0) constraint CE2_Produits 
     references Produits(NumProduit),
  Quantite number(6,2) constraint Qte_Composition NOT NULL
     check (Quantite > 0),
  constraint CP_Composition 
     primary key (NumProCompose, NumProComposant));


insert into Categoriesclt values ('B', 10);
insert into Categoriesclt values ('A', 20);
insert into Categoriesclt values ('C', 12);
insert into Categoriesclt values ('E',  5);


insert into Clients values (1, 'Tintin', 'B');
insert into Clients values (2, 'Dupond', 'E');
insert into Clients values (3, 'Dupont', 'E');
insert into Clients values (4, 'Haddock', 'B');
insert into Clients values (5, 'Tournesol', 'B');
insert into Clients values (6, 'Milou', NULL);
insert into Clients values (7, 'Dupont', 'A');
insert into Clients values (1715, 'Muller', 'E');
insert into Clients values (1718, 'Toto', 'B');
insert into Clients values (1723, 'Girard', 'B');
insert into Clients values (1716, 'girard', 'B');
insert into Clients values (1725, 'Girard', 'B');
insert into Clients values (1724, 'Girard', 'B');
insert into Clients values (17211, 'Girard', 'A');
insert into Clients values (1726, 'Nathalie', 'B');
insert into Clients values (1717, 'Alfred', 'A');
insert into Clients values (1721, 'Girard', 'B');
insert into Clients values (1730, 'Pedrono', 'C');
insert into Clients values (1720, 'Rastapopoulos', 'C');


insert into Produits  values (1, 'Foie', 150);
insert into Produits  values (6, 'Cacahuetes', 25);
insert into Produits  values (18, 'Cacahuettes', 35);
insert into Produits  values (23, 'Cage', 350);
insert into Produits  values (33, 'Peinture', 250);
insert into Produits  values (40, 'Tarte aux pommes', 45);
insert into Produits  values (41, 'Pate', 18);
insert into Produits  values (42, 'Pomme', 2);
insert into Produits  values (43, 'Farine', 2);
insert into Produits  values (44, 'Oeuf', 1);
insert into Produits  values (45, 'Sucre', 10);
insert into Produits  values (46, 'Compote', 12);


insert into Livraisons  values (1, 1, 500);
insert into Livraisons  values (6, 1, 2);
insert into Livraisons  values (6, 5, 10);
insert into Livraisons  values (6, 4, 1);
insert into Livraisons  values (18, 2, 25);
insert into Livraisons  values (23, 4, 1);
insert into Livraisons  values (33, 2, 5);
insert into Livraisons  values (33, 3, 5);
insert into Livraisons  values (23, 7, 2);
insert into Livraisons  values (1, 4, 250);
insert into Livraisons  values (18, 4, 3);
insert into Livraisons  values (33, 4, 55);
insert into Livraisons  values (6, 2, 1);
insert into Livraisons  values (6, 3, 2);
insert into Livraisons  values (6, 7, 3);


insert into Livraisons   values (40, 4, 100);
insert into Livraisons  values (41, 4, 10);
insert into Livraisons   values (42, 4, 25);
insert into Livraisons   values (43, 4, 35);
insert into Livraisons   values (44, 4, 5);
insert into Livraisons   values (45, 4, 13);
insert into Livraisons   values (46, 4, 14);


insert into composition values (40, 41, 1);
insert into composition values (40, 42, 5);
insert into composition values (40, 46, 1);
insert into composition values (40, 45, 0.10);
insert into composition values (41, 43, 1);
insert into composition values (41, 44, 2);
insert into composition values (41, 45, 0.25);

commit ; 



