BEGIN

    FOR i IN 1..10 LOOP
		IF MOD(i,2)= 0 THEN
			INSERT INTO Temp VALUES(i,100*i,RPAD(CONCAT(TO_CHAR(i),'est pair'),55));
	    ELSE
		    INSERT INTO Temp VALUES(i,100*i,RPAD(CONCAT(TO_CHAR(i),'est impair'),55));
	    END IF;
	END LOOP;
END;
/                                   