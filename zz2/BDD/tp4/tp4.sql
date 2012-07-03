
/* 
Package interface
*/

Create or replace Package tp4 AS
Type EmpRecTyp is record (emp_id emp.empno%type, emp_name emp.ename%type);
cursor emp_par_dep(dept_no dept.deptno%type) return EmpRecTyp;
procedure raise_sal(emp_num in emp.empno%type, salaire in emp.sal%type);
procedure afficher_emp(deptno dept.deptno%type);
end tp4;

/*fonction sal5ok*/
create or replace function sal5_ok
(job1 in salintervalle.job%type, salaire in salintervalle.lsal%type)
RETURN number
IS
ret number(5):=0;
BEGIN
	Select count(*) into ret from salintervalle where job=job1 AND salaire between hsal and lsal;
	return(ret);
end sal5_ok;
/

/*Declaration du package*/

CREATE OR REPLACE PACKAGE BODY tp4 AS  
   CURSOR emp_par_dep(dept_no dept.deptno%type) RETURN EmpRecTyp IS
      SELECT empno, ename FROM emp where dept_no=deptno;
   PROCEDURE raise_sal (emp_num in emp.empno%type, salaire in emp.sal%type) IS
	a number(5);
	chaine varchar2(50);
	typ varchar2(50);
BEGIN
	Select job into typ from emp where empno=emp_num;
	Select sal5_ok(typ,salaire) into a from dual;
	if a=1 then
		update emp set sal=salaire where empno=emp_num; 
	else
		chaine:='update impossible';
		dbms_output.put_line(chaine);
	end if;
	Commit;
end raise_sal;

   PROCEDURE afficher_emp (deptno dept.deptno%type) IS
   id emp.empno%type;
   name emp.ename%type;
   BEGIN
   Open emp_par_dep(deptno);
	LOOP
		FETCH emp_par_dep into id,name;
		EXIT WHEN (emp_par_dep%NOTFOUND);
	END LOOP;
	CLOSE emp_par_dep;
   END afficher_emp;
END tp4;

/* 
	Trigger
*/

/* Question 1 */

create or replace trigger Print_salary_changes
	before update on emp for each row when (new.sal <old.sal)
declare
begin
    dbms_output.put('Old salary: ' || :old.sal);
    dbms_output.put('  New salary: ' || :new.sal);
	Raise_application_error(-20201, 'pas le droit de baisser un salaire');
END;
/

/*

      7934 MILLER     CLERK           7782 23/01/82       1300
        10


14 ligne(s) sÚlectionnÚe(s).

SQL> update emp set sal=1000 where empno=7934;
update emp set sal=1000 where empno=7934
       *
ERREUR Ó la ligne 1 :
ORA-20201: pas le droit de baisser un salaire
ORA-06512: Ó "SCOTT.PRINT_SALARY_CHANGES", ligne 5
ORA-04088: erreur lors d'exÚcution du dÚclencheur 'SCOTT.PRINT_SALARY_CHANGES'


SQL> show errors
Pas d'erreur.
SQL> select * from emp where empno=7934;

     EMPNO ENAME      JOB              MGR HIREDATE        SAL       COMM
---------- ---------- --------- ---------- -------- ---------- ----------
    DEPTNO
----------
      7934 MILLER     CLERK           7782 23/01/82       1300
        10
*/

/*Question 2*/
create or replace trigger Dept_not_found
	before update or insert on emp for each row
declare
	a number(2) :=0;
begin
	select count(*) into a from dept where deptno=:new.deptno;
	
	if a=0 then
		insert into dept values (:new.deptno,'a saisir','a saisir');
	end if;
END;
/

/*

SQL> insert into emp values
  2  (7999,'JEAN','SALESMAN',7698,to_date('22-2-1981','dd-mm-yyyy'),1250,500,99)
 ;

1 ligne crÚÚe.

SQL> select * from dept;

    DEPTNO DNAME          LOC
---------- -------------- -------------
        99 a saisir       a saisir
        10 ACCOUNTING     NEW YORK
        20 RESEARCH       DALLAS
        30 SALES          CHICAGO
        19 sales          LA




SQL> update emp set deptno=98 where empno=7999;

1 ligne mise Ó jour.

SQL> select * from dept;

    DEPTNO DNAME          LOC
---------- -------------- -------------
        99 a saisir       a saisir
        98 a saisir       a saisir
        10 ACCOUNTING     NEW YORK
        20 RESEARCH       DALLAS
        30 SALES          CHICAGO
        19 sales          LA

6 ligne(s) sÚlectionnÚe(s).
*/


/*
Question 3
*/
create or replace trigger Modif_week_end
	before update or insert OR DELETE on emp for each row when (to_char(sysdate,'D')=6 or to_char(sysdate,'D')=7)
declare
begin
	Raise_application_error(-20201, 'repose toi du con, c est le week end');
END;
/

/*
Question 4
*/

drop table emp2 ;
drop Table logement ;


create table logement(
	loge_nom VARCHAR2(14) primary key, 
	manager VARCHAR2(14), 
	adress VARCHAR2(13));

create table emp2(
    nom     	varchar2(10) primary key,
    age        	number(5),
    loge_nom   	VARCHAR2(14) references logement);

create view Emp_Loge_Manager as select nom, e.loge_nom, l.manager
from emp2 e, logement l where e.loge_nom = l.loge_nom;

/*
trigger
*/
create or replace trigger Modif_week_end
	before update or insert OR DELETE on emp for each row when (to_char(sysdate,'D')=6 or to_char(sysdate,'D')=7)
declare
begin
	Raise_application_error(-20201, 'repose toi du con, c est le week end');
END;
/



