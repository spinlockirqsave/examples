/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on June 16, 2013, 4:43 PM
 */

/******************************************************************************
 * consumer producer problem. There is a std::stack of tasks to be done,
 * we create two worker threads to do this job and one watcher who waits on
 * conditional variable for the threads to signal empty container
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syscall.h>

#include <stack>

#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
typedef boost::mt19937 RNGType;

#define NUM_THREADS  3
#define TCOUNT 200
#define COUNT_LIMIT 0

int     count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshod_cv;

struct thread_data
{
   thread_data(int numberOfTasks) : numberOfTasks_(numberOfTasks), done_(false) {
      RNGType rng;
      boost::uniform_real<> zero_to_hundred( 0, 100 );
      boost::variate_generator< RNGType, boost::uniform_real<> >
                    dice(rng, zero_to_hundred);

       for(int i=0; i<numberOfTasks_; ++i) {
           jobToBeDone.push(dice());
       }
   }
   int	numberOfTasks_;
   std::stack<double> jobToBeDone;
   bool done_;
};

void* inc_count(void* threadarg) {
    fprintf( stderr,"Starting inc_count(): thread %ld\n", syscall( SYS_gettid));
    int i;
    struct thread_data* data;
    data = (thread_data*) threadarg;
sleep(1);
    for (i = 0; i < TCOUNT; i++) {
        pthread_mutex_lock(&count_mutex);
        if( data->done_) {
            pthread_mutex_unlock(&count_mutex);
            break;
        }
        if (!data->jobToBeDone.empty()) {
            // do the Job
            double task = data->jobToBeDone.top();
            data->jobToBeDone.pop();
            fprintf( stderr, "inc_count(): thread %ld, popped element = %f  Job done. ",
                    syscall(SYS_gettid), task);
        }
        /* 
        Check the condition and signal waiting thread when condition is
        reached.  Note that this occurs while mutex is locked. 
         */
        if (data->jobToBeDone.empty()) {
            data->done_ = true;
            pthread_cond_signal(&count_threshod_cv);
            fprintf( stderr, "Just sent signal.\n");
            fprintf( stderr, "inc_count(): thread %ld, stack size = %lu, unlocking mutex\n",
                syscall(SYS_gettid), data->jobToBeDone.size());
        pthread_mutex_unlock(&count_mutex);
            break;
        }
        
        fprintf( stderr, "inc_count(): thread %ld, stack size = %lu, unlocking mutex\n",
                syscall(SYS_gettid), data->jobToBeDone.size());
        pthread_mutex_unlock(&count_mutex);

        /* Do some work so threads can alternate on mutex lock */
        //sleep(1);
    }
    pthread_exit(NULL);
}

void* watch_count(void* threadarg) {
  struct thread_data* data;
  data = (thread_data*) threadarg;
  
  double task = data->jobToBeDone.top();
  long unsigned int stackSize = data->jobToBeDone.size();

  fprintf( stderr,"Starting watch_count(): thread %ld\n", syscall(SYS_gettid));

  /*
  Lock mutex and wait for signal.  Note that the pthread_cond_wait routine
  will automatically and atomically unlock mutex while it waits. 
  Also, note that if COUNT_LIMIT is reached before this routine is run by
  the waiting thread, the loop will be skipped to prevent pthread_cond_wait
  from never returning.
  */
  pthread_mutex_lock(&count_mutex);
  //while (count < COUNT_LIMIT) {
    fprintf( stderr, "watch_count(): thread %ld stack size= %lu. Going into wait...\n", syscall(SYS_gettid), stackSize);
    pthread_cond_wait(&count_threshod_cv, &count_mutex);
    fprintf( stderr, "watch_count(): thread %ld Condition signal received. stack size= %lu\n", syscall(SYS_gettid), data->jobToBeDone.size());
    fprintf( stderr, "watch_count(): thread %ld Updating the value of stack...\n", syscall(SYS_gettid));
//    for(int i=0; i<10; ++i) {
//           data->jobToBeDone.push(47);
//       }
    fprintf( stderr, "watch_count(): maybe later. Thank you very much.\n", syscall(SYS_gettid));
    fprintf( stderr, "watch_count(): thread %ld stack size now = %lu.\n", syscall(SYS_gettid), data->jobToBeDone.size());
    //}
  fprintf( stderr, "watch_count(): thread %ld Unlocking mutex.\n", syscall(SYS_gettid));
  pthread_mutex_unlock(&count_mutex);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  int i, rc; 
  long t1=1, t2=2, t3=3;
  pthread_t threads[3];
  pthread_attr_t attr;
  
  thread_data data(150);
  //data.numberOfTasks_ = 30;

  /* Initialize mutex and condition variable objects */
  pthread_mutex_init(&count_mutex, NULL);
  pthread_cond_init (&count_threshod_cv, NULL);

  /* For portability, explicitly create threads in a joinable state */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[1], &attr, inc_count, (void *) &data);
  pthread_create(&threads[0], &attr, watch_count, (void *) &data);
//  pthread_create(&threads[1], &attr, inc_count, (void *) &data);
  pthread_create(&threads[2], &attr, inc_count, (void *) &data);

  /* Wait for all threads to complete */
  for (i = 1; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  
  fprintf( stderr, "Main(): Waited and joined with %d threads. Final size of stack with tasks = %lu. Done.\n", 
          NUM_THREADS, data.jobToBeDone.size());

  /* Clean up and exit */
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&count_mutex);
  pthread_cond_destroy(&count_threshod_cv);
  pthread_exit (NULL);

}

