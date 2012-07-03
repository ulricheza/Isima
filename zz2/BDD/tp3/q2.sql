create table SalIntervalle(job varchar2(9), lsal number(7,2), hsal number(7,2));
insert into SalIntervalle values('ANALYST',2500,3000);
insert into SalIntervalle values('CLERK',900,1300);
insert into SalIntervalle values('MANAGER',2400,3000);
insert into SalIntervalle values('PRESIDENT',4500,4900);
insert into SalIntervalle values('SALESMAN',1200,1700);

create or replace function sal_ok
(job varchar2, salaire number)
return number
IS
cpt number(5);
BEGIN
 select COUNT(*) INTO cpt FROM SalIntervalle S WHERE S.job = job
 AND salaire > lsal AND salaire < hsal;
 
 RETURN (cpt);
 End sal_ok;
 /


VARIABLE moyenne NUMBER
EXECUTE :moyenne:=sal_ok('CLERK',1000);
PRINT moyenne;
