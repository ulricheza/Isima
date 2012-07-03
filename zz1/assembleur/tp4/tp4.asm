          PROGRAM SQUELETTE_TP

          EXTERN  aff_pixel

;----- Constantes --------------------------------------------------------------

;Déclarer les constantes ici


;----- Segment de données -----------------------------------------------------
          RSEG DATA_ID:DATA(2)
          DATA

;Déclarer les variables ici
          
;----- Segment de code --------------------------------------------------------------------
          RSEG CODE:CODE(2)
          CODE32

          PUBLIC main
main

          LDR     r6,=liste
          
          LDR     r0,[r6]               ;x
          ADD     r6,r6,#4
          LDR     r1,[r6]               ;y
          ADD     r6,r6,#4         
          mov     r2,#1                 ;couleur
          mov     r3,#101
          BL      carre
          LDR     r0,[r6]               ;x
          ADD     r6,r6,#4      
          mov     r2,#5                 ;couleur
          BL      carre
          LDR     r0,[r6]               ;x
          ADD     r6,r6,#4      
          mov     r2,#2                 ;couleur
          BL      carre
          LDR     r0,[r6]               ;x
          ADD     r6,r6,#4
          LDR     r1,[r6]               ;y
          ADD     r6,r6,#4               
          mov     r2,#3                 ;couleur
          BL      carre
          LDR     r0,[r6]               ;x
          ADD     r6,r6,#4    
          mov     r2,#4                 ;couleur
          BL      carre
          B       .   
          ;- Branch on C function (with interworking)

carre:
          MOV     r4,#0
          push    {lr}
          ADD     r4,r0,r3
traith:   
          push    {r0-r4}
          LDR     r5,=aff_pixel
          MOV     lr,pc
          BX      r5
          pop     {r0-r4}
          ADD     r0,r0,#1
          CMP     r0,r4
          BNE     traith
          ADD     r4,r1,r3
traitd:
          push    {r0-r4}
          LDR     r5,=aff_pixel
          MOV     lr,pc
          BX      r5
          pop     {r0-r4}
          ADD     r1,r1,#1
          CMP     r1,r4
          BNE     traitd
          SUB     r4,r0,r3
traitb:
          push    {r0-r4}
          LDR     r5,=aff_pixel
          MOV     lr,pc
          BX      r5
          pop     {r0-r4}
          SUB     r0,r0,#1
          CMP     r0,r4
          BNE     traitb
          SUB     r4,r1,r3
          SUB     r4,r4,#1
traitg:
          push    {r0-r4}
          LDR     r5,=aff_pixel
          MOV     lr,pc
          BX      r5
          pop     {r0-r4}
          SUB     r1,r1,#1
          CMP     r1,r4
          BNE     traitg          
          pop     {lr}
          BX      lr
    

;Fin du programme principal

          DATA
liste     DC32 100,100,250,400,175,175,325
         
          END ;main
          
          