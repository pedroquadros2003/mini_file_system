#ifndef __counter_unsafe_h__
#define __counter_unsafe_h__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct counter_unsafe_stats_s {

  char *mode;
  int threads;
  int iterations;
  int expected;
  int observed;
  char *race_demo;
} counter_unsafe_stats_t;

void pt_counter_unsafe(int thread_num, int inc_goal,
                       counter_unsafe_stats_t *stats_out);

#endif
