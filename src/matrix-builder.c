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
#include "../include/util.h"
#include "../include/matrix.h"
#include "../include/ansi-color.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*#define TEST_PRINT*/



/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  allocate_matrix
 *  Description:  Allocate heap memory for the 2D array located within the 
 *                matrix struct
 * =============================================================================
 */
void allocate_matrix (Matrix* _matrix)
{
        int num_rows, num_columns;
        int ii; /* for loop */ 

        num_rows = _matrix->num_rows;
        num_columns = _matrix->num_columns;
        _matrix->matrix = malloc(num_rows * sizeof(int*));
        
        for (ii = 0; ii < num_rows; ++ii) {
                _matrix->matrix[ii] = malloc(num_columns * sizeof(int));
        } 

}	/* -----  end of function allocate_matrix  ----- */


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  build_c
 *  Description:  Responsible for building and returning the product matrix C.
 *                The values inside the matrix wil not yet be assigned.
 *
 *        Input:  Received from commandline
 *       Return:  Malloc'd matrix
 * =============================================================================
 */
Matrix* build_c (int _num_rows, int _num_cols)
{
        Matrix* new_matrix;
        new_matrix = malloc(sizeof(*new_matrix));
        
        new_matrix->num_rows = _num_rows;
        new_matrix->num_columns = _num_cols;

        allocate_matrix(new_matrix);

        return new_matrix;
}	/* -----  end of function build_c  ----- */


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  setup_matrix
 *  Description:  Responsible for allocating the 2D array and read/writing the 
 *                values from file to the newly allocated array
 *
 *        Input:  input file, matrix pointer
 *       Return:  void
 * =============================================================================
 */
void setup_matrix (FILE* _input_file, Matrix* _matrix)
{
        char *token, *delimiters;
        char *line_buffer;
        int ii, jj; /* for loops */ 

        delimiters = " \n\t ";

        allocate_matrix(_matrix);

        for (ii = 0; ii < _matrix->num_rows; ++ii) {
                line_buffer = get_line(_input_file);
                token = strtok(line_buffer, delimiters);
                
                for (jj = 0; jj < _matrix->num_columns; jj++) {
                        _matrix->matrix[ii][jj] = atoi(token);
                        token = strtok(NULL, delimiters);
                }
        }
        free(line_buffer);
        
}	/* -----  end of function setup_matrix  ----- */


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  build_matrix
 *  Description:  Wrapper for the actual construction of a matrix. Uses 2D array
 *
 *        Input:  Matrix description file
 *       Output:  2 dimentional array representation of a matrix
 * =============================================================================
 */
Matrix* build_matrix (FILE* _input_file, int _num_rows, int _num_cols)
{
        Matrix* new_matrix;
        new_matrix = malloc(sizeof(*new_matrix));
        
        new_matrix->num_rows = _num_rows;
        new_matrix->num_columns = _num_cols;

        truncate_file(_input_file, 2);   /*cuts the first 2 lines off the file*/ 
        setup_matrix(_input_file, new_matrix);

        #ifdef TEST_PRINT
                printf(KWHT"\nNumber Rows: %d\nNumber Columns: %d\n\n"KNRM, 
                                new_matrix->num_rows, new_matrix->num_columns);
        #endif

        return new_matrix;
}	/* -----  end of function build_matrix  ----- */

