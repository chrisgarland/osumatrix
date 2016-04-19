/*
 * =============================================================================
 *
 *       Filename:  matrix-multiplier.c
 *
 *    Description:  Implementation of a matrix multiplier. Contains main()
 *
 *        Version:  1.0
 *        Created:  18/04/2016 21:17:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * ============================================================================
 */
#include "ansi-color.h"    /*Ansi colour coding used for output to sdtout*/ 
#include "matrix.h"
#include "matrix-builder.h"

#include <stdlib.h>
#include <stdio.h>

/*#define TEST_PRINT*/

/* 
 * ===  FUNCTION  =============================================================
 *         Name:  main
 *  Description:  Wrapper for matrix multiplier. Takes a description file, 
 *                builds the data structures & multiplies the matrices
 *
 *        Input:  Matrix description file
 *       Output:  Product of two matrices
 * =============================================================================
 */
int main ( int argc, char *argv[] )
{       
        if (argc != 3) {
                perror(KWHT"\nMust enter an argument: Input file\n\n");
                printf(KNRM);
        } else {
                FILE* description_file_A = fopen(argv[1], "r"); 
                FILE* description_file_B = fopen(argv[2], "r"); 
                Matrix *matrix_A = build_matrix(description_file_A); 
                Matrix *matrix_B = build_matrix(description_file_B); 
                /*Matrix *matrix_C = multiply_matricies(matrix_A, matrix_B);*/
                
                /*#ifdef TEST_PRINT */
                        /*os200_print_matrix(matrix_A);*/
                        /*os200_print_matrix(matrix_B);*/
                        /*os200_print_matrix(matrix_C);*/
                /*#endif*/

                free(matrix_A);
                free(matrix_B);
        }
        return EXIT_SUCCESS;
}		/* ----------  end of function main  ---------- */

