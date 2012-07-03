DECLARE 
CURSOR cur IS SELECT sal,empno,ename 
              FROM Emp WHERE sal > 4000 and empno NOT IN
														(SELECT empno
													    FROM Emp
														CONNECT BY PRIOR empno = mgr
														START WITH empno = 7902);
			  
sala emp.sal%type;
num  emp.empno%type;
name emp.ename%type;
BEGIN
	OPEN cur;
	FETCH cur INTO sala,num,name;
	INSERT INTO Temp VALUES(sala,num,name);
    CLOSE cur;
END;
/
