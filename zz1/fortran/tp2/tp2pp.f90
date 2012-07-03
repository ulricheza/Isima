!----------------------------------------------
! Maxime ESCOURBIAC
! G1
! 4/12/2009
! TP2 Methodes iteratives de solution
! de systeme lineaire
!------------------------------------------------
!Programme principal
!Appel des fonctions jacobi,gauss-seidel,relaxation
!------------------------------------------------

program tp2pp

use fonction
use iteration

implicit none

!declaration des variables
real(8),dimension(:,:),allocatable   :: A       !matrice du systeme
real(8),dimension(:),allocatable     :: b       !second membre du systeme
real(8),dimension(:),allocatable     :: x       !vecteur solution
real(8)                              :: eps     ! estimation de l'erreur 
real(8)                              :: w       ! coefficient de surrelaxation
integer                              :: n       !rang de la matrice
integer                              :: iter    !nombre d'iteration effectué
integer                              :: itermax !Nombre d'iteration a ne pas depasser
integer                              :: ichoix  !entier pour le choix de la fonction
integer                              :: compt

print *, "nombre d'iteration max?"
read *, itermax
print *, "precision souhaite?"
read *, eps
print *,"----------choix du systeme-------------------------"
print *,"1) systeme 4x4                                     "
print *,"2) systeme 9x9                                     "
print *,"---------------------------------------------------"

print *,"choix?"
read *, ichoix 
if(ichoix .eq. 1) then
   open(1,file='systeme.txt',status='old',action='read')
else
   open(1,file='systeme2.txt',status='old',action='read')
endif

 call lect_rang(1,n)
!allocation des vecteurs matrices
allocate(A(n,n))
allocate(b(n))
allocate(x(n))


print *,"------------tp2:Methode Iterative------------------"
print *,"                                                   "
print *,"1) Resolution du systeme avec Jacobi               "
print *,"2) Resolution du systeme avec Gauss-Seidel         "
print *,"3) Resolution du systeme avec la Relaxation        "
print *,"   avec variation du coeff de relaxation           "
print *,"0) exit                                            "
print *,"--------------by M.Escourbiac----------------------"

print *,"choix?"
read *, ichoix 

 call lect_fichier(1,A,b,n)
 call affich_mat(A,n)
 call affich_vect(b,n)

select case (ichoix)

      case(1)
         call jacobi(A,b,x,eps,n,iter,itermax)
         print *, "nombre d'iterations effectuees = ",iter
	 call affich_vect(x,n)
	
      case(2)
	 call gaussrelax(A,b,x,1.d0,eps,n,iter,itermax)
         print *, "nombre d'iterations effectuees = ",iter
	 call affich_vect(x,n)
	
      case(3)
         w = 0.1d0
         do compt=1,19	
	    call gaussrelax(A,b,x,w,eps,n,iter,itermax)
            print *, "------------------------------------------------------"
            print *, "Pour w=",w
            print *, "nombre d'iterations effectuees = ",iter
	    call affich_vect(x,n)
            w = w + 0.1d0
         end do
      case default 
	 print *, " au revoir"
end select

 close(1)


end program tp2pp