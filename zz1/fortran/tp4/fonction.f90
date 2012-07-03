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




end module fonction