/*
 * =============================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  type definition for a matrix
 *
 *        Version:  1.0
 *        Created:  19/04/2016 15:32:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =============================================================================
 */
#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
        int num_rows;
        int num_columns;
        int **matrix;
} Matrix;

#endif /* ifndef MATRIX_H */

