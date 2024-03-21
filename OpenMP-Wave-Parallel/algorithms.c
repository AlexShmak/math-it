#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>
#include "algorithms.h"

#define EPS 0.001
#define BLOCK_SIZE 64
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void prepare_net(net_t *net) {
    // * filling the net
    int size = net->size;
    double **u = net->u;
    double **f = net->f;
    double h = net->h;

    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            f[i][j] = 0;
            double x = i * h;
            double y = j * h;
            if (j == 0) {
                u[i][j] = 100 - 200 * x;
            } else if (i == 0) {
                u[i][j] = 100 - 200 * y;
            } else if (j == size + 1) {
                u[i][j] = -100 + 200 * x;
            } else if (i == size + 1) {
                u[i][j] = -100 + 200 * y;
            } else {
                u[i][j] = (rand() % 201) - 100;
            }
        }
    }
}

net_t *create_net(int size) {
    net_t *net = malloc(sizeof(net_t));
    net->size = size;
    net->u = (double **) malloc((net->size + 2) * sizeof(double *));
    net->f = (double **) malloc((net->size + 2) * sizeof(double *));
    for (int i = 0; i < net->size + 2; i++) {
        net->u[i] = (double *) malloc((net->size + 2) * sizeof(double));
        net->f[i] = (double *) malloc((net->size + 2) * sizeof(double));
    }
    prepare_net(net);
    int net_space = net->size - 2;
    net->blocks_num = net_space / BLOCK_SIZE;
    if (net->blocks_num * BLOCK_SIZE != net_space) net->blocks_num += 1;
    net->h = 1.0 / (size + 3);
    return net;
}

void consecutive_algorithm(net_t *net, result_t *res) {
    double d_max, temp, dm;
    int i, j;
    int N = net->size;
    double h = net->h;
    double start = omp_get_wtime();
    do {
        res->iterations += 1;
        d_max = 0; // * max value difference
        for (i = 1; i < N + 1; i++)
            for (j = 1; j < N + 1; j++) {
                temp = net->u[i][j];
                net->u[i][j] = 0.25 * (net->u[i - 1][j] + net->u[i + 1][j] + net->u[i][j - 1] + net->u[i][j + 1] -
                                       h * h * net->f[i][j]);
                dm = fabs(temp - net->u[i][j]);
                if (d_max < dm) d_max = dm;
            }
    } while (d_max > EPS);
    double end = omp_get_wtime();
    res->time = end - start;
    res->average_time += res->time;
}

double process_block(net_t *net, int x, int y) {
    // * Evaluate block with given coordinates
    double d_max, dm, temp;
    int i, j;
    int N = net->size;
    double h = net->h;
    int x_start = 1 + x * BLOCK_SIZE;
    int x_end = MIN(x_start + BLOCK_SIZE, N + 1);
    int y_start = 1 + y * BLOCK_SIZE;
    int y_end = MIN(y_start + BLOCK_SIZE, N + 1);
    d_max = 0; // * max value difference
    for (i = x_start; i < x_end; i++)
        for (j = y_start; j < y_end; j++) {
            temp = net->u[i][j];
            net->u[i][j] = 0.25 * (net->u[i - 1][j] + net->u[i + 1][j] + net->u[i][j - 1] + net->u[i][j + 1] -
                                   h * h * net->f[i][j]);
            dm = fabs(temp - net->u[i][j]);
            if (d_max < dm) d_max = dm;
        }
    return d_max;
}

void parallel_algorithm(net_t *net, result_t *res) {
    int NB = net->blocks_num;

    double d_max;
    double *dm = calloc(NB, sizeof(*dm));
    double time_start = omp_get_wtime();
    do {
        res->iterations += 1;
        d_max = 0;
        for (int nx = 0; nx < NB; nx++) {
            dm[nx] = 0;
            int i, j;
            double d;
#pragma opm parallel for shared(nx, dm, net, NB) private(i, j, d)
            for (i = 0; i < nx + 1; i++) {
                j = nx - i;
                d = process_block(net, i, j);
                if (dm[i] < d) dm[i] = d;
            }
        }
        for (int nx = NB ; nx > -1; nx--) {
            int i, j;
            double d;
#pragma omp parallel for shared(nx, dm, net, NB) private(i, j, d) default(none)
            for (i = 0; i < nx + 1; i++) {
                j = 2 * (NB ) - nx - i;
                d = process_block(net, i, j);
                if (dm[i] < d) dm[i] = d;
            }
        }
        for (int i = 0; i < NB; i++)
            if (d_max < dm[i]) {
                d_max = dm[i];
            }
    } while (d_max > EPS);
    double time_end = omp_get_wtime();
    res->time = time_end - time_start;
    res->average_time += res->time;
}

void save_result(net_t *net) {
    char *path = "/home/alexander/math-it/OpenMP-Wave-Parallel/graph/array.txt";
    FILE *file = fopen(path, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
    }

    for (int i = 0; i < net->size + 2; i++) {
        for (int j = 0; j < net->size + 2; j++) {
            fprintf(file, "%f ", net->u[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void test_consecutive(int times, int size) {
    result_t *res = malloc(sizeof(result_t));

    // * Test Consecutive Algorithm
    printf("-------------------------\n");
    printf("|  net_t Size |    %d    |\n", size);
    printf("-------------------------\n");
    printf("|   Time    |    Iter   |\n");
    printf("-------------------------\n");
    for (int i = 0; i < times; i++) {
        net_t *net = create_net(size);
        res->time = 0;
        res->iterations = 0;
        consecutive_algorithm(net, res);
        printf("|  %f |    %d   |\n", res->time, res->iterations);
        save_result(net);
        free(net);
    }
    printf("-------------------------\n");
    printf("|        AvgTime        |\n");
    printf("-------------------------\n");
    printf("|       %f        |\n", res->average_time / times);
    printf("-------------------------\n\n");

    free(res);
}

void test_parallel(int times, int size, int threads_num) {
    result_t *res = malloc(sizeof(result_t));

    // * Test Parallel Algorithm
    printf("-------------------------\n");
    printf("|  net_t Size |    %d    |\n", size);
    printf("-------------------------\n");
    printf("|   Time    |    Iter   |\n");
    printf("-------------------------\n");
    for (int i = 0; i < times; i++) {
        net_t *net = create_net(size);
        res->time = 0;
        res->iterations = 0;
        omp_set_num_threads(threads_num);
        parallel_algorithm(net, res);
        printf("|  %f |    %d   |\n", res->time, res->iterations);
        save_result(net);
        free(net);
    }
    printf("-------------------------\n");
    printf("|        AvgTime        |\n");
    printf("-------------------------\n");
    printf("|       %f        |\n", res->average_time / times);
    printf("-------------------------\n\n");

    free(res);
}
