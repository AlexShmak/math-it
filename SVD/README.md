# Singular Value Decomposition implementation

### Three methods must have been implemented

- Primitive implementation
- Using Python standart methods
- Method with an optimization

---

> Two pictures were used in the experiments:
>
> - `luntik.bmp` : 594 $\times$ 811 (`1.4 MB`)
> - `highres.bmp` : 5304 $\times$ 7952 (`121 MB`)

| luntik    | highres   |
| --------- | --------- |
| something | something |

---

## Primitive implementation

> - Sizes after compression and time of execution:
>   - luntik:
>   - highres:

| luntik    | highres   |
| --------- | --------- |
| something | something |

---

## Standard implementation

> - Sizes after compression and time of execution:
>   - luntik:
>   - highres:

| luntik    | highres   |
| --------- | --------- |
| something | something |

---

## Random SVD (method with optimization)

> - Sizes after compression and time of execution:
>   - luntik:
>   - highres:

| luntik    | highres   |
| --------- | --------- |
| something | something |

---

### Saving middle representation

- Image data is saved in `.lol` files
- Each pictures's data file stores information about:
  - metadata about picture's width, height, N (compression factor)
  - U, S, V matrices of each color chanel of the picture
