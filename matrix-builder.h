/*
 * ==============================================================================
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
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * ==============================================================================
 */
#ifndef MATRIX_BUILDER_H
#define MATRIX_BUILDER_H

#include <stdio.h>

void allocate_matrix (Matrix* _matrix);

void setup_matrix (FILE* _input_file, Matrix* _matrix);

void get_matrix_dimensions (FILE* _input_file, Matrix* _matrix);

Matrix* build_matrix (FILE* _input_file);

#endif /* ifndef MATRIX_BUILDER_H */

