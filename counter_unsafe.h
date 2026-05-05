#ifndef __counter_unsafe_h__
#define  __counter_unsafe_h__

#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

char *unsafe_1 = "unsafe";
char *done_1 = "done";

typedef struct counter_unsafe_stats_s {
	
	char *mode;
	int threads;
	int iterations;
	int expected;
	int observed;
	char *race_demo;
} counter_unsafe_stats_t;

static long int counter_unsafe = 0;

static void *increment_task(void *inc_goal)
{
	for(int i = 0; i < *(int *)inc_goal; ++i)
		counter_unsafe += 1;
	return NULL;
}

static void pt_counter_unsafe( int thread_num, int inc_goal, counter_unsafe_stats_t *stats_out)
{
	if(thread_num < 1)
		return;
	pthread_t *thread_vec = malloc(thread_num*sizeof(pthread_t));

	for(int i = 0; i<thread_num; ++i)
	{
		pthread_create( &(thread_vec[i]), NULL, increment_task, &inc_goal);
	}

	for(int i = 0; i < thread_num; ++i)
	{
		pthread_join(thread_vec[i], NULL);
	}

	stats_out->mode = unsafe_1;
	stats_out->threads = thread_num;
	stats_out->iterations = inc_goal;
	stats_out->expected = thread_num*inc_goal;
	stats_out->observed = counter_unsafe;
	stats_out->race_demo = done_1;

	free(thread_vec);
}

#endif
