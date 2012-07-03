LOAD DATA INFILE *
INTO TABLE Auteurs
FIELDS TERMINATED BY ","
(Num,Nom nullif Nom="null",Prenom nullif Prenom="null",Pays nullif Pays="null",tel nullif tel="null")
begindata
1,Dupont,Jacques,FR,0473151585
2,Durand,Marie,GB,null
3,Dupont,Pierre,null,null
3,Dupont,null,null,null