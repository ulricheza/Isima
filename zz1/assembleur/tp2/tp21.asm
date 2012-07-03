        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

main    NOP
        ;utilisation des registre
        ;r0 tete de lecture de la chaine
        ;r1 tete d ecriture de la chaine
        ;r2 registre temporaire de lecture de chaine

        ;initialisation des tetes de lectures et d ecriture 
        LDR r0,=chaine
        LDR r1,=chaine
boucle:
        ;LDRB car la valeur est un char
        LDRB r2,[r0]
        ;deplacement du pointeur de lecture
        ADD r0,r0,#1
        CMP r2,#' '
        BEQ boucle
        CMP r2,#'\0'
        ;on ecrit dans la valeur pointe par r1 le contenu du registre r2
        STRB r2,[r1]
        ;deplacement du pointeur d ecriture
        ADD r1,r1,#1
        ;test de fin
        BNE boucle
        B .       

;declaration  de variable
        DATA
;declaration de la chaine de caractere
chaine DC8 "b on jour les zz1"

        END
