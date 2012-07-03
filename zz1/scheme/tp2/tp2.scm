!-------------------------------------------------------------------!
2ieme TP scheme:
Fonctionelle & programmation avancée                                                        
!-------------------------------------------------------------------!




;;utilisation de la fonction map
;;-------------------------------------------------------------------
;; Exercise d'initiation
;;-------------------------------------------------------------------

;;(carre_all L) retourne le carre de tous les element de liste

(define carre_all (lambda (L)
                  (if (null? L)
                      "liste vide"
                      (map (lambda (n) (* n n)) L))))

(carre_all '(1 2 3 4 5)) 

;;(double L) retourne le double de tous les elements de la liste

(define double (lambda (L)
               (if (null? L)
               "liste vide"
               (map (lambda (x) (+ x x)) L))))

(double '(1 2 3 4 5))

;;(parite L) liste des termes pairs

(define parite (lambda (L)
               (if (null? L)
               "liste vide"
               (append-map (lambda (x) (if (even? x)
                                           (list x)
                                           ()))     L))))

(parite '( 1 2 4 6 7 8))


;;-------------------------------------------------------------------
;; feuille d'exercise sur les fonctionnelles 
;;-------------------------------------------------------------------

;; programme de base existe? et quelquesoit? vues en cours

(define existe? (lambda (L P)
                        (if L
                            (or (P (car L))
                                (existe? (cdr L) P))
                         #f)))

(define quelquesoit? (lambda (L P)
                             (if L 
                                (and (P (car L))
                                     (quelquesoit? (cdr L) P))
                              #t)))



;;-------------------------------------------------------------------
;;exercise1: utilisation de schema de quantification logique
;;-------------------------------------------------------------------
1°)

;;(tous_egaux L) retourne #t si tous les elements de la liste sont egaux 2 à 2


   ;;en mode schéma universel (en utilisant quelquesoit)

   (define tous_egaux_universel (lambda (L)
                                  (if L
                                     (quelquesoit? L (lambda (x)
                                                        (= x (car L)))))))

   (tous_egaux_universel '(0 1 2 3 4))
   (tous_egaux_universel '( 1 1 1 1 1))

   ;;en mode schéma existentiel (en utilisant existe)

   (define tous_egaux_existentiel (lambda (L)
                                  (if L
                                     (not(existe? L (lambda (x)
                                                  (not(= x (car L)))))))))

   (tous_egaux_existentiel '(0 1 2 3 4))
   (tous_egaux_existentiel '(1 1 1 1 1))

;;(tous_diff L) retourne #t si tous les elements de la listes sont different 1 a 1

   ;;en mode schema existentiel

   (define tous_diff_existentiel_sp (lambda (a L)
                                    (if L
                                    (not(existe? L (lambda (x)
                                                           ( = x a))))
                                     #t)))
                                    
                                     
   (define tous_diff_existentiel (lambda (L)
                                 (if (null? L)
                                 #t
                                 (and (tous_diff_existentiel_sp (car L) (cdr L)) 
                                      (tous_diff_existentiel (cdr L))))))

   (tous_diff_existentiel '(1 2 3 4 5))
   (tous_diff_existentiel '(1 2 3 5 5))


   ;;en schema universel 

   (define tous_diff_universel_sp (lambda (a L)
                                  (if L
                                      (quelquesoit? L (lambda (x)
                                                              (not(= x a))))
                                   #t)))
   
  (define tous_diff_universel (lambda (L)
                                  (if L
                                      (and (tous_diff_universel_sp (car L) (cdr L))
                                           (tous_diff_existentiel (cdr L)))
                                      #t)))

   (tous_diff_universel '(1 2 3 4 5))
   (tous_diff_universel '(1 2 3 5 5))


;;-------------------------------------------------------------------
;; schema de recurrence simple et double
;;-------------------------------------------------------------------

   (define fonc (lambda (F u0 n n0)
                (if (= n n0)
                u0
                (F (fonc F u0 (- n 1) n0) n))))

   (fonc (lambda (x n) (+ x n))  0 5 0) ;;somme des 5 premiers entiers
   (fonc (lambda (x n) (+ x (* n n))) 0 5 0) ;;somme des carres de 1 a 5
   (fonc (lambda (x n) (* x n)) 1 5 0) ;; calcul de la factorielle de 5
   
   ; pour fibonaci (on passe par des vecteurs)

   (car (fonc (lambda (Un-1 n)
                 (list (+ (car Un-1) (cadr Un-1))(car Un-1))) '(1 1) 10 0))                      
            
  

3°)
;; (selection L P) retourne la liste des elements de L qui verifient P

   (define selection (lambda (L P)
                     (if (null? L)
                     ()
                     (if (P (car L))
                         (cons (car L) (selection (cdr L) P))
                         (selection (cdr L) P)))))

   (selection '(0 1 t 5 2 4 i) integer?)

   ;;solution prof

   (define selection2 (lambda (L P)
                      (append-map (lambda (x)
                                  (if (P x)
                                      (list x)
                                      ())) L)))


(define (implique A B)
    (or (not A) B))

;; (reflexive L P) retourne #t si tous les elements de L s'applique a P

   (define reflexive (lambda (L P)
                     (if (null? L)
                     #t
                     (and (P (car L) (car L))
                          (reflexive (cdr L) P)))))
  
   (reflexive '(1 2 3) =)
   
;;(transitive R E) retourne #t si R est transitive #f sinon (xRy = yRx)

(define transitive (lambda (L P)
		(quelquesoit? L (lambda(x)
                                (= (P  x) (P x (car L)))))))

                                                        						 

 (transitive '(1 2 3) +)     

;;(PC L n) retourne l'emsemble des n-uplets de L

(define PC (lambda (L n)
           (if (= n 1)
               (if (null? L)
               ()
               (cons (list (car L)) (PC (cdr L) n)))
               (append-map (lambda (x) 
			     (map (lambda (y) (cons x y))  
				  (PC L (- n 1)))) L))))
           

(PC '(0 1) 2) 

;;(matprod M V) effectue le produit matrice vecteur

(define matprod (lambda (M V)
                (map (lambda (x) (apply + (map * x V))) M)))

(matprod '((1 0 0) (0 1 1) (1 0 1)) '(1 2 3))

(define transpose (lambda (M)
                  (if (null? (cdr M))
                  (map list (car M))
                  (map cons (car M) (transpose (cdr M)))))))
                   
(define (transp M)
        (apply map list M))                      
                        
(transp '((0 1 0) (0 2 3) (4 5 6)))
(transpose '((0 1 0) (0 2 3) (4 5 6)))

(define trace (lambda (M)
              (if (null? M)
               0
              

;;exercise 8 Ensemble des parties d'un ensemble

(define PE (lambda (E)
           (if (null? E)
              '(())
              (let ((res (PE (cdr E))))
              (append (map (lambda (x)
                           (cons (car E) x)) res) res)))))

(PE '(1 2 3))

;;exercise 9 Partition d'un ensemble en deux parties

(define long(lambda(L)
            (if (null? L )
             0
            (+ 1 (long(cdr L))))))

(define (ajout x L)
        (list (cons (cons x (car L))
                    (cdr L))
              (list (car L)
                    (cons x (cadr L)))))
   
(ajout 1 '((2 3) (4)))

(define (PU L)
        (append-map (lambda (x)
                    (ajout (car L) x)) (PU (cdr L))))

(PU '(1 2 3))