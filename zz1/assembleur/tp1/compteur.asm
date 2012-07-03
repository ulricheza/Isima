          PROGRAM SQUELETTE_TP

;----- Constantes --------------------------------------------------------------

;Déclarer les constantes ici


;----- Segment de donnes -----------------------------------------------------
          RSEG DATA_ID:DATA(2)
          DATA

;Déclarer les variables ici
          DATA
X DC32 1,2,3,4,5,6,7,8,9,10
N DC32 10


          
;----- Segment de code --------------------------------------------------------------------
          RSEG CODE:CODE(2)
          CODE32

          PUBLIC main
main
          
;Fin du programme principal
          LDR r0,=X
          LDR r1,N
          MOV r2,#0
          CMP r1,#0
          BEQ FinBoucle
Boucle:
          SUBS r1,r1,#1
          LDR r3,[r0]
          ADD r2,r2,r3
          ADD r0,r0,#4
          BNE Boucle
FinBoucle:
          

          END ;main
          