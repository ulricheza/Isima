Create or replace procedure raise_salary(emp_id number, amount number)
Is
cpt number;
Begin
    SELECT COUNT(*) into cpt FROM Emp E, SalIntervalle S Where emp_id = E.empno
	AND S.job = E.job
	AND (E.sal + amount) < S.hsal
	AND (E.sal + amount) > S.lsal;
    if  cpt = 1 THEN
		update Emp set sal = sal + amount
		where emp_id=empno;
	END IF;
END raise_salary;
/