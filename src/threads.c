 /* The idea is to create some threads and play around with semaphores  */


    /* 1. DONE: pthread_self can be mapped to neater thread_ids or names     */
    /* 2. DONE: The debugs  have to print the time in milliseconds. */
    /* 3. DONE: Debug logs have to print the thread names!!  */

    /* TODO: 
    1.  Warning removal. ;-) 
    */


 #include <stdio.h> 
 #include <stdlib.h>
 #include <unistd.h>
 #include <pthread.h>
 #include <assert.h>
 #include <assert.h>
 #include <semaphore.h>
 #include <string.h>


 #include "msm_common.h"
 #include "threads.h"

 /* globals, not statics!!  */

 pthread_t threads[MAX_TEST_THREADS];

pthread_key_t namekey; /*can have another key for another purpose. May be for bumping up and restoring priorities. Then it will be priority key.*/

 char threadnames[][MAX_THREAD_NAME_LEN] = {"main", "thread0", "thread1", "thread2"}; 

 sem_t sem;

 /* FUCNTION definitions */



 int main(void)
 {
   int i; 

   printf("starting main ...\n\r");


   //create sems first.
   create_sems();

   //create threads and they run the tests! 
   create_threads();

   //From here All our macros are good to use.

   //wait for the threads to finish. Or can have an infinite loop here.
   for (i = 0; i < MAX_TEST_THREADS ; i++)
     {
       assert(0 == pthread_join(threads[i], NULL));
     }

   EXIT;
   return 0;
 }

 void *thread0(void)
 {

   int retval = 0; 
   retval = pthread_setspecific(namekey, threadnames[1]);
   assert(0 == retval);

   ENTRY;

   take_sem(&sem);

   EXIT;
   return NULL; 
 }

 void *thread1(void)
 {

   int retval = 0; 
   retval = pthread_setspecific(namekey, threadnames[2]);
   assert(0 == retval);


   ENTRY;

   DEBUG_LOG_0("going to sleep for 5 seconds");
   sleep(5);
   release_sem(&sem);

   //DEBUG_LOG_0("going to sleep for 10 seconds");
   //  sleep(10);
   take_sem(&sem);
 //take_sem(&sem);
 // take_sem(&sem);
 //  take_sem(&sem);


   EXIT;
   return NULL; 
 }

 void *thread2(void)
 {

   int retval = 0; 
   retval = pthread_setspecific(namekey, threadnames[3]);
   assert(0 == retval);

   ENTRY;

 //take_sem(&sem);
 //take_sem(&sem);  
 // take_sem(&sem);  
 //take_sem(&sem);  
 //take_sem(&sem);  
 //take_sem(&sem);

   EXIT;
   return NULL; 
 }

 void create_threads(void)
 {
   int retval = 0; 

   /* int pthread_create(pthread_t *thread, const pthread_attr_t *attr, */
   /*   void *(*start_routine)(void*), void *arg); */

   /* int pthread_setname_np(pthread_t thread, const char *name); */

   printf("now in %s\n\r", __PRETTY_FUNCTION__);


 /* int pthread_key_create(pthread_key_t *key, void (*destr_function) (void *)); */

 /* int pthread_key_delete(pthread_key_t key); */

 /* int pthread_setspecific(pthread_key_t key, const void *pointer); */

 /* void * pthread_getspecific(pthread_key_t key); */

   retval = pthread_key_create(&namekey, NULL); 
   assert(0 == retval);

   retval = pthread_setspecific(namekey, threadnames[0]);
   assert(0 == retval);

   retval = pthread_create(&threads[0], NULL,  thread0, NULL);
   assert(0 == retval);

   retval = pthread_create(&threads[1], NULL,  thread1, NULL);
   assert(0 == retval);


   retval = pthread_create(&threads[2], NULL,  thread2, NULL);
   assert(0 == retval);

 EXIT;

   return; 
 }


 void create_sems(void)
 {
   int retval = 0; 

   /* int sem_init(sem_t *sem, int pshared, unsigned int value); */
   /* as a rule as semaphores are inited to 0 */

   printf("now in %s\n\r", __PRETTY_FUNCTION__);

   retval = sem_init(&sem, 0, 0);
   assert(0 == retval);

   return; 
 }

 void take_sem(sem_t *psem)
 {
   int retval = 0 ; 
   int semval = 0 ; 

   ENTRY;

 /* NOTE THAT sem_getvalue is not that great an implementation in linux or cygwin because it retuens 0 for any number of waiting processes/ threads.
    If you want to see a non zero value, then release it many times. Bingo. - MSM.
  */

   /* int sem_getvalue(sem_t *sem, int *sval); */
   retval = sem_getvalue(psem, &semval);
   assert(0 == retval);
   DEBUG_LOG_1("sem is now : %d", semval);
   DEBUG_LOG_0("going to lock");
   retval = sem_wait(psem);
   DEBUG_LOG_0("got the lock");
   DEBUG_LOG_1("sem is now : %d", semval);
   assert(0 == retval);

   EXIT;
   return; 
 }


 void release_sem(sem_t *psem)
 {
   int retval = 0; 
   int semval = 0 ; 

   ENTRY;

   retval = sem_getvalue(psem, &semval); 
   assert(0 == retval);

   DEBUG_LOG_1("sem is now : %d", semval);
   DEBUG_LOG_0("going to release");
   retval = sem_post(psem);
   DEBUG_LOG_0("released");
   DEBUG_LOG_1("sem is now : %d", semval);
   assert(0 == retval);

   EXIT;
   return; 
 }
