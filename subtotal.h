/*
 * ==============================================================================
 *
 *       Filename:  subtotal.h
 *
 *    Description:  type definition for a subtotal struct
 *
 *        Version:  1.0
 *        Created:  22/04/2016 17:20:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * ==============================================================================
 */
#ifndef SUBTOTAL_H
#define SUBTOTAL_H

#include <sys/types.h>

typedef struct {
        pid_t pid;
        int subtotal;
}Subtotal;

#endif /* ifndef SUBTOTAL_H */

