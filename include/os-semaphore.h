/*
 * =============================================================================
 *
 *       Filename:  os-semaphore.h
 *
 *    Description:  semaphore implementation
 *
 *        Version:  1.0
 *        Created:  23/04/2016 23:42:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =============================================================================
 */

#ifndef OSSEMAPHORE_H
#define OSSEMAPHORE_H

#include <semaphore.h>

typedef struct {
        sem_t* mutex;
        sem_t* empty;
        sem_t* full;
}Semaphore;

#endif /* ifndef OSSEMAPHORE_H */

