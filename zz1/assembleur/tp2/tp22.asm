        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

main    NOP
        ;utilisation des registres
        ;r0 variable I
        ;r1 variable J
        ;r2 variable Cpt
        ;r3 variable S
        ;r4 contenue de tab(I)
        ;r5 contenue de tab(J)
        ;initialisation des variables
        LDR r0,=tab  ;I=adresse du tableau
        LDR r2,N     ;Cpt = N
        SUB r2,r2,#1 ;Cpt = N-1
BoucleP:
        CMP r2,#0    ;if Cpt == 0
        BEQ End
        MOV r3,r2    ;S = Cpt
        MOV r1,r0    ;J = I
BoucleS:
        CMP r2,#0    ;if Cpt == 0
        BEQ FinBP
        ADD r1,r1,#4 ;incrementataion de J
        SUB r2,r2,#1 ;Cpt--
        LDR r4,[r0]  ;On charge dans r4, tab[i]
        LDR r5,[r1]  ;on charge dans r5, tab[j]
        CMP r4,r5
        BLS BoucleS
        STR r5,[r0]  ;echange de tab(i) et tab(j)
        STR r4,[r1]
        B BoucleS
FinBP:
        ADD r0,r0,#4 ;incrementation de I
        MOV r2,r3    ;on recharge Cpt
        SUB r2,r2,#1 ;Cpt--
        B BoucleP
End:
        B.
        DATA
;tableau a trier        
tab DC32 6,3,8,5,2,1,3,7,8,5,6,10 
;nombre d elements dans le tableau
N DC32 12
        
        END
