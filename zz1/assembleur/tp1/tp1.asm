        NAME    main
        
        PUBLIC  __iar_program_start
;declaration des variables       
Cste    EQU 4
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

main    NOP
;----code du programme ----
;utilisation de variable directe
        MOV r1,#0012h
        MOV r0,#12
;utilisation de constantes
        LDR r2,=Cste
        ADD r0,r0,r2
;utilisation de variable        
        LDR r3,X
        ADD r0,r0,r3
;utilisation de pointeur
;on charge dans r4 la valeur de l adresse de X contenue dans PY 
        LDR r4,PY
;les crochets servent a chercher la valeur dans le bloc memoire de valeur r4
        LDR r5,[r4]
        ADDS r0,r0,r4
;on stocke le contenu de le registre r0 dans la variable SOM 
        STR r0,SOM
        LDR r6,SOM
;on est alle chercher le 4ieme element du tableau
        STR r0,TAB + 4
        LDR r7,TAB + 4
        B .
;---- sous programme ----

       DATA
;Declaration des variables
X DC32 3
;declaration d un pointeur Y qui pointe sur la variable X
PY DC32 X
SOM DC32 0
;declaration d un tableau
TAB DS32 4
        END