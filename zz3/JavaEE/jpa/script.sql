DROP TABLE IF EXISTS PERSONNE; 

CREATE  TABLE `PERSONNE` (`prenom` VARCHAR(15) ,
                          `nom` VARCHAR(15),
						  `telephone` VARCHAR(15),
						  `mail` VARCHAR(15),
						  PRIMARY KEY(prenom,nom)
						  );