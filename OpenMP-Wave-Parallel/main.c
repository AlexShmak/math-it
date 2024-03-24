#include <stdio.h>
#include "algorithms.h"


int main() {
    int times = 10;
    int net_size[] = {100, 300, 500, 1000, 2000};
    int net_sizes = sizeof (net_size) / sizeof (net_size[0]);
    int threads_num[] = {1, 2, 4, 8, 16};
    int threads_numbers = sizeof(threads_num) / sizeof(threads_num[0]);
    printf("N  - net size\nTN - threads number\nAT - average time\nCI - confidence interval\nA  - acceleration\n\n");
    test_parallel(times, net_size, net_sizes, threads_num, threads_numbers);



    return 0;
}
