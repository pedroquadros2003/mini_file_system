#include "io_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counter_unsafe.h"

int main(int argc, char **argv) {

  print_inputs(argc, argv);

  if (argc != 5) {
    printf("Invalid input: there should be only four arguments\n");
  }

  char *program2execute = argv[1];
  char *counter_mode = argv[2];

  if (!strcmp(program2execute, "counter") && !strcmp(counter_mode, "unsafe")) {
    printf("Running counter unsafe...\n\n");

    counter_unsafe_stats_s stats_out;

    stats_out.mode = counter_mode;
    stats_out.threads = atoi(argv[3]);
    stats_out.iterations = atoi(argv[4]);

    print_counter_unsafe_stats(&stats_out);

  } else if (!strcmp(program2execute, "counter") &&
             !strcmp(counter_mode, "mutex")) {
    printf("Running counter mutex...\n\n");

    counter_unsafe_stats_s stats_out;

    stats_out.mode = counter_mode;
    stats_out.threads = atoi(argv[3]);
    stats_out.iterations = atoi(argv[4]);

  } else if (!strcmp(program2execute, "rwlock")) {
    printf("Running rwlock...\n\n");

    char *mode = argv[1];

    int num_readers = atoi(argv[2]);

    int num_writers = atoi(argv[3]);

    int num_iterations = atoi(argv[4]);

  } else {
    printf("Invalid input\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
