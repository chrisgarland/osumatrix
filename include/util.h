/*
 * ==============================================================================
 *
 *       Filename:  util.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/04/2016 13:18:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * ==============================================================================
 */

#ifndef UTIL_H
#define UTIL_H

#include "matrix.h"

#include <stdio.h>

int truncate_file (FILE* _input_file, int _num_lines_to_be_truncated);

char* get_line (FILE* _input_file);

void os200_print_matrix (Matrix* _matrix);

#endif /* ifndef UTIL_H */

