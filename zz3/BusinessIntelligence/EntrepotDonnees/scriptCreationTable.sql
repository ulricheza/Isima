DROP TABLE IF EXISTS FAIT;
DROP TABLE IF EXISTS D_Provenance;
DROP TABLE IF EXISTS D_Nationalite;
DROP TABLE IF EXISTS D_Niveau;
DROP TABLE IF EXISTS D_Domaine;
DROP TABLE IF EXISTS D_Bac;
DROP TABLE IF EXISTS D_Entreprise;


CREATE TABLE `D_Entreprise`(
   `NomEntreprise` VARCHAR(25),
   `GroupeEntr` VARCHAR(25),
   `DomaineEntr` VARCHAR(25),
   `TypeEntr` VARCHAR(25),
   `VilleEntr` VARCHAR(25),
   `DeptEntr` VARCHAR(25),
   `RegEntr` VARCHAR(25),
   `PaysEntr` VARCHAR(25),
   PRIMARY KEY (`NomEntreprise`)
);

CREATE TABLE `D_Bac`(
   `deptBac` VARCHAR(25),
   `regBac` VARCHAR(25),
   `paysBac` VARCHAR(25),
   PRIMARY KEY (`deptBac`)
);

CREATE TABLE `D_Domaine`(
   `SSDomaine` VARCHAR(25),
   `domaine` VARCHAR(25),
   PRIMARY KEY (`SSDomaine`)
);

CREATE TABLE `D_Niveau`(
   `niveau` VARCHAR(25),
   `filiere` VARCHAR(25),
   `annee` VARCHAR(25),
   PRIMARY KEY (`niveau`)
);

CREATE TABLE `D_Nationalite`(
   `nationalite` VARCHAR(25),
   `natType` VARCHAR(25),
   PRIMARY KEY (`nationalite`)
);

CREATE TABLE `D_Provenance`(
   `provenance` VARCHAR(25),
   `provType` VARCHAR(25),
   `niveau` VARCHAR(25),
   PRIMARY KEY (`provenance`)
);

CREATE TABLE `FAIT` (
   `sexe` VARCHAR(25),
   `LV2` VARCHAR(25),
   `LV3` VARCHAR(25),
   `age` VARCHAR(25),
   `etudiant` VARCHAR(25),
   `redoublant` VARCHAR(25),
   `statut` VARCHAR(25),
   `anneeScolaire` VARCHAR(25),
   `cspParent` VARCHAR(25),
   `anneeBac` VARCHAR(25),
   `MentionBac` VARCHAR(25),
   `typeBac` VARCHAR(25),
   #Cle etrangere 
   `provenance` VARCHAR(25),
   `nationalite` VARCHAR(25),
   `domaineprojet` VARCHAR(25),
   `domainestage` VARCHAR(25),
   `deptBac` VARCHAR(25),
   `entrProjet` VARCHAR(25),
   `entrStage` VARCHAR(25),
   `niveau` VARCHAR(25),
   `idLigne` INT NOT NULL AUTO_INCREMENT,
   UNIQUE KEY (`etudiant`,`anneeScolaire`),
   PRIMARY KEY (idLigne),
   FOREIGN KEY (provenance) REFERENCES D_Provenance(provenance) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (nationalite) REFERENCES D_Nationalite(nationalite) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (niveau) REFERENCES D_Niveau(niveau) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (domaineprojet) REFERENCES D_Domaine(SSDomaine) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (domainestage) REFERENCES D_Domaine(SSDomaine) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (deptBac) REFERENCES D_Bac(deptBac) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (entrProjet) REFERENCES D_Entreprise(NomEntreprise) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (entrStage) REFERENCES D_Entreprise(NomEntreprise) ON DELETE CASCADE ON UPDATE CASCADE
);
