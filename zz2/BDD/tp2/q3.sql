DECLARE 
CURSOR cur IS SELECT sal,empno,ename 
              FROM Emp
              ORDER BY sal  DESC;
sala emp.sal%type;
num  emp.empno%type;
name emp.ename%type;
BEGIN
	OPEN cur;
	FOR i IN 1..5 LOOP
		FETCH cur INTO sala,num,name;
		EXIT WHEN cur%NOTFOUND;
		INSERT INTO Temp VALUES(sala,num,name);
	END LOOP;
    CLOSE cur;
END;
/
