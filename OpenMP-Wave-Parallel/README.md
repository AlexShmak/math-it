# The wave parallel algorithm 

Implementing and making experiments with parallel algorithm for solving partial differential equations (C, OpenMP).

---

## Working machine

-  PC: Legion 5 Pro 16ACH6H
-  OS: Ubuntu 22.04.4 LTS x86_64
-  CPU: AMD Ryzen 7 5800H

---

## General experiments' conditions

- ___Times___ run per a number of threads: $10$ 
- ___Confidence intervals___ are counted for each number of threads in both experiments
- Executed with ___-O3 optimization___
- The ___net size___ is changing withing the range {100, 300, 500, 1000, 2000} 
- The ___number of threads___ is changing within the range {1, 2, 4, 8, 16}
- The ___net___ is filled with random numbers from [-100, 100]
- $Block\_size = 64$
- $epsilon = 0.001$

---

## Book problem reproduction

### Conditions

- Dirichlet problem parallel solution
- Boundary value problems are given in the following picture

<details>
<summary>Boundary value problems</summary>

![Screenshot from 2024-03-24 19-42-24](https://github.com/AlexShmak/math-it/assets/113236455/87330112-b2ff-4fb0-8dc2-83b2613ab2c4)

</details>

 

### Result


The results given in the book could not be reproduced in terms of execution time and acceleration, however the similar tendency is clear to notice.
- The calculation results are given in the following [table](https://docs.google.com/spreadsheets/d/1B8UMsyFEmXLN1PIc9MqrMURixblv_F2LvgiZPTIZZMI/edit?usp=sharing)

<details>
<summary>Graph</summary>

![Screenshot from 2024-03-24 19-50-40](https://github.com/AlexShmak/math-it/assets/113236455/02fd47b5-b9ae-4314-9b78-16e854ca83f6)

</details>

## Experiment (Personally chosen conditions) 

This exact experiment was chosen in order to have a better and simpler visualisation of the result of the algorithm because of the easy-to-predict expected output. Such a choice was made so that more precise output could be achieved and different conditions' effect on the algorithm work would be easier to explore.

### Conditions 

- The observed problem shows the approximation of the theoretical problem of heat spreading from 100 degrees at the top border to 0 degrees at the bottom border of a solid material 
- The side borders are filled according to the following function:
  - $u_{i,j} = u_{i,j-1} - interval$, where $interval = 100 / net\_size$

### The expected result
The algorithm is expected to approximate the function so that the resulting net would represent the values gradually decreasing from 100 to 0 with the given speed (interval). The efficiency is expected to rise in in accordance with the number of threads used.

### The actual result
- The actual result meets the expectations drawn out in the expected results. The result changes dramatically when increasing $epsilon$ value. The acceptable result is reached starting from $epsilon = 0.001$ precision
- The efficiency of the algorithm gradually increases when using more threads
- The calculations are given in the following [table](https://docs.google.com/spreadsheets/d/1B8UMsyFEmXLN1PIc9MqrMURixblv_F2LvgiZPTIZZMI/edit?usp=sharing)


<details>
<summary>Graph</summary>

![mine_condition](https://github.com/AlexShmak/math-it/assets/113236455/c9525619-32ea-45fb-a212-6f9910c428a3)

</details>

---

