#ifndef THREADS_H
#define THREADS_H 

#define MAX_TEST_THREADS 3 

/* function prototypes */

void create_threads(void);

void create_sems(void);

void take_sem(sem_t *psem);

void release_sem(sem_t *psem);

#endif /* THREADS_H */
