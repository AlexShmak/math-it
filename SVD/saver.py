"""
    WIDTH:INT
    HEIGHT:INT
    N:INT
    U:2D INT ARRAY
    SIGMA:INT ARRAY
    VT:2D INT ARRAY
"""

import numpy as np


def create_meta_data(w, h, n):
    metadata = [
        w.to_bytes(2, "big"),
        h.to_bytes(2, "big"),
        n.to_bytes(2, "big"),
    ]

    with open("middle_repr.lol", "wb") as file:
        file.write(b"".join(metadata))


def write_middle_repr(r, g, b):
    red = [np.arrayx(x).tobytes() for x in r]
    green = [np.array(x).tobytes() for x in g]
    blue = [np.array(x).tobytes() for x in b]

    with open("middle_repr.lol", "ab") as file:
        for i in [red, green, blue]:
            for j in i:
                file.write(j)
