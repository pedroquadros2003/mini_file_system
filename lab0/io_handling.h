#ifndef IO_HANDLING_H
#define IO_HANDLING_H

#include "counter_mutex.h"
#include "counter_unsafe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_inputs(int argc, char **argv);

void print_counter_unsafe_stats(counter_unsafe_stats_t *stats_out);

void print_counter_mutex_stats(counter_mutex_stats_t *stats_out);

#endif