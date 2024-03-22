#include <stdio.h>
#include "algorithms.h"


int main() {
    int times = 10;
    int net_size = 400;
    int threads_num[] = {1, 2, 4, 8, 16};
    int number_of_elements = sizeof(threads_num) / sizeof(threads_num[0]);

    for (int i = 0; i < number_of_elements; i++) {
        printf("#### Threads: %d ####\n", threads_num[i]);
        test_parallel(times, net_size, threads_num[i]);
    }

    for (int i = 0; i < number_of_elements; i++) {
        printf("#### Threads: %d ####\n", threads_num[i]);
        test_parallel_mine(times, net_size, threads_num[i]);
    }

    return 0;
}
