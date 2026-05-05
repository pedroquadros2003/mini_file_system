#ifndef __rwlock_h__
#define __rwlock_h__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct counter_rwlock_stats_s {
  char *mode;
  int readers;
  int writers;
  int iterations;
  int final_value;
  int read_errors;
  char *check;
} counter_rwlock_stats_t;

#endif
