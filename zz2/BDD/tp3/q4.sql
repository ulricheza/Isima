Declare
CURSOR curDelete IS SELECT table_name
              FROM user_tables
			  WHERE table_name LIKE '%_old'
              ORDER BY sal  DESC;
CURSOR curSave IS SELECT table_name
              FROM user_tables
			  WHERE table_name NOT LIKE '%_old'
              ORDER BY sal  DESC;

name_table varchar2(20);
requete varchatr2(80);
BEGIN
open curDelete;
LOOP
		FETCH curDelete INTO name_table;
		EXIT WHEN cur%NOTFOUND;
		execute immediate ('DROP table name_table;');
END LOOP; 
close curDelete;
open curSave;
LOOP
		FETCH curSave INTO name_table;
		EXIT WHEN cur%NOTFOUND;
	    //gerer la generation de chaine via des concat etc 
		create table CONCAT(name_table,'_old') as Select * from nametable;
END LOOP;
close curSave;
END; 			  			  

