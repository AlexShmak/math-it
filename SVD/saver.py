"""
    ------
    meta-information:
    ------
    WIDTH: 2 bytes
    HEIGHT: 2 bytes
    N: 2 bytes
    ------
    For each color channel consquently:
    ------
    U: byte per value (length of U == HEIGHT)
    SIGMA: byte per value (length of SIGMA == N)
    V: byte per value (length of V == N)
"""

import os
import numpy as np

""" Function to create meta-information """
def create(path, width, height, n):
    meta = [
        width.to_bytes(2, "little"),
        height.to_bytes(2, "little"),
        n.to_bytes(2, "little"),
    ]

    with open(path, "wb") as file:
        file.write(b"".join(meta))

""" Function to write U, SIGMA and V matrices of each color channel of a picture """
def write_matrices(path, red, green, blue):
    data_r = [np.array(x).tobytes() for x in red]
    data_g = [np.array(x).tobytes() for x in green]
    data_b = [np.array(x).tobytes() for x in blue]

    with open(path, "ab") as file:
        for item in [data_r, data_g, data_b]:  # r g b
            for x in item:  # u s v
                file.write(x)

""" Function to display size of a file """
def file_size(path):
    return str((os.path.getsize(path) / 1024)) + " Kbs"

""" Functoion to read information about color channels' matrices from a .lol file """
def read_matrices(path):
    with open(path, "rb") as file:
        data = [x.to_bytes() for x in file.read()]

    # Читаем заголовок (little end)
    height = int.from_bytes(b"" + data[3] + data[2])
    n = int.from_bytes(b"" + data[5] + data[4])

    res = []

    for i in range(3):
        f = 6 + height * i  # сдвиг относительно матриц r g b
        u = data[f : height + f]
        s = data[height + f + 1 : height + f + 1 + n]
        v = data[height + f + 2 + n : height + f + 2 + 2 * n]
        res.append((u, s, v))

    return res
