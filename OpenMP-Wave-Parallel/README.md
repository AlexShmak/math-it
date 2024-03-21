# The wave parallel algorithm 

Implementing and making experiments with parallel algorithm for solving partial differential equations (C, OpenMP).

---

### PC: Legion 5 Pro 16ACH6H
### OS: Ubuntu 22.04.4 LTS x86_64
### CPU: AMD Ryzen 7 5800H

---

- Times run per a number of threads (1,2,4,8,16): 10 

- Confidence intervals are counted for each number of threads

- Results are given in the following table

---
## Experiment

### Conditions 

- The observed problem shows the approximation of the theoretical problem of heat spreading from 100 degrees at the top border to 0 degrees at the bottom border
- The side borders are filled according to the following function:
  - $u_{i,j} = u_{i,j-1} - interval$, where $interval = 100 / net_size$
    [//]: # (- The net size is changing withing the range {100, 300, 500, 1000, 2000, 3000} )
- The net is filled with random numbers from [-100, 100]
- Block size remains consisted throughout the experiments and equals 64
### The expected result
The algorithm is expected to approximate the function so that the resulting net would represent the values gradually decreasing from 100 to 0 with the given speed (interval)

### The actual result
- The actual result meets the expectations drawn out in the expected results. The result changes dramatically when increasing _epsilon_ value. The acceptable result is reached which _epsilon = 0.001_ precision
- The efficiency of the parallel algorithm significantly decreases (run time increases) after using more than 8 threads
- The amount of iterations remains approximately consistent 

![mine_condition.png](..%2F..%2FDownloads%2Fmine_condition.png)

---

