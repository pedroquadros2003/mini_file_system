#include "benchmark_functions.h"

void thread_test(char *root, int pid, int thread_id,
                 benchm_stats_s *stats_ptr) {

  for (int i = 0; i < stats_ptr->ops; ++i) {
    char file_path[256];

    // Constrói o nome do arquivo de forma segura
    snprintf(file_path, sizeof(file_path), "%s/bench_%d_%d_%d.dat", root, pid,
             thread_id, i % stats_ptr->files);

    int fd = open(file_path, O_RDWR | O_CREAT, 0644);

    if (fd == -1) {
      perror("Erro ao criar o arquivo");
    }

    char write_buffer[256];

    snprintf(write_buffer, sizeof(write_buffer), "this_is_operation%d", i);

    size_t word_len = strlen(write_buffer);

    // 1. Escreve no descritor de arquivo
    if (write(fd, write_buffer, word_len) == -1) {
      perror("Erro ao escrever no arquivo");
    }

    // 2. Reposiciona o cursor para o início (0) do arquivo
    lseek(fd, 0, SEEK_SET);

    // 3. Lê o conteúdo de volta. {0} garante que a string termine com caractere
    // nulo
    char read_buffer[256] = {0};
    if (read(fd, read_buffer, word_len) == -1) {
      perror("Erro ao ler do arquivo");
    }

    if (strcmp(write_buffer, read_buffer) != 0)
      __sync_fetch_and_add(&stats_ptr->failures, 1);
    else
      __sync_fetch_and_add(&stats_ptr->successes, 1);

    // 4. Fechar o arquivo para não causar vazamento de descritores
    close(fd);
  }
}

static void *test_task(void *args) {
  thread_args_t *t_args = (thread_args_t *)args;

  // Executa a função do benchmark com os argumentos desempacotados
  thread_test(t_args->root, t_args->pid, t_args->thread_id, t_args->stats_ptr);

  return NULL;
}

void run_threads(char *root, int pid, int thread_num, benchm_stats_s *stats) {
  if (thread_num < 1)
    return;

  pthread_t *thread_vec = (pthread_t *)malloc(thread_num * sizeof(pthread_t));
  // Aloca um array de argumentos, um exclusivo para cada thread
  thread_args_t *args_vec =
      (thread_args_t *)malloc(thread_num * sizeof(thread_args_t));

  for (int i = 0; i < thread_num; ++i) {
    args_vec[i].root = root;
    args_vec[i].pid = pid;
    args_vec[i].thread_id = i;
    args_vec[i].stats_ptr = stats;
    pthread_create(&(thread_vec[i]), NULL, test_task, &(args_vec[i]));
  }

  for (int i = 0; i < thread_num; ++i) {
    pthread_join(thread_vec[i], NULL);
  }

  free(thread_vec);
  free(args_vec);
}

void print_benchmark_stats(benchm_stats_s *stats) {
  printf("\n\n____________ Beginning of Results ____________\n");
  printf("threads=%d\n", stats->threads);
  printf("files=%d\n", stats->files);
  printf("ops=%d\n", stats->ops);
  printf("elapsed_ms=%f\n", stats->elapsed_ms);
  printf("ops_per_sec=%d\n", stats->ops_per_sec);
  printf("successes=%d\n", stats->successes);
  printf("failures=%d\n", stats->failures);
  printf("check=%s\n", stats->check);
  printf("________________ End of Results ______________\n\n");
}