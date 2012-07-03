DROP TABLE IF EXISTS RESPONSABLEENTREPRISE;
DROP TABLE IF EXISTS PROPOSITIONKEYWORD;
DROP TABLE IF EXISTS PROPOSITIONOUTIL;
DROP TABLE IF EXISTS PROJETOUTIL;
DROP TABLE IF EXISTS PROJETKEYWORD;
DROP TABLE IF EXISTS PROJETEVALUATION;
DROP TABLE IF EXISTS PROJETRESPONSABLE;
DROP TABLE IF EXISTS PROPOSITIONRESPONSABLE;
DROP TABLE IF EXISTS AFFECTATIONETUDIANT;
DROP TABLE IF EXISTS AFFECTATIONJURY;
DROP TABLE IF EXISTS SOUTENANCE;
DROP TABLE IF EXISTS PROJET;
DROP TABLE IF EXISTS PROPOSITION; 
DROP TABLE IF EXISTS EVALUATION;
DROP TABLE IF EXISTS KEYWORD;
DROP TABLE IF EXISTS OUTIL;
DROP TABLE IF EXISTS ETUDIANT;
DROP TABLE IF EXISTS RESPONSABLE;
DROP TABLE IF EXISTS ENTREPRISE;
DROP TABLE IF EXISTS JURY;



CREATE  TABLE `PROJET` (`idProjet` INT NOT NULL AUTO_INCREMENT ,
                        `sujet` VARCHAR(50),
						`filiere` ENUM("F1","F2","F3","F4","F5","FI", ""),
						`annee` ENUM("ZZ1","ZZ2","ZZ3"),
						`descriptif` TEXT,
						`environnement` SET("Windows","Linux/Unix","Mac OS","A definir"),
						`travailExt` ENUM("OUI","NON"),
						`remuneration` DECIMAL(6,2) DEFAULT "0.0",
						`convention` ENUM("OUI","NON"),
						`remarques` TEXT,
						PRIMARY KEY (`idProjet`)
						);

CREATE TABLE `PROPOSITION` (
                            `idProposition` INT NOT NULL AUTO_INCREMENT ,
                            `sujet` VARCHAR(50),
							`filiere` SET("F1","F2","F3","F4","F5","FI",""),
							`annee` SET("ZZ1","ZZ2","ZZ3"),
						    `descriptif` TEXT,
						    `environnement` SET("Windows","Linux/Unix","Mac OS","A definir"),
							`travailExt` ENUM("OUI","NON"),
							`remuneration` DECIMAL(6,2) DEFAULT "0.0",
							`convention` ENUM("OUI","NON"),
							`remarques` TEXT,
							PRIMARY KEY (`idProposition`)
						   ); 

CREATE TABLE `EVALUATION` (
                           `idEvaluation` INT NOT NULL AUTO_INCREMENT,
                           `assiduite` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `progression` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `espritInitiative` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `communication` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `organisation` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `objectif` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `qualite` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `documentation` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `rapport` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `presentation` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `expression` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `question` ENUM("TInsuffisant","Insuffisant","Moyen","Bon","TBon","Excellent"),
						   `noteProposee` DECIMAL(4,2),
						   `noteReele` DECIMAL(4,2),
						   `commentaires` TEXT,
						   PRIMARY KEY (`idEvaluation`)
                           );

CREATE TABLE `KEYWORD` (
                        `idKeyword` INT NOT NULL AUTO_INCREMENT ,
                        `intitule` VARCHAR(50),
						PRIMARY KEY (`idKeyword`)
					   );
					   
CREATE TABLE `OUTIL` (
                      `idOutil` INT NOT NULL AUTO_INCREMENT ,
                      `nomOutils` VARCHAR(50),
					  `filiere` SET("F1","F2","F3","F4","F5","FI",""),
					  PRIMARY KEY (`idOutil`)
					 );

CREATE  TABLE `ETUDIANT` (`idEtudiant` INT NOT NULL AUTO_INCREMENT ,
                          `nomEtudiant` VARCHAR(15),
						  `prenomEtudiant` VARCHAR(15),
						  PRIMARY KEY (`idEtudiant`)
						  );
						 
CREATE  TABLE `RESPONSABLE`(`idResponsable` INT NOT NULL AUTO_INCREMENT,
                            `nomResponsable` VARCHAR(15),
							`prenomResponsable` VARCHAR(15),
							`adresseResponsable` VARCHAR(100),
							`mailResponsable` VARCHAR(30),
							`telephoneResponsable` VARCHAR(15),
							PRIMARY KEY (`idResponsable`)
							);

CREATE  TABLE `JURY` (`idJury` INT NOT NULL AUTO_INCREMENT,
                      `nomJury` VARCHAR(45),
					  `prenomJury` VARCHAR(45),
					  `mailJury` VARCHAR(45),
					  `telephoneJury` VARCHAR(45),
					  PRIMARY KEY (`idJury`)
					 );
					 
CREATE  TABLE `ENTREPRISE` (`idEntreprise` INT NOT NULL AUTO_INCREMENT,
                            `adresseEntreprise` VARCHAR(50),
							PRIMARY KEY (`idEntreprise`)
							);

CREATE  TABLE `SOUTENANCE` (`idSoutenance` INT NOT NULL AUTO_INCREMENT ,
                            `dateSoutenance` DATETIME,
							`salleSoutenance` VARCHAR(10),
							PRIMARY KEY (`idSoutenance`),
							FOREIGN KEY (idSoutenance) REFERENCES PROJET(idProjet) ON DELETE CASCADE ON UPDATE CASCADE
							);
							
CREATE TABLE `PROPOSITIONOUTIL` (`idOutil` INT NOT NULL ,
                                   `idProposition` INT NOT NULL,
								   FOREIGN KEY (idOutil) REFERENCES OUTIL(idOutil) ON DELETE RESTRICT ON UPDATE CASCADE,
								   FOREIGN KEY (idProposition) REFERENCES PROPOSITION(idProposition) ON DELETE CASCADE ON UPDATE CASCADE
								  );

CREATE TABLE `PROJETOUTIL` (`idOutil` INT NOT NULL ,
                                   `idProposition` INT NOT NULL,
								   FOREIGN KEY (idOutil) REFERENCES OUTIL(idOutil) ON DELETE RESTRICT ON UPDATE CASCADE,
								   FOREIGN KEY (idProposition) REFERENCES PROPOSITION(idProposition) ON DELETE CASCADE ON UPDATE CASCADE
								  );
								  
CREATE TABLE `PROPOSITIONKEYWORD` (`idKeyword` INT NOT NULL ,
                                   `idProposition` INT NOT NULL,
								   FOREIGN KEY (idKeyword) REFERENCES KEYWORD(idKeyword) ON DELETE RESTRICT ON UPDATE CASCADE,
								   FOREIGN KEY (idProposition) REFERENCES PROPOSITION(idProposition) ON DELETE CASCADE ON UPDATE CASCADE
								  );

CREATE TABLE `PROJETKEYWORD` (`idKeyword` INT NOT NULL ,
                              `idProjet` INT NOT NULL,
							  FOREIGN KEY (idKeyword) REFERENCES KEYWORD(idKeyword) ON DELETE RESTRICT ON UPDATE CASCADE,
							  FOREIGN KEY (idProjet) REFERENCES PROJET(idProjet) ON DELETE CASCADE ON UPDATE CASCADE
							 );

CREATE TABLE `PROJETEVALUATION` (`idEvaluation` INT NOT NULL ,
                                 `idProjet` INT NOT NULL,
							     FOREIGN KEY (idEvaluation) REFERENCES EVALUATION(idEvaluation) ON DELETE RESTRICT ON UPDATE CASCADE,
							     FOREIGN KEY (idProjet) REFERENCES PROJET(idProjet) ON DELETE CASCADE ON UPDATE CASCADE
							    );

CREATE  TABLE `PROJETRESPONSABLE` (`idProjet` INT NOT NULL ,
                                   `idResponsable` INT NOT NULL,
								   FOREIGN KEY (idProjet) REFERENCES PROJET(idProjet) ON DELETE CASCADE ON UPDATE CASCADE,
								   FOREIGN KEY (idResponsable) REFERENCES RESPONSABLE(idResponsable) ON DELETE CASCADE ON UPDATE CASCADE
								  );

CREATE  TABLE `PROPOSITIONRESPONSABLE` (`idProposition` INT NOT NULL ,
                                        `idResponsable` INT NOT NULL,
										 FOREIGN KEY (idProposition) REFERENCES PROPOSITION(idProposition) ON DELETE CASCADE ON UPDATE CASCADE,
										 FOREIGN KEY (idResponsable) REFERENCES RESPONSABLE(idResponsable) ON DELETE CASCADE ON UPDATE CASCADE
										);
										
CREATE  TABLE `AFFECTATIONETUDIANT` (`idProjet` INT NOT NULL ,
                                     `idEtudiant` INT NOT NULL,
									 `filiere` VARCHAR(3),
									 `annee` INT,
									 FOREIGN KEY (idProjet) REFERENCES PROJET(idProjet) ON DELETE CASCADE ON UPDATE CASCADE,
									 FOREIGN KEY (idEtudiant) REFERENCES ETUDIANT(idEtudiant) ON DELETE CASCADE ON UPDATE CASCADE
									 );
									
CREATE  TABLE `AFFECTATIONJURY` (`idSoutenance` INT NOT NULL ,
                                 `idJury` INT NOT NULL,
								 FOREIGN KEY (idSoutenance) REFERENCES SOUTENANCE(idSoutenance) ON DELETE CASCADE ON UPDATE CASCADE,
								 FOREIGN KEY (idJury) REFERENCES JURY(idJury) ON DELETE CASCADE ON UPDATE CASCADE
								 );
								 
CREATE  TABLE `RESPONSABLEENTREPRISE` (`idEntreprise` INT NOT NULL ,
                                       `idResponsable` INT NOT NULL,
								       FOREIGN KEY (idEntreprise) REFERENCES ENTREPRISE(idEntreprise) ON DELETE CASCADE ON UPDATE CASCADE,
								       FOREIGN KEY (idResponsable) REFERENCES RESPONSABLE(idResponsable) ON DELETE CASCADE ON UPDATE CASCADE
								      );				
