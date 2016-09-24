/*
 * ==============================================================================
 *
 *       Filename:  thread-control.h
 *
 *    Description:  header file
 *
 *        Version:  1.0
 *        Created:  26/04/2016 14:08:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * ==============================================================================
 */

#ifndef THREADCONTRON_H
#define THREADCONTRON_H

void* consume_data (void* ptr);
void* set_subtotal (void* _matrix);
int thread_controller (Matrix* _matrix);

#endif /* ifndef THREADCONTRON_H */

