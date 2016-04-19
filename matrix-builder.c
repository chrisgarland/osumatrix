/*
 * =============================================================================
 *
 *       Filename:  matrix-builder.c
 *
 *    Description:  Inplemtation of a matrix builder using a 2D array
 *
 *        Version:  1.0
 *        Created:  19/04/2016 10:29:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =============================================================================
 */
#include "util.h"
#include "matrix.h"

#include <stdlib.h>



/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  get_matrix_dimensions
 *  Description:  
 * =============================================================================
 */
void get_matrix_dimensions (int *num_rows, int *num_colums)
{
        j
}	/* -----  end of function get_matrix_dimensions  ----- */


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  build_matrix
 *  Description:  Wrapper for the actual construction of a matrix. Uses 2D array
 *
 *        Input:  Matrix description file
 *       Output:  2 dimentional array representation of a matrix
 * =============================================================================
 */
Matrix* build_matrix (FILE* _input_file)
{
        Matrix *new_matrix;

        truncate_file(_input_file, 2);   /*cuts the first 2 lines off the file*/ 
        get_matrix_dimensions(_input_file, new_matrix);

        return new_matrix;
}	/* -----  end of function build_matrix  ----- */

