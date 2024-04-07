# Cubic Spline and Quadratic B-Spline implementation in Maple

## Conditions

- Both, Cubic Spline and Quadratic B-Spline, were consturcted on a segment [0,1] with a step = 0.1
- In case of the Quadratic B-Spline coeffitients were calculated using approximation functionals mentioned in [T. Lyche & K. Morken “Spline methods”](https://www.uio.no/studier/emner/matnat/ifi/nedlagte-emner/INF-MAT5340/v10/undervisningsmateriale/book.pdf)

## Experiments

The purposes of the experiments were:
- To point out the accuracy difference between the mentioned Splines implementations
- Compare them to the builtin Maple implementation of the Cubic Spline
- Conduct an accuracy test

## Cubic Spline

According to the experiments it was found out that the Cubic Splines seem to perform generally high level of approximation. However at the same time they perform the worst approximation results when approximating:
- Functions with high level of periodicity
- Discontinuous functions

---

$f(x)=cos(44*x)/2$:

| My Implementation (___green___ - function itself, ___red___ - my implementation) | Maple Standard Implementation |
|---|---|
| ![image](https://github.com/AlexShmak/math-it/assets/113236455/40c07822-8c1d-4d61-a864-292749f29ca9) | ![image](https://github.com/AlexShmak/math-it/assets/113236455/1faee3d8-cbb0-4618-af36-5218f83c3533) |


