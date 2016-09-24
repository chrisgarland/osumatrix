/*
 * =============================================================================
 *
 *       Filename:  util.c
 *
 *    Description:  Grneric utilities
 *
 *        Version:  1.0
 *        Created:  19/04/2016 11:42:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =============================================================================
 */

#include "../include/matrix.h"
#include "../include/ansi-color.h"

#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH    256

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  truncate_file
 *  Description:  Cuts a predetermined number of lines off the top of a file
 *
 *        Input:  input_file, number of lines to be truncated
 *       Output:  Exit status: 0 = success; non-zero = failure
 * =============================================================================
 */
int truncate_file (FILE* _input_file, int _num_lines_to_be_truncated)
{
        char buffer[MAX_LINE_LENGTH];
        int num_lines_truncated;

        num_lines_truncated = 0;

        while (num_lines_truncated < _num_lines_to_be_truncated) {
                if (fgets(buffer, MAX_LINE_LENGTH, _input_file) == NULL) {
                        exit(EXIT_FAILURE);
                }
                num_lines_truncated++;        
        }

        return EXIT_SUCCESS;
}	/* -----  end of function truncate_file  ----- */



/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  get_line
 *  Description:  Responsible for reading/returning a line from a given file
 * =============================================================================
 */
char* get_line (FILE* _input_file)
{
        char* line_buffer;
        line_buffer = malloc(MAX_LINE_LENGTH * sizeof(*line_buffer));

        if (fgets(line_buffer, MAX_LINE_LENGTH, _input_file) == NULL) {
                perror("util.h:65: Error reading from file");
                exit(EXIT_FAILURE);
        }
        return line_buffer;
}	/* -----  end of function get_line  ----- */


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  os200_print_matrix
 *  Description:  Responsible for printing a given matrix. Used for testing
 *                purposes.
 *
 *        Input:  Matrix struct pointer
 *       Output:  Properly formatted matrix
 * =============================================================================
 */
void os200_print_matrix (Matrix* _matrix)
{
        int ii, jj; /* for loops */ 

        printf(KWHT"\n");
        for (ii = 0; ii < _matrix->num_rows; ++ii) {
                for (jj = 0; jj < _matrix->num_columns; jj++) {
                        if (jj == 0) {
                                printf("[");
                        }
                        printf("%d", _matrix->matrix[ii][jj]);

                        if (jj == _matrix->num_columns - 1) {
                                printf("]\n");
                        } else {
                                printf("    ");
                        }
                }
        }
        printf("\n\n"KNRM);
}	/* -----  end of function os200_print_matrix  ----- */

