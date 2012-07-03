!----------------------------------------------
! Maxime ESCOURBIAC
! G1
! 4/12/2009
! TP2 Methodes iteratives de solution
! de systeme lineaire
!------------------------------------------------
!Module incluant les subroutines de la
! Methode de Jacobi
! Methode de Gauss-Seidel
! Methode de relaxation
!------------------------------------------------

Module iteration

implicit none

contains

!-------------------------------------------------
!-------------------------------------------------
!subroutine de la methode de jacobi

subroutine jacobi(A,b,x1,eps,n,iter,itermax)

implicit none

real(8),dimension(:,:),intent(in)   :: A       !matrice du systeme
real(8),dimension(:),intent(in)     :: b       !second membre du systeme
real(8),dimension(:),intent(inout)  :: x1      !vecteur solution
real(8),dimension(:),allocatable    :: x2      !vecteur temporaraire de calcul
real(8),intent(in)                  :: eps     ! estimation de l'erreur 
real(8)                             :: err     ! erreur relative
real(8)                             :: s2,s1   !variable temporaire de calcul de l'erreur
integer, intent(in)                 :: n       !rang de la matrice
integer, intent(in)                 :: itermax !Nombre d'iteration a ne pas depasser
integer, intent(out)                :: iter    !Nombre d'iteration pour la resolution du systeme
integer                             :: i       !indice de boucle

allocate(x2(n))
iter = 0
x1= 0.d0

Maxou: do
      s1= 0.d0
	  s2= 0.d0
	  iter = iter+1
	  do i= 1,n
	     x2(i)=(b(i)-dot_product(A(i,1:n),x1)+A(i,i)*x1(i))/A(i,i)
		 s1= s1+(x1(i)-x2(i))**2
		 s2= s2+x2(i)**2
	  end do
	  err= sqrt(s1/s2)
	  x1=x2
	  if((err<eps) .or. (iter>itermax)) then 
	     exit Maxou
      endif
enddo Maxou

end subroutine jacobi

!-------------------------------------------------
!-------------------------------------------------

!-------------------------------------------------
!-------------------------------------------------
!subroutine de la relaxation et gauss-seidel

subroutine gaussrelax(A,b,x,w,eps,n,iter,itermax)

implicit none

real(8),dimension(:,:),intent(in)   :: A       !matrice du systeme
real(8),dimension(:),intent(in)     :: b       !second membre du systeme
real(8),dimension(:),intent(inout)  :: x       !vecteur solution
real(8),intent(in)                  :: eps     ! estimation de l'erreur
real(8),intent(in)                  :: w       !coeffficient de sur-relaxation ou sous-relaxation 
real(8)                             :: err     ! erreur relative
real(8)                             :: s       !variable temopraire de calcul
real(8)                             :: s2,s1,z !variable temporaire de calcul de l'erreur
integer, intent(in)                 :: n       !rang de la matrice
integer, intent(in)                 :: itermax !Nombre d'iteration a ne pas depasser
integer, intent(out)                :: iter    !Nombre d'iteration pour la resolution du systeme
integer                             :: i       !indice de boucle

iter = 0
x = 0.d0

John: do
      iter = iter + 1
	  s1= 0.d0
	  s2= 0.d0
	  do i= 1,n
	     z = x(i)
		 s =(b(i)-dot_product(A(i,1:n),x)+A(i,i)*x(i))/A(i,i)
		 x(i)=(1.d0 - w)*x(i) + w*s
		 s1 = s1 +(x(i) -z)**2
		 s2 = s2 + x(i)**2
	  enddo
	  
	  err= sqrt(s1/s2)
	  if((err<eps) .or. (iter>itermax)) then 
	     exit John
      endif
enddo John

end subroutine gaussrelax


!-------------------------------------------------
!-------------------------------------------------	  

end module iteration