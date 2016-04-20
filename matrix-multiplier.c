/*
 * =============================================================================
 *
 *       Filename:  matrix-multiplier.c
 *
 *    Description:  The actual matrix multiplication happens here
 *
 *        Version:  1.0
 *        Created:  20/04/2016 18:30:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =============================================================================
 */

#include "matrix.h"

#include <stdlib.h>

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  multiply_matrices
 *  Description:  This is where the actual matrix multiplication happens
 *
 *        Input:  matrices A and B are to be multiplied. The value is stored in
 *                product matrix.
 *       Output:  If operation successful, returns EXIT_SUCCESS (0)
 * =============================================================================
 */
int multiply_matrices (Matrix* matrix_A, Matrix* matrix_B, 
                                   Matrix* product_matrix)
{
        int ac_rows, a_cols_b_rows, bc_cols;
        int ii, jj, kk;                         /* for loops */ 

        ac_rows = matrix_A->num_rows;           /* M */ 
        a_cols_b_rows = matrix_A->num_columns;  /* N */ 
        bc_cols = matrix_B->num_columns;        /* K */ 

        for (ii = 0; ii < ac_rows; ii++) {

                for (jj = 0; jj < bc_cols; jj++) {
                        /* Initialise all elements in C to 0 */
                        product_matrix->matrix[ii][jj] = 0;
                        
                        for (kk = 0; kk < a_cols_b_rows; kk++) {
                                product_matrix->matrix[ii][jj] +=
                                matrix_A->matrix[ii][kk] * 
                                matrix_B->matrix[kk][jj];
                        }
                }
        }

        return EXIT_SUCCESS;
}	/* -----  end of function multiply_matrices  ----- */

