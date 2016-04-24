/*
 * =============================================================================
 *
 *       Filename:  process-control.c
 *
 *    Description:  Responsible for generating child prosesses and
 *
 *        Version:  1.0
 *        Created:  24/04/2016 10:00:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CHRIS GARLAND (15560955), c.garland@student.curtin.edu.au
 *   Organization:  
 *
 * =============================================================================
 */
#include "subtotal.h"
#include "os-semaphore.h"
#include "matrix.h"
#include "ansi-color.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define PS_OUTPUT

#define SEM_BLOCK_NAME  "/SEMBLOCK"
#define SUB_BLOCK_NAME  "/SUBBLOCK"
#define SNAME_MUTEX     "/MUTEX"
#define SNAME_EMPTY     "/EMPTY"
#define SNAME_FULL      "/FULL"

Subtotal* stotal_s;
Semaphore* semaphore;





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  free_resources
 *  Description:  deallocate/unlink resources
 * =============================================================================
 */
static void free_resources ()
{
        shm_unlink(SUB_BLOCK_NAME);
        sem_close(semaphore->mutex);
        sem_close(semaphore->empty);
        sem_close(semaphore->full);
        sem_unlink(SNAME_MUTEX);
        sem_unlink(SNAME_EMPTY);
        sem_unlink(SNAME_FULL);
}	/* -----  end of function free_resources  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  consume_data
 *  Description:  sums the subtotals produced by child processes
 * =============================================================================
 */
static int consume_data (int n)
{
        int total = 0;
        printf("\n");
        while (n > 0) {
                sem_wait(semaphore->full);
                sem_wait(semaphore->mutex);

                printf(KWHT"Subtotal produced by process with ID %d: %d\n"KNRM, 
                                            stotal_s->pid, stotal_s->subtotal);
                total += stotal_s->subtotal;

                sem_post(semaphore->mutex);
                sem_post(semaphore->empty);
                --n;
        }
        return total;
}	/* -----  end of function consume_data  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  set_subtotal
 *  Description:  Calculates and returns the sum of a matrix row
 * =============================================================================
 */
static int get_subtotal (int* _matrix, int num_cols)
{
        int subtotal;
        subtotal = 0;

        for (int ii = 0; ii < num_cols; ++ii) {
                subtotal += _matrix[ii];
        }

        return subtotal;
}	/* -----  end of function set_subtotal  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  start_children
 *  Description:  fork() child/producer processes
 * =============================================================================
 */
static void start_children (pid_t* pids, Matrix* _matrix)
{
        const int NUM_CHILDREN = _matrix->num_rows;
        const int NUM_COLS = _matrix->num_columns;

        for (int ii = 0; ii < NUM_CHILDREN; ++ii) {
                if ((pids[ii] = fork()) < 0) {
                        perror("fork() failed");
                        abort();
                } else if (pids[ii] == 0) { /*child process*/ 
                        sem_wait(semaphore->empty);
                        sem_wait(semaphore->mutex);

                        stotal_s->subtotal = get_subtotal(_matrix->matrix[ii], 
                                                                    NUM_COLS);
                        stotal_s->pid = (int)getpid();

                        sem_post(semaphore->mutex);
                        sem_post(semaphore->full);
                        exit(EXIT_SUCCESS);
                }
        }

}	/* -----  end of function start_children  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  os200_sem_init
 *  Description:  Responsible for initialising the semaphore values
 * =============================================================================
 */
static void os200_sem_init (Semaphore* _sem)
{
        if ((_sem->mutex = sem_open(SNAME_MUTEX, O_CREAT, 0644, 1)) == 
                                                         SEM_FAILED) {
                perror("Semaphore initialisation");
                exit(EXIT_FAILURE);
        }
        if ((_sem->empty = sem_open(SNAME_EMPTY, O_CREAT, 0644, 1)) == 
                                                         SEM_FAILED) {
                perror("Semaphore initialisation");
                exit(EXIT_FAILURE);
        }
        if ((_sem->full = sem_open(SNAME_FULL, O_CREAT, 0644, 0)) == 
                                                         SEM_FAILED) {
                perror("Semaphore initialisation");
                exit(EXIT_FAILURE);
        }
}	/* -----  end of function os200_sem_init  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  build_shared_objects
 *  Description:  Responsible for mapping Subtotal* and Semaphore* to shared 
 *                memory.
 * =============================================================================
 */
static void build_shared_objects()
{
        stotal_s = malloc(sizeof(*stotal_s));
        semaphore = malloc(sizeof(*semaphore));

        int subtotal_fd = shm_open(SUB_BLOCK_NAME, O_CREAT | O_RDWR, 0666);
        int semaphore_fd = shm_open(SEM_BLOCK_NAME, O_CREAT | O_RDWR, 0666);

        ftruncate(subtotal_fd, sizeof(*stotal_s));
        ftruncate(semaphore_fd, sizeof(*semaphore));

        stotal_s = (Subtotal*)mmap(0, sizeof(*stotal_s), PROT_READ | PROT_WRITE,
                                                                     MAP_SHARED,
                                                                subtotal_fd, 0);
        semaphore = (Semaphore*)mmap(0, sizeof(*semaphore), PROT_READ | 
                                                             PROT_WRITE, 
                                                             MAP_SHARED,
                                                       semaphore_fd, 0);
}	/* -----  end of function build_shared_objects  ----- */





/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  process_controller
 *  Description:  Acts as the parent prosess. All calls to fork() are done here.
 *                Responsible for process management.
 *
 *        Input:  Takes the product matrix (as a Matrix struct) to be summed. 
 *                numRows and cols are also retrieved from Matrix struct.
 *       Return:  EXIT_STATUS
 * =============================================================================
 */
int process_controller (Matrix* _matrix)
{
        const int NUM_ROWS = _matrix->num_rows;
        const int NUM_CHILDREN = NUM_ROWS;

        int total;
        pid_t pids[NUM_CHILDREN];

        build_shared_objects();
        os200_sem_init(semaphore);
        start_children(pids, _matrix);
        #ifdef PS_OUTPUT
                system("ps > psout");
        #endif
        total = consume_data(NUM_CHILDREN);

        free_resources();

        printf(KWHT"Total: %d\n\n"KNRM, total);

        return EXIT_SUCCESS;
}	/* -----  end of function process_controller  ----- */

