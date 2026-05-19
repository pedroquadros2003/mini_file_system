#ifndef __counter_mutex_h__
#define __counter_mutex_h__

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SEM_COUNTER "/counter"

sem_t *get_semaphore(char *name);

sem_t *create_semaphore(char *name, unsigned int value);

void check_error(bool error, char *msg);

#define import_semaphore() sem_t *counter_sem = get_semaphore(SEM_COUNTER);

typedef struct counter_mutex_stats_s {
  char *mode;
  int threads;
  int iterations;
  int expected;
  int observed;
  char *check;
} counter_mutex_stats_t;

void pt_counter_mutex(int thread_num, int inc_goal,
                      counter_mutex_stats_t *stats_out);

#endif
