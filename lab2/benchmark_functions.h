#ifndef BENHCM_H
#define BENHCM_H

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// qtd de linhas, cada linha tem uma string, escrevemos e comparamos para ver se
// é isto mesmo

typedef struct benchm_stats_s {
  int threads;
  int files;
  int ops;
  float elapsed_ms;
  int ops_per_sec;
  int successes;
  int failures;
  char *check;
} benchm_stats_s;

// Estrutura para empacotar os múltiplos argumentos da thread
typedef struct {
  char *root;
  int pid;
  int thread_id;
  benchm_stats_s *stats_ptr;
} thread_args_t;

void thread_test(char *root, int pid, int thread_id, benchm_stats_s *stats_ptr);

void run_threads(char *root, int pid, int thread_num, benchm_stats_s *stats);

void print_benchmark_stats(benchm_stats_s *stats);

#endif