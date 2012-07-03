DECLARE
nom varchar2(10);
salaire number(7,2);
commi number(7,2);
depmt varchar2(14);
BEGIN
	SELECT ename,sal,comm,D.dname INTO nom,salaire,commi,depmt
	FROM Dept D, Emp E
    where E.ename = 'MILLER' and D.deptno = E.deptno;

    dbms_output.put_line('nom'||nom || ' '|| 'salaire' || salaire || ' ' || 'depmt' || depmt);
END;
/	