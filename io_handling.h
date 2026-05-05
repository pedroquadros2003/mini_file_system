#ifndef IO_HANDLING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct counter_unsafe_stats_s {
  char *mode;
  int threads;
  int iterations;
  int expected;
  int observed;
  char *race_demo;
} counter_unsafe_stats_s;

void print_inputs(int argc, char **argv) {

  printf("%d\n", argc);

  for (int i = 1; i <= argc; ++i) {

    printf("%d: %s\n", i, argv[i]);
  }
}

void print_counter_unsafe_stats(counter_unsafe_stats_s *stats_out) {

  printf("mode=unsafe\n");
  printf("threads=%d\n", stats_out->threads);
  printf("iterations=%d\n", stats_out->iterations);
  printf("expected=%d\n", stats_out->expected);
  printf("observed=%d\n", stats_out->observed);
  printf("race_demo=%s\n", stats_out->race_demo);
}

#endif