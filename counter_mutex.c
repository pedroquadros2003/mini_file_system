
#include "counter_mutex.h"
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

char *mutex_1 = "mutex";
char *check_1 = "pass";

static long int counter_mutex = 0;

static void *increment_task(void *inc_goal);

sem_t *get_semaphore(char *name) {
  sem_t *sem = sem_open(name, O_RDWR);
  check_error(sem == SEM_FAILED, name);
  return sem;
}

sem_t *create_semaphore(char *name, unsigned int value) {
  sem_t *sem = sem_open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, value);
  check_error(sem == SEM_FAILED, name);
  return sem;
}

void check_error(bool error, char *msg) {
  if (error) {
    printf("errno: %d\n", errno);
    perror(msg);
    exit(EXIT_FAILURE);
  }
}

static void *increment_task(void *inc_goal) {
  import_semaphore();

  for (int i = 0; i < *(int *)inc_goal; ++i) {
    sem_wait(counter_sem);

    counter_mutex += 1;

    sem_post(counter_sem);
  }
  return NULL;
}

void pt_counter_mutex(int thread_num, int inc_goal,
                      counter_mutex_stats_t *stats_out) {
  if (thread_num < 1)
    return;

  pthread_t *thread_vec = (pthread_t *)malloc(thread_num * sizeof(pthread_t));

  create_semaphore(SEM_COUNTER, 1);

  for (int i = 0; i < thread_num; ++i) {
    pthread_create(&(thread_vec[i]), NULL, increment_task, &inc_goal);
  }

  for (int i = 0; i < thread_num; ++i) {
    pthread_join(thread_vec[i], NULL);
  }

  stats_out->mode = mutex_1;
  stats_out->threads = thread_num;
  stats_out->iterations = inc_goal;
  stats_out->expected = thread_num * inc_goal;
  stats_out->observed = counter_mutex;
  stats_out->check = check_1;

  free(thread_vec);
}
