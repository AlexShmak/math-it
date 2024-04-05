#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>
#include "algorithms.h"

#define EPS 0.001
#define BLOCK_SIZE 64
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void prepare_net_mine_condition(net_t *net) {
    // * filling the net
    int size = net->size;
    double **u = net->u;
    double **f = net->f;

    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            f[i][j] = 0;
            //! Mine condition
            double interval = 100.0 / (size + 2);
            if (j == 0) {
                u[i][j] = 100;
            } else if (i == 0 || i == size + 1) {
                if (j < 100) u[i][j] = u[i][j - 1] - interval;
            } else if (j == size + 1) {
                u[i][j] = 0;
            } else {
                u[i][j] = (rand() % 201) - 100;
            }
        }
    }
}

void prepare_net_book_condition(net_t *net) {
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

            //! Book condition
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

net_t *create_net(int size, func f) {
    net_t *net = malloc(sizeof(net_t));
    net->size = size;
    net->u = (double **) malloc((net->size + 2) * sizeof(double *));
    net->f = (double **) malloc((net->size + 2) * sizeof(double *));
    for (int i = 0; i < net->size + 2; i++) {
        net->u[i] = (double *) malloc((net->size + 2) * sizeof(double));
        net->f[i] = (double *) malloc((net->size + 2) * sizeof(double));
    }
    f(net);
    int net_space = net->size - 2;
    net->blocks_num = net_space / BLOCK_SIZE;
    if (net->blocks_num * BLOCK_SIZE != net_space) net->blocks_num += 1;
    net->h = 1.0 / (size + 3);
    return net;
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
#pragma omp parallel for shared(nx, dm, net, NB) private(i, j, d) default(none)
            for (i = 0; i < nx + 1; i++) {
                j = nx - i;
                d = process_block(net, i, j);
                if (dm[i] < d) dm[i] = d;
            }
        }
        for (int nx = NB; nx > -1; nx--) {
            int i, j;
            double d;
#pragma omp parallel for shared(nx, dm, net, NB) private(i, j, d) default(none)
            for (i = 0; i < nx + 1; i++) {
                j = 2 * (NB) - nx - i;
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
    res->avg_time += res->time;
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

void test_parallel(int times, const int *size, int net_sizes, const int *threads_num, int threads_numbers) {
    result_t *res = malloc(sizeof(result_t));
    double time[times];
    func method[] = {prepare_net_book_condition, prepare_net_mine_condition};

//    // * Test Parallel Algorithm (Book Condition)
    for (int f = 0; f < 2; f++) {
        if (f == 0) {
            printf("#### Book Condition ####\n\n");
        } else { printf("#### My Condition ####\n\n"); }
        for (int i = 0; i < net_sizes; i++) {
            for (int j = 0; j < threads_numbers; j++) {
                for (int k = 0; k < times; k++) {
                    net_t *net = create_net(size[i], method[f]);
                    res->time = 0;
                    res->iterations = 0;
                    omp_set_num_threads(threads_num[j]);
                    parallel_algorithm(net, res);
                    time[k] = res->time;
                    res->avg_time += time[k];
                    save_result(net);
                    free(net);
                }
                res->avg_time = res->avg_time / times;
                if (threads_num[j] == 1) res->avg_time_one_thread = res->avg_time;

                // * Confidence interval
                double sum_book = 0;
                for (int n = 0; n < times; n++) {
                    sum_book += (pow((time[n] - res->avg_time), 2));
                }
                double standard_deviation_book = sqrt(sum_book / times);
                double error_limit_book = 1.96 * standard_deviation_book / sqrt(times);

                printf("N: %4.d | TN: %2.d | AT: %4.4f | CI: [ %4.4f ; %4.4f ] | A: %.3f\n",
                       size[i], threads_num[j], res->avg_time, res->avg_time - error_limit_book,
                       res->avg_time + error_limit_book, res->avg_time_one_thread / res->avg_time);
            }
            printf("\n");
        }
        printf("\n");
    }
    free(res);
}