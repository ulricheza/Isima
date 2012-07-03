DECLARE 
CURSOR cur IS SELECT sal,comm,ename,empno 
              FROM Emp;
			  
sala Emp.sal%type;
num  Emp.empno%type;
name Emp.ename%type;
com Emp.comm%type;
salaire number(8,0);
BEGIN
	OPEN cur;
	LOOP
		FETCH cur INTO sala,com,name,num;
		EXIT WHEN cur%NOTFOUND;
		salaire := sala;
		IF com IS NOT NULL THEN
			salaire := salaire + com;
		END IF;
		IF salaire > 2000 THEN
			INSERT INTO Temp VALUES(salaire,num,name);
		END IF;
	END LOOP;
    CLOSE cur;
END;
/