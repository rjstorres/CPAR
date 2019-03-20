function OnMult(n_a, n_b)
	integer, intent(in) :: n_a
	integer, intent(in) :: n_b

	integer :: i, j, k
	real :: temp
	real :: start
	real :: finish
	!Create arrays
	real, dimension(n_a*n_a) :: a
	real, dimension(n_b*n_b) :: b
	real, dimension(n_a*n_b) :: c
	
  	!Initialize array a
	do i=1,n_a*n_a
		a(i) = 1
	end do

	!Initialize array b
	do i=0,n_b*n_b - 1
		b(i+1) = i/n_b + 1
	end do

	!Matrix Multiplication
	
    call cpu_time(start)

	do i=0,n_a - 1
		do j=0,n_b - 1
			temp = 0
			do k=0,n_a - 1
				temp = temp + a(i*n_a+k+1) * b(k*n_b+k+1)
			end do
			c(i*n_a+j+1) = temp
		end do
	end do

	! put code to test here
    call cpu_time(finish)
	print '("Time = ",f6.3," seconds.")',finish-start
	
	!Print Result Matrix
	!print *, "Result matrix: "
	!do i=1,min(n_a*n_b, 10)
	!	print *, c(i)
	!end do

 end function 

function OnMultLine(n_a, n_b)
	integer, intent(in) :: n_a
	integer, intent(in) :: n_b

	integer :: i, j, k
	real :: start, finish
	!Create arrays
	real, dimension(n_a*n_a) :: a
	real, dimension(n_b*n_b) :: b
	real, dimension(n_a*n_b) :: c
	
  	!Initialize array a
	do i=1,n_a*n_a
		a(i) = 1
	end do

	!Initialize array b
	do i=0,n_b*n_b - 1
		b(i+1) = i/n_b+1
	end do

	!Initialize array b
	do i=1,n_a*n_b
		c(i) = 0
	end do
			
	
    call cpu_time(start)
	!Matrix Multiplication
	do i=0,n_a - 1
		do k=0,n_b - 1
			do j=0,n_b - 1
				c(i*n_a+j+1) = c(i*n_a+j+1) + a(i*n_a+k+1) * b(k*n_b+j+1)
			end do
		end do
	end do

		! put code to test here
    call cpu_time(finish)
	print '("Time = ",f6.3," seconds.")',finish-start
	!Print Result Matrix
	!print *, "Result matrix: "
	!do i=1,min(n_a*n_b, 10)
	!	print *, c(i)
	!end do

end function 


program ex1
	print *, OnMultLine(1000, 1000)
	print *, OnMult(1000, 1000)
end program ex1