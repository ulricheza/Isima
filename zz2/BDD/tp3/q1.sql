/* TP programmation en PL/SQL*/

A) procedure et fonc stockees

1) Procédure create_dept*

Create or replace procedure create_dept(numero_dept number, dept_name varchar2, localisation varchar2)
Is
 cpt number(5,0);
Begin
    SELECT COUNT(*) into cpt FROM Dept Where Deptno = numero_dept;
    if  cpt = 0 THEN
		Insert Into Dept Values(numero_dept,dept_name,localisation);
	END IF;
END create_dept;
/


