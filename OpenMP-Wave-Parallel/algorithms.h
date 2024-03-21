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
    double time_full;
    int iterations;
} result_t;

void prepare_net(net_t *net);

net_t *create_net(int size);

void consecutive_algorithm(net_t *net, result_t *res);

double process_block(net_t *net, int x, int y);

void save_result(net_t *net);

void parallel_algorithm(net_t *net, result_t *res);

void test_parallel(int times, int size, int threads_num);

#endif //OPENMP_WAVE_PARALLEL_ALGORITHMS_H
