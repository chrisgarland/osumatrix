/*
 * =====================================================================================
 *
 *       Filename:  matrix-builder.h
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  19/04/2016 18:31:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>

void get_matrix_dimensions (FILE* _input_file, Matrix* _matrix);

Matrix* build_matrix (FILE* _input_file);

