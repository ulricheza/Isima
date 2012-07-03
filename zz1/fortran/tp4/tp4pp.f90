!------------------------------------------------------------------------------
! Maxime ESCOURBIAC
! G1
! 16/01/2010
! TP4 Methode du gradient conjugue, de Fletcher-Reeves
!         Et Polak-Ribiere
!------------------------------------------------------------------------------
! Programme principal:
! gc.f90 : recherche lineaire, methode de Fletcher, methode 
!               de Polak ribiere
! fct.f90: Fonction de calcul de la fonction et de son gradient
!  fonction.f90: subroutine de lecture/affichage de matrice
!-------------------------------------------------------------------------------

program tp4pp

   use fonction
   use fct
   use gc
   
   implicit none

   !declaration de variables 
   real(8),dimension(:),allocatable  :: x,y
   integer                           :: n,i
   integer                           :: ichoix,itermax

   print *,"Nombre d'iteration maximum"
   read *, itermax
   print *,"----------choix de l'equation----------------------"
   print *,"1) f(x,y)= 100(y-x²)²+(-x)²                        "
   print *,"2) f(x,y)=(x+y)²+(2(x²+y²-1)-1/3)²                 "
   print *,"3) f3(x)                                           "
   print *,"4) f4(x)                                           "
   print *,"---------------------------------------------------"

   print *,"choix?"
   read *, ichoix 


   select case (ichoix)

   
       case(1)
	      n = 2
	      allocate(x(n))
	      allocate(y(n))
          x(1)= 0.d0
	      x(2)= 0.d0  
	      y=x
       case(2)
	      n = 2
	      allocate(x(n))
          allocate(y(n))
          x(1)= sqrt(7.d0/6.d0)
	      x(2)= 0.d0
              y=x
       case(3)
          print *, "quelle valeur de n?"
          read *, n
          allocate(x(n))
          allocate(y(n))
          x = 1.d0
          y = x
       case(4)
	      print *, "quelle valeur de n?"
          read *, n
		  n = n+1
          allocate(x(n))  !decalage car selon le poly il existe une valeur  xo jusqu'a xn.
          allocate(y(n))
		  i = 1
          do while(i .lt. n)
		     x(i)= -1.2d0
			 x(i+1)= 1.d0
			 i = i+2
		  end do
		  if(i .eq. n) x(n)=-1.2d0 
		  y = x
   end select 

   

   print *,"Fletcher-Reeves :::"
   call fletcher_reeves(x,n,ichoix,itermax)
   call affich_vect(x,n)
   print *,"Polak-Ribiere :::"
   call polak_ribiere(y,n,ichoix,itermax)
   call affich_vect(y,n)
   call system("pause") !programmation sous windows

end program tp4pp