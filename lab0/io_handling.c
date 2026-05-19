#include "io_handling.h"
#include <stdio.h>

void print_inputs(int argc, char **argv) {

  printf("%d\n", argc);

  for (int i = 1; i < argc; ++i) {

    printf("%d: %s\n", i, argv[i]);
  }
}

void print_counter_unsafe_stats(counter_unsafe_stats_t *stats_out) {

  printf("mode=unsafe\n");
  printf("threads=%d\n", stats_out->threads);
  printf("iterations=%d\n", stats_out->iterations);
  printf("expected=%d\n", stats_out->expected);
  printf("observed=%d\n", stats_out->observed);
  printf("race_demo=%s\n", stats_out->race_demo);
}

void print_counter_mutex_stats(counter_mutex_stats_t *stats_out) {

  printf("mode=mutex\n");
  printf("threads=%d\n", stats_out->threads);
  printf("iterations=%d\n", stats_out->iterations);
  printf("expected=%d\n", stats_out->expected);
  printf("observed=%d\n", stats_out->observed);
  printf("check=%s\n", stats_out->check);
}