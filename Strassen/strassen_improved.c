#include <stdlib.h>
#include "matrix.h"

void sum_matrix_blocks(float **C,
                       const size_t C_f_row,
                       const size_t C_f_col,
                       float ** A,
                       const size_t A_f_row,
                       const size_t A_f_col,
                       float ** B,
                       const size_t B_f_row,
                       const size_t B_f_col,
                       const size_t n);

void sub_matrix_blocks(float **C,
                       const size_t C_f_row,
                       const size_t C_f_col,
                       float ** A,
                       const size_t A_f_row,
                       const size_t A_f_col,
                       float ** B,
                       const size_t B_f_row,
                       const size_t B_f_col,
                       const size_t n);

void naive_aux(float **C, const size_t C_f_row, const size_t C_f_col,
               float **A, const size_t A_f_row, const size_t A_f_col,
               float **B, const size_t B_f_row, const size_t B_f_col,
               const size_t n);


void strassen_aux_improved_mar(float **C, const size_t C_f_row, const size_t C_f_col,
                  float **A, const size_t A_f_row, const size_t A_f_col,
                  float **B, const size_t B_f_row, const size_t B_f_col,
 		              float **M1,float **M2,float **M3, const size_t M_f_row, const size_t M_f_col, //added auxiliary matrices
                  const size_t n)

{
  if (n < (1<<6)) {
    naive_aux(C, C_f_row, C_f_col,
              A, A_f_row, A_f_col,
              B, B_f_row, B_f_col,
              n);
    return;
  }

  const size_t n2=n/2;

  const size_t C1X = C_f_row;
  const size_t C2X = C_f_row + n2;
  const size_t CX1 = C_f_col;
  const size_t CX2 = C_f_col + n2;

  const size_t A1X = A_f_row;
  const size_t A2X = A_f_row + n2;
  const size_t AX1 = A_f_col;
  const size_t AX2 = A_f_col + n2;

  const size_t B1X = B_f_row;
  const size_t B2X = B_f_row + n2;
  const size_t BX1 = B_f_col;
  const size_t BX2 = B_f_col + n2;

  const size_t M1X = M_f_row;
  const size_t M2X = M_f_row + n2;
  const size_t MX1 = M_f_col;
  const size_t MX2 = M_f_col + n2;


  // C11 = (P5 + P4) - P2 + P6

  // P6 = S7 x S8
  sub_matrix_blocks(C, C2X, CX2, //S7
      	            A,A1X,AX2,
      	            A,A2X,AX2,
      	            n2);

  sum_matrix_blocks(C, C1X, CX2, //S8
      	            B,B2X,BX1,
      	            B,B2X,BX2,
      	            n2);

  strassen_aux_improved_mar(M1, M1X, MX1, //P6
      	                    C, C2X, CX2, //S7
      	                    C, C1X, CX2, //S8
		                        M1,M2,M3,M2X,MX2,
        	                  n2);

  // P2 = S2 x B22
 	sum_matrix_blocks(C, C2X, CX2, //S2
 	                  A,A1X,AX1,
 	                  A,A1X,AX2,
 	                  n2);

  strassen_aux_improved_mar(C, C1X, CX2, //P2
            	              C, C2X, CX2, //S2
            	              B, B2X, BX2,
          		              M1,M2,M3,M2X,MX2,
              	            n2);

	// P5 = S5 x S6
	sum_matrix_blocks(C, C2X, CX2, //S5
                    A,A1X,AX1,
                    A,A2X,AX2,
                    n2);


  sum_matrix_blocks(C, C2X, CX1, //S6
      	            B,B1X,BX1,
      	            B,B2X,BX2,
      	            n2);

  strassen_aux_improved_mar(M2, M1X, MX2, // P5
	                          C, C2X, CX2, //S5
      	                    C, C2X, CX1, //S6
	                          M1,M2,M3,M2X,MX2,
      	                    n2);

  	// P4 = A22 x S4
  sub_matrix_blocks(C, C2X, CX2, //S4
      	            B,B2X,BX1,
      	            B,B1X,BX1,
      	            n2);

  strassen_aux_improved_mar(M3, M2X, MX1, // P4
      	                    A, A2X, AX2,
      	                    C, C2X, CX2, //S4
	                          M1,M2,M3,M2X,MX2,
      	                    n2);

  // P4 + P5
  sum_matrix_blocks(C, C1X, CX1,
  	                M2, M1X, MX2, //P5
  	                M3, M2X, MX1, //P4
  	                n2);

  // (P4 + P5) - P2
  sub_matrix_blocks(C, C1X, CX1,
                    C, C1X, CX1,
                    C, C1X, CX2, //P2
                    n2);

  // ((P4 + P5) - P2) + P6
  sum_matrix_blocks(C, C1X, CX1,
                    C, C1X, CX1,
                    M1, M1X, MX1, //P6
                    n2);



   // C12 = P1 + P2
 	 // P1 = A11 x S1
  sub_matrix_blocks(C, C2X, CX1, //S1
          	          B, B1X,BX2,
          	          B, B2X,BX2,
          	          n2);

	strassen_aux_improved_mar(C, C2X, CX2, //P1
              	            A, A1X, AX1,
              	            C, C2X, CX1, //S1
              		          M1,M2,M3,M2X,MX2,
              	            n2);

  sum_matrix_blocks(C, C1X, CX2,
                    C, C2X, CX2, //P1
                    C, C1X, CX2, //P2
                    n2);


  // C21 = P3 + P4
 	// P3 = S3 x B11

 	sum_matrix_blocks(C, C2X, CX1, //S3
                    A, A2X, AX1,
  	                A, A2X, AX2,
  	                n2);

  strassen_aux_improved_mar(M1, M1X, MX1, //P3
        	                  C, C2X, CX1, //S3
        	                  B, B1X, BX1,
		                        M1,M2,M3,M2X,MX2,
        	                  n2);


  sum_matrix_blocks(C, C2X, CX1,
                    M1, M1X, MX1, //P3
                    M3, M2X, MX1, //P4
                    n2);

  // C22 = P5 + P1 - P3 - P7
  // P1 + P5
  sum_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2, //P1
                    M2, M1X, MX2, //P5
                    n2);

  // (P5 + P1) - P3
  sub_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    M1, M1X, MX1, //P3
                    n2);

  // P7 = S9 x S10
 	sub_matrix_blocks(M1, M1X, MX1, //S9
    	              A,A1X,AX1,
        	          A,A2X,AX1,
        	          n2);

  sum_matrix_blocks(M2, M1X, MX2, //S10
      	            B,B1X,BX1,
      	            B,B1X,BX2,
      	            n2);

  strassen_aux_improved_mar(M3, M2X, MX1, //P7
                            M1, M1X, MX1, //S9
                            M2, M1X, MX2, //S10
                            M1,M2,M3,M2X,MX2,
                            n2);

  // ((P5 + P1) - P3) - P7
  sub_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    M3, M2X, MX1, //P7
                    n2);

}

void strassen_improved_mar(float **C, float **A, float **B, const size_t n)
{
  // the following three matrices are used to store the results
  float **M1 = allocate_matrix(n,n); // allocate auxiliary matrix
  float **M2 = allocate_matrix(n,n); // allocate auxiliary matrix
  float **M3 = allocate_matrix(n,n); // allocate auxiliary matrix

  strassen_aux_improved_mar(C, 0, 0, A, 0, 0, B, 0, 0, M1, M2, M3, 0, 0, n);

  deallocate_matrix(M1,n); // free auxiliary matrix
  deallocate_matrix(M2,n); // free auxiliary matrix
  deallocate_matrix(M3,n); // free auxiliary matrix

}
