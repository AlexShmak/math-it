# Cubic Spline and Quadratic B-Spline implementation in Maple

## Conditions

- Both, Cubic Spline and Quadratic B-Spline, were consturcted on a segment [0,1] with a step = 0.1
- In case of the Quadratic B-Spline coeffitients were calculated using approximation functionals mentioned in [T. Lyche & K. Morken “Spline methods”](https://www.uio.no/studier/emner/matnat/ifi/nedlagte-emner/INF-MAT5340/v10/undervisningsmateriale/book.pdf)

## Experiments

The purposes of the experiments were:
- To point out the accuracy difference between the mentioned Splines implementations
- Compare them to the builtin Maple implementation of the Cubic Spline
- Conduct an accuracy test

## Experiments Results

According to the experiments it was found out that the Cubic Splines and B-Splines seem to perform generally high level of approximation. However at the same time they perform the worst approximation results when approximating:
- Functions with high level of periodicity
- Discontinuous functions

---

$f(x)=cos(44*x)/2$:

| My Implementation of Cubic Spline (___GREEN___ - function itself, ___RED___ - my implementation) | My Implementation of B-Spline (___GREEN___ - function itself, ___RED___ - my implementation) | Maple Standard Implementation of Cubic Spline |
|---|---|---|
| ![image](https://github.com/AlexShmak/math-it/assets/113236455/40c07822-8c1d-4d61-a864-292749f29ca9) | ![image](https://github.com/AlexShmak/math-it/assets/113236455/013b2762-2fb3-41bf-9864-ceb4e8b1357f) | ![image](https://github.com/AlexShmak/math-it/assets/113236455/1faee3d8-cbb0-4618-af36-5218f83c3533) |

---

$f(x)=x-floor(x-0.5)$

| My Implementation of Cubic Spline (___GREEN___ - function itself, ___RED___ - my implementation) | My Implementation of B-Spline (___GREEN___ - function itself, ___RED___ - my implementation) | Maple Standard Implementation of Cubic Spline |
|---|---|---|
| ![image](https://github.com/AlexShmak/math-it/assets/113236455/5bf779fb-1854-441b-a1e9-dab5291d366a) | ![image](https://github.com/AlexShmak/math-it/assets/113236455/a2e3021c-ee9f-4e51-b246-601ec04c03e1) | ![image](https://github.com/AlexShmak/math-it/assets/113236455/72491b1c-182a-412b-a206-f3357845aa68) |

---
The experiments resultst are similarly achieved and pointed out in the following articles:
- [Quadratic B-Spline curve interpolation](https://core.ac.uk/reader/82327690)
- [A very accurate method to approximate discontinuous functions
with a finite number of discontinuities](https://arxiv.org/ftp/arxiv/papers/1601/1601.05132.pdf)

### Approximation deviation test
Experiments were conducted with calculating the largest deviation in approximation on the observed segment. In the test the actual function and the approximanted function were compared to each other. The results of the tests are given in the codefiles.

