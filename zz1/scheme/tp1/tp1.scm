;; Premier Tp de scheme avec initiation a Xemacs

;; Commandes Xemacs indispensables

;; C-x 3            :: diviser verticalement l'espace de travail
;; ESC-x run-scheme :: lancer le mode scheme dans une des fenetres
;; ESC-x scheme-mode:: Lancer le mode texte pour taper le code 


;;Premiere commande scheme

(car '(1 2 3))

;;(quad x): retourne la puissance 4ieme de x

(define quad(lambda (x)
             (* x (* x (* x x)))))

(quad 2)

;;(cercle r) : retourne la liste contenant la circonference et la surface d'un cercle
;; de rayon r

(define cercle(lambda (r)
              (list (* r (* 2 3.14)) (* 3.14 (carre r)))))

(cercle 1)

;;(fact n) : retourne factorielle de n

(define fact(lambda(n)
            (if (= n 0)
                1
                (* n (fact (- n 1))))))
(fact 3)

;; (som_int n) :: retourne la somme des n entiers non nuls

(define som_int(lambda(n)
            (if (= n 1)
                1
                (+ n (som_int (- n 1))))))
(som_int 5)

;;(long L) :: retourne la longeur de la liste L

(define long(lambda(L)
            (if (null? L )
             0
            (+ 1 (long(cdr L))))))

(long '( a b c d ))

;;(miroir L) retourne la liste L inverse

(define miroir(lambda(L)
              (if (null?  (cdr L))
              L
              (list (miroir (cdr L)) (car L)))))
(miroir '(1 2 3)) 

;;(carre L) retourne la liste des carres des nombres contenus dan sla liste L

(define carre(lambda(L)
             (if (null? L)
             ()
             (cons (* (car L) (car L)) (carre (cdr L))))))
(carre '(1 2 3 4))

;;(nbpos L) retourne le nombres de nombres positif contenue dans L

(define nbpos(lambda(L)
             (if (null? L)
             0
             (if (positive? (car L))
             (+ 1 (nbpos(cdr L)))
             (nbpos (cdr L))))))

(nbpos '( 1 2 3 -3 0 -5 5))


;;(membre x L) retourne #t si la valeur x est presente dans L sinon #f
(define membre(lambda( x L)
              (if (null? L)
              #f
              (if (= x (car L))
              #t
              (membre x (cdr L))))))
(membre 4 '(1 2 3 4 5 6))
(membre 4 '(1 2 3 5 6))

;;(epure L) retourne une liste sans doublon

ma solution pas optimisé:::

(define epure(lambda (L)
             (if (null? L)
             ()
             (if (membre (car L) (cdr L))
                 (epure (cdr L))
                 (cons (car L) (epure (cdr L)))))))
             
(epure '(1 1 2 2 1 1 4 5 6 3 4)) 



              
;;(som_list L) retourne la somme des entiers d'une liste si il y en a sinon afficher un message d'erreur

(define som_list(lambda (L)
        (if (null? L)
            "erreur"
            (if (number? (car L))
            (som L)
            (som_list (cdr L))))))

(define som(lambda (L)
        (if (null? L)
        0
        (if (number? (car L))
        (+ (car L) (som (cdr L)))
        (som (cdr L))))))

(som_list '( 1 f 6 f -6 -1 d g j))
(som_list '( 1 f 6 sf f 12 ))
(som_list '( a z ojjh zlur ))

;; (nieme n L) retourne le nieme element de la liste

(define nieme(lambda (n L)
             (if (= n 1)
             (car L)
             (nieme (- n 1) (cdr L)))))

(nieme 4 '(a b c d e f ))

;;(insere n x L) retourne la liste L où si cela est possible, x est inséré
                 en nieme postion et sinon retourne L

(define insere(lambda ( n x L)
              (if (null? L)
                  (if (= n 1)
                      (list x)
                      ()
                  )
                  (if (= n 1)
                      (cons x L)
                      (cons (car L)(insere (- n 1) x (cdr L)))
                  ))))


(insere 2 'f '(s d j l m))
(insere 8 'f '(a b c))
(insere 4 'f '(a b c))

(cdr '(1))

;;(niv0 L) retourne la liste mise a plat

(define niv0(lambda (L)
            (if (null? L)
                ()
                (if (list? (car L))
                    (append (niv0 (car L)) (niv0 (cdr L)))
                    (cons (car L) (niv0 (cdr L)))
                    
                )
            )))

(niv0 '( 1 2 (1 2) 1))

;;(fibo n) calcul le nieme terme de la suite de fibonnaci

solution barbare::

(define fibo(lambda(n)
            (if (<= n 1)
            1
            (+ (fibo (- n 1)) (fibo (- n 2))))))

(fibo 6)

solution listé:

(define fibo_list(lambda(n)
                 (if (= n 1)
                     '(1 1)
                     (let ((RR (fibo_list (- n 1))))
                     (cons (+ (car RR) (cadr RR)) RR)))))
(fibo_list 1000)

solution perso:

(define fibo_max(lambda (n)
                (if (> n 2)
                (fibo_max2 1 1 (- n 1))
                "erreur")))

(define fibo_max2(lambda (u2 u1 n)
                 (if (zero? n)
                     u2
                     (fibo_max2 (+ u1 u2) u2 (- n 1)))))

(fibo_max 400)

;;(moy L) calcule ma moyenne des elements numerique de la liste 

on va utiliser une solution recussive terminale:

(define moy(lambda(L)
           (moy2 L 0 0)))


(define moy2(lambda(L R n)
        (if (null? L)
            (if (= n 0)
                "aucune valeur numerique"
                (/ R n))
            (if (number? (car L))
                (moy2 (cdr L) (+ R (car L)) (+ n 1))
                (moy2 (cdr L) R n)))))
            
(moy '(1 2 3 s d f 6))
(moy '(a b d))
                     
;;(tri_ins L) retourne la liste L triee par insertion

(define tri_ins (lambda (L)
                (if (null? L)
                    ()
                    (insert (car L) (tri_ins (cdr L))))))



(define insert (lambda (a L)
               (if (null? L)
                   (list a)
                   (if (> a (car L))
                       (cons (car L) (insert a (cdr L)))
                       (cons a L)))))
                       
                
(tri_ins '(1 6 5 4 41 5 2))

;;(tri_sel L) retourne la liste triee par selection

on va utiliser pour cela 3 fonctions:
- Une fonction qui va calculer la valeur min de la liste
- Une fonction qui va supprimer une valeur de la liste 
- Une fonction generale qui exploite les deux premiere fonctions

(define recherche_min (lambda (L)
                       (if (null? L)
                           "liste vide pas de minimum"
                           (recherche_min1 (car L) (cdr L)))))

(define recherche_min1 (lambda (m L) 
                       (if (null? L)
                        m
                       (if (< m (car L))
                           (recherche_min1 m (cdr L))
                           (recherche_min1 (car L) (cdr L))))))

test de la fonction de recherche de min

(recherche_min '( 1 2 3 4 -9 5 -10))

(define suppr_val (lambda (v L)
                  (if (null? L)
                      "la valeur est pas dans la liste"
                      (if (= v (car L))
                          (cdr L)
                          (cons (car L) (suppr_val v (cdr L)))))))

(suppr_val 4 '(1 2 3 4 5 6 7 8 9))

(define tri_sel (lambda (L) 
                (if (null? L)
                ()
                (let ((x (recherche_min L)))
                (cons x (tri_sel (suppr_val x L)))))))

(tri_sel '(1 6 -4 5 3 8))



 

        










