!-------------------------------------------------------
!Module fonction.f90
!
!Maxime ESCOURBIAC
!ZZ1 G1
!
!Module incluant les fonctions de lecture de matrice
!et de vecteurs dans un fichier ainsi que les affichages 
!et ecriture
!--------------------------------------------------------
module fonction

implicit none

contains

!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------
!subroutine de lecture de rang de matrice dans un fichier
subroutine lect_rang(fic,n)

implicit none

integer, intent(inout)                  :: n   !rang de la matrice
integer, intent(in)                     :: fic !fichier ouvert

read (fic,*) n

end subroutine lect_rang
!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------

!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------
!subroutine de lecture de matrice et du second membre

subroutine lect_fichier(fic,A,b,n)

implicit none

!declaration des variables
real(8), dimension(:,:), intent(inout)   :: A !matrice a  lire dans le fichier
real(8), dimension(:)  , intent(inout)   :: b !second membre du systeme
integer, intent(in)                      :: n !rang de la matrice A
integer, intent(in)                      :: fic
integer                                  :: i,j


do i=1,n
   read(fic,*) (A(i,j),j= 1,n) 
end do    
   read(fic,*) (b(i),i=1,n)
close(1)
end subroutine lect_fichier
!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------


!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------
!subroutine d'affichage de matrice et de vecteur

subroutine affich_vect(A,n)

implicit none

!declaration des variables
real(8), dimension(:), intent(in) :: A !vecteur a afficher
integer, intent(in)               :: n !rang du vecteur A
integer                           :: j


print *,"vecteur:"
   print *,(A(j), j=1,n)

end subroutine affich_vect

!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------


!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------
subroutine affich_mat(A,n)

implicit none

!declaration de variables
real(8), dimension(:,:), intent(in) :: A   !matrice a afficher
integer, intent(in)                 :: n   !rang de la matrice A
integer                             :: j,i

print *,"Matrice :"
do i=1,n
   print *,(A(i,j), j=1,n)
end do

end subroutine affich_mat

!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------


!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------
subroutine calcul_trace(A,n,sdet)

implicit none

!declaration de variables
real(8), dimension(:,:),intent(in) :: A !matrice ou l'on calcule la trace
integer,intent(in)                 :: n !dimension de la matrice
real(8),intent(in)                 :: sdet ! entier pour le signe du determinant
real(8)                            :: tr!resultat
integer                            :: i !indice de boucle

tr = sdet
do i=1,n
   tr = tr * A(i,i)
end do
 
print *, "le determinant de la matrice par la factorisation LU :: ",tr
end subroutine calcul_trace

!----------------------------------------------------------------------------------
!---------------------------------------------------------------------------------- 

end module fonction