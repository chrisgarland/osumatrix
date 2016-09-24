/*
 * =============================================================================
 *
 *       Filename:  thread-control.c
 *
 *    Description:  Same as prcess-control.c but uses threads instead. Does not 
 *                  create shared-memory blocks because (unlike processes), 
 *                  threads can access/share global variables.
 *
 *        Version:  1.0
 *        Created:  26/04/2016 12:30:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =============================================================================
 */
#include "../include/matrix.h"
#include "../include/subtotal.h"
#include "../include/ansi-color.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#define BUFFER_SIZE     1

Subtotal* stotal;
pthread_mutex_t mutex;
pthread_cond_t cond_consumer, cond_producer;
pthread_t* producer_tids;

int elements_in_buffer = 0;
int total = 0;
int NUM_ROWS;
int NUM_COLS;
int NUM_CHILDREN;





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  lock_destroy
 *  Description:  
 * =============================================================================
 */
static void lock_destroy ()
{
        pthread_cond_destroy(&cond_producer);
        pthread_cond_destroy(&cond_consumer);
        pthread_mutex_destroy(&mutex);
}	/* -----  end of function lock_destroy  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  consume_data
 *  Description:  
 * =============================================================================
 */
void* consume_data (void* ptr)
{
        ptr = NULL;
        for (int ii = 0; ii < NUM_CHILDREN; ++ii) {
                
                pthread_mutex_lock(&mutex);
                while (elements_in_buffer == 0) {
                        pthread_cond_wait(&cond_consumer, &mutex);
                }
                assert(elements_in_buffer > 0);
                total += stotal->subtotal;
                elements_in_buffer = 0;
                printf(KWHT"Subtotal produced by thread with ID %d: %d\n", 
                                          (int)stotal->id, stotal->subtotal);
                pthread_cond_signal(&cond_producer);
                pthread_mutex_unlock(&mutex);
        }
        printf("Total: %d\n"KNRM, total);
        pthread_exit(EXIT_SUCCESS);
}	/* -----  end of function consume_data  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  set_subtotal
 *  Description:  Producer function
 * =============================================================================
 */
void* set_subtotal (void* _matrix)
{
        int* array = (int*)_matrix;
        int subtotal;

        pthread_mutex_lock(&mutex);
        while (elements_in_buffer == BUFFER_SIZE) {
                pthread_cond_wait(&cond_producer, &mutex);
        }

        assert(elements_in_buffer < BUFFER_SIZE);
        subtotal = 0;       

        for (int ii = 0; ii < NUM_COLS; ++ii) {
                subtotal += array[ii];
        }
        stotal->subtotal = subtotal;
        stotal->id = (int)pthread_self();
        elements_in_buffer = 1;

        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);

        pthread_exit(EXIT_SUCCESS);
}	/* -----  end of function set_subtotal  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  start_producers
 *  Description:  
 * =============================================================================
 */
static void start_producers (Matrix* _matrix)
{
        int* array;

        /* Thread ID */
        producer_tids = malloc(NUM_CHILDREN * sizeof(*producer_tids));

        for (int ii = 0; ii < NUM_CHILDREN; ++ii) {
                array = _matrix->matrix[ii];               
                /* create attributes */
                pthread_attr_t attr;
                pthread_attr_init(&attr);

                pthread_create(&producer_tids[ii], &attr, set_subtotal, 
                                                         (void*)array);
        }
}	/* -----  end of function start_producers  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  lock_init
 *  Description:  
 * =============================================================================
 */
static void lock_init (void)
{
        pthread_mutex_init(&mutex, 0);
        pthread_cond_init(&cond_producer, 0);
        pthread_cond_init(&cond_consumer, 0);
}	/* -----  end of function lock_init  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  thread_controller
 *  Description:  
 * =============================================================================
 */
int thread_controller (Matrix* _matrix)
{
        NUM_ROWS = _matrix->num_rows;
        NUM_COLS = _matrix->num_columns;
        NUM_CHILDREN = NUM_ROWS;
        stotal = malloc(sizeof(*stotal));
        pthread_t consumer_tid;
        int ii;

        lock_init();
        start_producers(_matrix);
        /* consume data */
        pthread_create(&consumer_tid, 0, consume_data, 0);

        pthread_join(consumer_tid, 0);
        for (ii = 0; ii < NUM_CHILDREN; ++ii) {
                pthread_join(producer_tids[11], 0);
        }
        free(producer_tids);
        lock_destroy();

        return EXIT_SUCCESS;
}	/* -----  end of function thread_controller  ----- */

