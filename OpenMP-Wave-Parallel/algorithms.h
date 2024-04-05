#ifndef OPENMP_WAVE_PARALLEL_ALGORITHMS_H
#define OPENMP_WAVE_PARALLEL_ALGORITHMS_H

typedef struct net_t {
    int size;
    double **u;
    double **f;
    int blocks_num;
    double h;
} net_t;

typedef struct result_t {
    double time;
    double avg_time;
    double avg_time_one_thread;
    int iterations;
} result_t;

typedef void (*func)(net_t *);

void prepare_net_mine_condition(net_t *net);

net_t *create_net(int size, func f);

double process_block(net_t *net, int x, int y);

void save_result(net_t *net);

void parallel_algorithm(net_t *net, result_t *res);

void test_parallel(int times, const int *size, int net_sizes, const int *threads_num, int threads_numbers);

#endif //OPENMP_WAVE_PARALLEL_ALGORITHMS_H
