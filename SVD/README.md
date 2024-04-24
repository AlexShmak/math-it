# Singular Value Decomposition implementation

### Three methods must have been implemented

- Primitive implementation
- Using Python standart methods
- Method with an optimization

---

> Two pictures were used in the experiments (Comression factor `N = 2`):

| luntik    | highres   |
| --------- | --------- |
| <img src="images/luntik.bmp" width="811"> | <img src="https://github.com/AlexShmak/math-it/assets/113236455/5a292c52-d8b6-4d9c-a8f7-7d9282b62f05)" width="811"> |

---

## Primitive implementation

| luntik    | highres   |
| --------- | --------- |
| <img src="https://github.com/AlexShmak/math-it/assets/113236455/390a7f3f-dbfd-4671-90ad-96f162adc480" width="811"> | <img src="https://github.com/AlexShmak/math-it/assets/113236455/bae11e9a-0443-4ecf-998a-234f4298afe6" width="811"> |

### Results

| luntik | highres |
| --- | --- |
| 594 $\times$ 811 | 5304 $\times$ 7952 |
| Initial size: `1.4 MB` | Initial size: `121 MB` |
| After compression: `663 KB` | After compression: `67.4 MB` |
| Execution time: `2.7 s` | Execution time: `3560 s` |

---

## Standard implementation

| luntik    | highres   |
| --------- | --------- |
| <img src="https://github.com/AlexShmak/math-it/assets/113236455/0b149cf8-c287-4c03-9868-ed365899ea84" width="811"> | <img src="https://github.com/AlexShmak/math-it/assets/113236455/9ddf3fbf-3de9-468d-aa21-784d93643e5a" width="811"> |

### Results

| luntik | highres |
| --- | --- |
| 594 $\times$ 811 | 5304 $\times$ 7952 |
| Initial size: `1.4 MB` | Initial size: `121 MB` |
| After compression: `702 KB` | After compression: `65 MB` |
| Execution time: `0.425 s` | Execution time: `380 s` |

---

## Random SVD (method with optimization)


| luntik    | highres   |
| --------- | --------- |
| ![compressed_optimized](https://github.com/AlexShmak/math-it/assets/113236455/455d2756-17c2-4db7-ab5d-9d0031039d3b) | <img src="https://github.com/AlexShmak/math-it/assets/113236455/2c12bf6e-ddc4-4b69-8685-2b7137362c23)" width="811"> |

### Results

| luntik | highres |
| --- | --- |
| 594 $\times$ 811 | 5304 $\times$ 7952 |
| Initial size: `1.4 MB` | Initial size: `121 MB` |
| After compression: `494 KB` | After compression: `65 MB` |
| Execution time: `0.118 s` | Execution time: `9.2 s` |

---

### Saving middle representation

- Image data is saved in `.lol` files
- Each pictures's data file stores information about:
  - metadata about picture's width, height, N (compression factor)
  - U, S, V matrices of each color chanel of the picture
