!----------------------------------------------
! Maxime ESCOURBIAC
! G1
! 4/12/2009
! TP3 La methode QR
!------------------------------------------------

program tp3pp

use fonction
use methodeqr

implicit none

real(8), dimension(:,:), allocatable            :: a         !matrice du systeme
real(8), dimension(:)  , allocatable            :: b         !vecteur solution
real(8)                                         :: eps       !precision souhaite
integer                                         :: n,itermax,iter,i,ichoix


print *, "nombre d'iteration max?"
read *, itermax
print *, "precision souhaite?"
read *, eps
print *,"----------choix du systeme-------------------------"
print *,"1) systeme 3x3                                     "
print *,"2) systeme 3x3                                     "
print *,"3) systeme 9x9                                     "
print *,"---------------------------------------------------"

print *,"choix?"
read *, ichoix 

select case (ichoix)
   
       case(1)
	      open(1,file='systeme1.txt',status='old',action='read')

       case(2)
	      open(1,file='systeme2.txt',status='old',action='read')

       case(3)
          open(1,file='systeme3.txt',status='old',action='read')	   

end select 

 call lect_rang(1,n)
 allocate(a(n,n))
 allocate(b(n))
 call lect_fichier(1,a,b,n)
 
 !appel de la subroutine methode QR
 
  call qr(a,n,itermax,eps,iter)
  
  call affich_mat(a,n)
  
  do i= 1,n
     b(i) = a(i,i)
   end do
   print *,"nombre d'iteration effectue",iter
   print *,"vecteur resultat"
   call affich_vect(b,n)
   
   close (1)
   
end program tp3pp
