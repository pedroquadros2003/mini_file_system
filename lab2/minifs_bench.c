#include "benchmark_functions.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {

  if (argc != 5) {
    printf("Invalid input: there should be only four arguments\n");
  }

  char *root = argv[1];
  int num_threads = atoi(argv[2]);
  int num_files = atoi(argv[3]);
  int num_ops = atoi(argv[4]);
  pid_t this_pid = getpid();

  benchm_stats_s stats = {.threads = num_threads,
                          .files = num_files,
                          .ops = num_ops,
                          .successes = 0,
                          .failures = 0};

  struct timespec start, end;

  // Marca o tempo de início
  clock_gettime(CLOCK_MONOTONIC, &start);

  run_threads(root, this_pid, num_threads, &stats);

  // Marca o tempo de fim
  clock_gettime(CLOCK_MONOTONIC, &end);

  // Calcula a diferença convertendo segundos e nanossegundos para milissegundos
  stats.elapsed_ms = (end.tv_sec - start.tv_sec) * 1000.0f +
                     (end.tv_nsec - start.tv_nsec) / 1000000.0f;

  // Preenche a quantidade de operações por segundo
  if (stats.elapsed_ms > 0)
    stats.ops_per_sec =
        (stats.successes + stats.failures) / (stats.elapsed_ms / 1000.0f);

  stats.check = stats.failures == 0 ? "pass" : "fail";

  print_benchmark_stats(&stats);

  return EXIT_SUCCESS;
}
