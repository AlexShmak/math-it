#include <stdio.h>
#include "algorithms.h"


int main() {
    int times = 1;
    int net_size = 100;
//    int threads_num[] = {1, 2, 4, 8, 16};
    int threads_num[] = {8};
    int number_of_elements = sizeof(threads_num) / sizeof(threads_num[0]);
    printf("#### Consecutive Algorithm ####\n");
//    test_consecutive(times, net_size);
    for (int i = 0; i < number_of_elements; i++) {
        printf("#### Parallel Algorithm | Threads: %d ####\n", threads_num[i]);
        test_parallel(times, net_size, threads_num[i]);
    }

    return 0;
}
