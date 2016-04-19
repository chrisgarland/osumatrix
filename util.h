/*
 * =============================================================================
 *
 *       Filename:  util.h
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
#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

#define MAX_LINE_LENGTH    80

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  truncate_file
 *  Description:  Cuts the first two lines off a file
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

#endif /* ifndef UTIL_H */

