/*
 * ==============================================================================
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
 * ==============================================================================
 */
#include "ansi-color.h"    /*Ansi colour coding used for output to sdtout*/ 
#include "matrix.h"
#include "matrix-builder.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>

#define TEST_PRINT

/* Global variables only used for freeing resources */
FILE* description_file_A;
FILE* description_file_B;
Matrix* matrix_A;
Matrix* matrix_B;


/* 
 * ===  FUNCTION  ===============================================================
 *         Name:  cleanup_resources
 *  Description:  Close all files and free all previously allocated heap memory
 * ==============================================================================
 */
void cleanup_resources ()
{
        fclose(description_file_A);
        fclose(description_file_B);
        free(matrix_A);
        free(matrix_B);
}	/* -----  end of function cleanup_resources  ----- */


/* 
 * ===  FUNCTION  ===============================================================
 *         Name:  main
 *  Description:  Wrapper for matrix multiplier. Takes a description file, 
 *                builds the data structures & multiplies the matrices
 *
 *        Input:  Matrix description file
 *       Output:  Product of two matrices
 * ==============================================================================
 */
int main ( int argc, char *argv[] )
{       
        if (argc != 3) {
                perror(KWHT"\nMust enter 2 arguments: Input/Output files\n\n");
                printf(KNRM);
        } else {
                description_file_A = fopen(argv[1], "r"); 
                description_file_B = fopen(argv[2], "r"); 
                matrix_A = build_matrix(description_file_A); 
                matrix_B = build_matrix(description_file_B);
                
                #ifdef TEST_PRINT 
                        os200_print_matrix(matrix_A);
                        os200_print_matrix(matrix_B);
                        /*os200_print_matrix(matrix_C);*/
                #endif

                cleanup_resources();
        }
        return EXIT_SUCCESS;
}		/* ----------  end of function main  ---------- */

