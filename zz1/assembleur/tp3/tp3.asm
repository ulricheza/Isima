        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

;construction du programme principal
main    NOP
        MOV r0,#1
        LDR r1,=liste
        LDR r2,M
        LDR r3,cle
        BL genelist
        LDR r0,=liste  ;on recupere N et l adresse de tab
        LDR r1,M
        ADD r1,r1,#1 
        BL TriSelect
        LDR r0,=adresse
        LDR r3,=chaine
        BL TransAddChar 
        B.

;debut des sous programmes
;fonction de tri par selection(N,tab)
        ;utilisation des registres
        ;r0 variable I
        ;r1 variable Cpt
        ;r2 variable J
        ;r3 variable S
        ;r4 contenue de tab(I)
        ;r5 contenue de tab(J)
TriSelect:
        push{lr}
BoucleP:
        CMP r1,#1    ;if Cpt == 1
        BEQ End
        MOV r3,r1    ;S = Cpt
        MOV r2,r0    ;J = I
BoucleS:
        CMP r1,#1    ;if Cpt == 1
        BEQ FinBP
        ADD r2,r2,#4 ;incrementataion de J
        SUB r1,r1,#1 ;Cpt--
        LDR r4,[r0]  ;On charge dans r4, tab[i]
        LDR r5,[r2]  ;on charge dans r5, tab[j]
        CMP r4,r5
        BLS BoucleS
        STR r5,[r0]  ;echange de tab(i) et tab(j)
        STR r4,[r2]
        B BoucleS
FinBP:
        ADD r0,r0,#4 ;incrementation de I
        MOV r1,r3    ;on recharge Cpt
        SUB r1,r1,#1 ;Cpt--
        B BoucleP
End:
        pop{lr}
        BX lr
   
;Transformation d une adresse en chaine de caractere
;utilisation des registres:
; r0 : add
; r1 : caractere hexa
; r2 : variables de decalage
; r3 : pointeur sur chaine
; r5 : registre temporaire de sortie de l adresse
TransAddChar:
        ;init variable
        push {lr}
        MOV r2,#28
        LDR r5,[r0]
Conv:
        CMP r2,#0
        BLT FinConv
        MOV r1,r5,LSR r2
        AND r1,r1,#1111b
        CMP r1, #9
        ADDLS r1, r1, #'0'
        ADDHI r1, r1, #'A'-10
        STRB r1,[r3]
        ADD r3,r3,#1
        SUB r2,r2,#4
        B Conv
FinConv:
        pop{lr}
        BX lr
;fin TransAddChar

;generation d une liste aleatoire de chiffre
;utilisation des registre
; r0 : chiffre a inserer
; r1 : pointeur sur la liste a creer
; r2 : nombre d element a inserer
; r3 : valeur de la cle

genelist:
        push {lr}
generation:
        CMP r2,#1
        BEQ fingene
        MUL r0,r3,r0
        ADD r0,r0,#1
        STR r0,[r1]
        ADD r1,r1,#4
        SUB r2,r2,#1
        B   generation
fingene:
        pop {lr}
        BX lr
        
;fin des sous programmes



;declaration des variables
        DATA
M       DC32 50
cle     DC32 134775813
adresse DC32 0x1234ABCD
chaine  DS8 8
liste   DS32 50

        END