module facto_lu


!----------------------------------
!TP1: Programmation numerique 
!Factorisation LU et applications
!Sam 21 novembre 2009
!Maxime Escourbiac
!----------------------------------
!Module de factorisation LU et de
!resolution de systeme triangulaire
!----------------------------------

implicit none

contains

	subroutine facto(a,b,x,n,ichoix,sdet,err,iperm)
	
	implicit none
	!declaration de variable
	real(8),dimension(:,:),intent(inout)  :: a      !Matrice a factoriser
	real(8),dimension(:)  ,intent(in)     :: b      !second membre
	real(8),dimension(:)  ,intent(inout)  :: x      !vecteur resultat
	real(8),intent(out)                   :: sdet   !compte le nombre d'inversion pour le determinant
        integer,intent(in)                    :: n      !rang de la matrice
	integer,intent(in)                    :: ichoix !choix de l'utilsateur,
	integer,intent(out)                   :: err    !booleen indiquant la stabilité numerique
	real(8),dimension(n)                  :: temp   !vecteur e stockage pour la permutation
	integer,dimension(:),intent(inout)    :: iperm  !vecteur de stockage des permutations
	integer,dimension(1)                  :: ip     !stockage du pivot partiel
	integer                               :: i,j,k  !entier pour les boucles
	
	!initialisation des variables pour la subroutine
	sdet = 1.d0
	err = 0
	iperm = (/ (i,i=1,n) /)
	!partie de la subroutine qui permet de factoriser A=LU
        if(ichoix .ne. 3) then
           do j=1,n
	      do i=1,j
	         a(i,j) = a(i,j)-dot_product(a(i,1:j-1),a(1:i-1,j))
              end do

	      do i=j+1,n
	         a(i,j) = a(i,j)-dot_product(a(i,1:j-1),a(1:j-1,j))
              end do
	
              ip = maxloc(abs(a(j:n,j))) +(j-1)
	      
              if(ip(1) .ne. j) then
                 temp= a(j,1:n)
                 a(j,1:n)=a(ip(1),1:n)
	         a(ip(1),1:n)=temp
                 k = iperm(j)	
       	         iperm(j)=ip(1)
	         iperm(ip(1))= k
	         sdet=-sdet
	      end if
		  
              if(abs(a(j,j)) .lt. 1.d-12) then
                 err = j
	         return
              end if
	   
              a(j+1:n,j)=a(j+1:n,j)/a(j,j)
		     
	   end do
        end if
   !partie sur la resolution du systeme LUx =Pb
        if((ichoix .eq. 1) .or. (ichoix .eq. 3)) then
   
   !resolution du systeme Ly = Pb
           x = b(iperm)
           do i=2,n
	      x(i)=(x(i)-dot_product(a(i,1:i-1),x(1:i-1)))
           end do
	
   !resolution du systeme Ux = y
           x(n)=x(n)/a(n,n)

           do i=n-1,1,-1
              x(i)=(x(i)-dot_product(a(i,i+1:n),x(i+1:n)))/a(i,i)
           end do
	
        end if


   end subroutine facto



end module facto_lu