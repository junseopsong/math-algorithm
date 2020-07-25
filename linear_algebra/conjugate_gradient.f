! ..........................................
! Conjugate gradient method for solving Ax = b
! n : Size of matrix A
! a, ia, ja : Matrix A in compressed row storage (CRS) format
! ..........................................
      subroutine conjugate_gradient_solver(n,a,ia,ja,b,x,maxiter,tol)
      use omp_lib
      implicit real*8(a-h,o-z)
      integer(4) ia(*), ja(*)
      real(kind=8) a(*), b(*), x(*), u(n), v(n), w(n)
   
!$omp parallel private(i,j,t,k)
!$omp do schedule(guided)
      do i = 1, n
         t = 0.0d0
         do j = ia(i), ia(i+1) - 1
            k = ja(j)
            t = t + a(j) * x(k)
         enddo
         u(i) = b(i) - t
      enddo
!$omp end parallel
   
      rho = 0.0d0
      alpha0 = 0.0d0
!$omp parallel private(i,j,t)
!$omp do schedule(static)
      do i = 1, n
         v(i) = u(i)
      enddo
!$omp do schedule(static), reduction(+:rho)
      do i = 1, n
         rho = rho + u(i) * u(i)
      enddo
!$omp do schedule(guided)
      do i = 1, n
         t = 0.0d0
         do j = ia(i), ia(i+1) - 1
            t = t + a(j) * v(ja(j))
         enddo
         w(i) = t
      enddo
!$omp do schedule(static), reduction(+:alpha0)
      do i = 1, n
         alpha0 = alpha0 + v(i) * w(i)
      enddo
!$omp single
      alpha = rho / alpha0
!$omp end single
!$omp do schedule(static)
      do i = 1, n
         x(i) = x(i) + alpha * v(i)
         u(i) = u(i) - alpha * w(i)      
      enddo
!$omp end parallel
      rho1 = rho
   
! ................ Start Iteration ................
      iter = 1
   11 continue
      iter = iter + 1
   
      rho = 0.0d0
      alpha0 = 0.0d0
      res = 0.0d0
!$omp parallel private(i,j,t)
!$omp do schedule(static), reduction(+:rho)
      do i = 1, n
         rho = rho + u(i) * u(i)
      enddo
   
!$omp single
      beta = rho / rho1
!$omp end single
!$omp do schedule(static)
      do i = 1, n
         v(i) = u(i) + beta * v(i)
      enddo
!$omp do schedule(guided)
      do i = 1, n
         t = 0.0d0
         do j = ia(i), ia(i+1) - 1
            t = t + a(j) * v(ja(j))
         enddo
         w(i) = t
      enddo
!$omp do schedule(static), reduction(+:alpha0)
      do i = 1, n
         alpha0 = alpha0 + v(i) * w(i)
      enddo
!$omp single
      alpha = rho / alpha0
!$omp end single
   
!$omp do schedule(static)
      do i = 1, n
         x(i) = x(i) + alpha * v(i)
         u(i) = u(i) - alpha * w(i)
      enddo
   
!$omp do schedule(static), reduction(+:res)
      do i = 1, n
         res = res + u(i) * u(i)
      enddo
!$omp end parallel
      if ( res <= tol ) go to 22
      if ( iter == maxiter ) go to 22
   
      rho1 = rho
      go to 11
! ................ End Iteration ................
   
   22 continue
      return
      end subroutine conjugate_gradient_solver