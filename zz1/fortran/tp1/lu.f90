program LU


!---------------------------------
!TP1: Programmation numerique 
!Factorisation LU et applications
!Sam 21 novembre 2009
!Maxime Escourbiac
!---------------------------------

use facto_lu

implicit none

!declaration des variables
real(8), dimension(:,:), allocatable :: A               !matrice A  lire dans le fichier
real(8), dimension(:,:), allocatable :: ainv            !matrice inverse de A
real(8), dimension(:), allocatable   :: b               !second membre du systeme
real(8), dimension(:), allocatable   :: x               !vecteur resultat
real(8)                              :: sdet,t,y            !pour le calcul de determinant
integer, dimension(:), allocatable   :: iperm
integer                              :: err   
integer                              :: n               !rang de la matrice A
integer                              :: ichoix = 1
integer                              :: i,j,first = 1   !indice de boucle
character(len=*),parameter           :: fmt='(5E15.8)'

!attention lire le rang de la matrice dans le programme principal


!affichage du menu
do while (ichoix .ne. 0)

   print *,"------------tp1:factorisation LU ------------------"
   print *,"                                                   "
   print *,"1) factorisation LU + resolution                   "
   print *,"2) factorisation LU seulement + determinant        "
   print *,"3) calcul de l'inverse d'une matrice               "
   print *,"4) test avec la matrice de Hilbert                 "
   print *,"0) exit                                            "
   print *,"--------------by M.Escourbiac----------------------"

   print *,"choix?"
   read *, ichoix 
   call system("clear")
   if(ichoix .eq. 0) then
      exit
   end if

   if((ichoix .ne. 4) .and. (first .eq. 1)) then
      open(1,file='systeme.txt',status='old',action='read')
      read (1,*) n
      allocate(A(n,n))
      allocate(b(n))
      allocate(iperm(n))
      allocate(x(n))
      call lect_fichier(A,b,n)
      call affich_mat(A,n)
      call affich_vect(b,n)
   end if   
   
   if((ichoix .eq. 4) .and. (first .eq. 1)) then
   !construction de la matrice de Hilbert
      open(2,file='resulat_hilbert.txt',status='replace',action='write')
      print *,"donner la dimension de la matrice de Hilbert"
      read *,n
      allocate(A(n,n))
      allocate(b(n))
      allocate(iperm(n))
      allocate(x(n))
      t=1.d0
      y=1.d0
      do i =1,n
         do j =1,n
            A(i,j) = 1.d0 /(t+y-1.d0)
            y = y+1.d0
         end do
         t = t+1.d0
      end do
   end if
   !fin de la construction de la matrice de hilbert


 
   select case (ichoix)
          case (1) 
             call facto(A,b,x,n,ichoix,sdet,err,iperm)
             print*,"factorisation LU de A"
             call affich_mat(A,n)
             print*,"vecteur resultat x"
             call affich_vect(x,n)

          case (2)
             call facto(A,b,x,n,ichoix,sdet,err,iperm)
             print*,"factorisation LU de A"
             call affich_mat(A,n) 
             call calcul_trace(A,n,sdet)

          case (3)
             allocate(ainv(n,n))
             do i = 1,n
                b = 0.d0
                b(i) = 1.d0
                call facto(A,b,x,n,ichoix,sdet,err,iperm)
                do j=1,n
                   ainv(j,i)=x(j)
                end do
             end do
             print *, "Inverse de A"
             call affich_mat(ainv,n) 

          case (4)
             allocate(ainv(n,n))
             call facto(A,b,x,n,2,sdet,err,iperm)
             do i = 1,n
                b = 0.d0
                b(i) = 1.d0
                call facto(A,b,x,n,3,sdet,err,iperm)
                do j=1,n
                   ainv(j,i)=x(j)
                end do
             end do 
             do i=1,n
                write (2,fmt) (ainv(i,j), j=1,n)
             end do
             close(2)
          case default
             print *,"au revoir"
             exit
   end select
   first = 0

end do
!---Fin partie executive du programme principal

close(1)

contains

!----------------------------------------------------------------------------------
!----------------------------------------------------------------------------------
!subroutine de lecture de matrice et du second membre

subroutine lect_fichier(A,b,n)

implicit none

!declaration des variables
real(8), dimension(:,:), intent(inout)   :: A !matrice a  lire dans le fichier
real(8), dimension(:)  , intent(inout)   :: b !second membre du systeme
integer, intent(in)                      :: n !rang de la matrice A
integer                                  :: i,j


do i=1,n
   read(1,*) (A(i,j),j= 1,n) 
end do    
   read(1,*) (b(i),i=1,n)
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

end program LU

!fin du tp