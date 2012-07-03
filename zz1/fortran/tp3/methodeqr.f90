!----------------------------------------------
! Maxime ESCOURBIAC
! G1
! 4/12/2009
! TP3 La methode QR
!------------------------------------------------
!module incluant la methode QR
!------------------------------------------------

module methodeqr

implicit none

contains

!--------------------------------------------------
!--------------------------------------------------
!subroutine de la methode QR

subroutine qr(a,n,itermax,eps,iter)

implicit none

real(8), dimension(:,:),intent(inout)      :: a         !matrice ou l'on doit calculer les valeurs propres
real(8), dimension(:,:),allocatable        :: Q,H       !matrice temporaire de calcul
real(8), dimension(:),allocatable          :: v         !vecteur de calcul
real(8), intent(in)                        :: eps       !variable de precision
real(8)                                    :: r,s       !variable de calcul
integer,intent(in)                         :: n,itermax
integer,intent(out)                        :: iter 
integer                                    :: i,j,k,fin


allocate(Q(n,n))
allocate(H(n,n))
allocate(v(n))
iter = 0

rita: do 
   iter = iter + 1
   ! Q = In
   Q = 0.d0
   do i = 1,n
      Q(i,i) = 1.d0
   end do
  
   do k = 1, n-1
      s= sqrt(dot_product(a(k:n,k),a(k:n,k)))
	  v(k:n)= a(k:n,k)
	  v(k) = v(k) + sign(1.d0,a(k,k))*s
	  r = sqrt(dot_product(v(k:n),v(k:n)))
	  v = v/r
	  
	  do i = k,n
	     do j = k,n
		    H(i,j)=-2.d0*v(i)*v(j)
		 end do
         H(i,i)= H(i,i) + 1.d0
	  end do
	  if(k .ne. 1) then
	     H(k-1,1:n)= 0.d0
	     H(1:n,k-1)= 0.d0
	     H(k-1,k-1) = 1.d0
	  end if
	  Q= matmul(Q,H)
	  a= matmul(H,a)
	  
     enddo
	
	a= matmul(a,Q)
	
	!partie de test
	fin = 1
	bob: do i= 1,n
	   do j= 1,i-1
	      if(abs(a(i,j)) .gt. eps) then
	         fin = 0
		 exit bob
	      end if
	   end do
        end do bob
        if((fin .eq. 1) .or. (iter .gt. itermax)) then
	   exit rita
	end if

end do rita

end subroutine qr
!--------------------------------------------------
!--------------------------------------------------

end module methodeqr