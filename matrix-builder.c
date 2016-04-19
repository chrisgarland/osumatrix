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
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =============================================================================
 */
#include "util.h"
#include "matrix.h"
#include "ansi-color.h"

#include <stdlib.h>
#include <stdio.h>

#define TEST_PRINT


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  get_matrix_dimensions
 *  Description:  Retrieves the dimensions of a matrix from the input file and 
 *                assigns the appropriate values within the Matrix struct
 *
 *        Input:  Takes a Matrix struct as input
 *       Output:  None
 *       Return:  void
 * =============================================================================
 */
void get_matrix_dimensions (FILE* _input_file, Matrix* _matrix)
{
        int scan_status;
        scan_status = fscanf(_input_file, "%dx%d", &(_matrix->num_rows),       \
                                               &(_matrix->num_columns));
        if (scan_status != 2) {
                printf(KWHT);
                perror("Error scanning matrix dimensions");
                printf(KNRM);
                exit(EXIT_FAILURE);
        }
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
        Matrix *new_matrix = malloc(sizeof(*new_matrix));

        truncate_file(_input_file, 2);   /*cuts the first 2 lines off the file*/ 
        get_matrix_dimensions(_input_file, new_matrix);

        #ifdef TEST_PRINT
                printf(KWHT"\nNumber Rows: %d\nNumber Columns: %d\n\n"KNRM, 
                                new_matrix->num_rows, new_matrix->num_columns);
        #endif

        return new_matrix;
}	/* -----  end of function build_matrix  ----- */

