import pagerank_scripts.IO as IO
import numpy as np


def experimento(rep=100, tam=20, dir="./resultados/error_relativo/"):
    n = 5
    p = 0.85
    A = np.array([
        [0, 1, 1, 0, 1],
        [1, 0, 1, 0, 0],
        [0, 0, 0, 1, 1],
        [1, 1, 0, 0, 0],
        [0, 0, 0, 1, 0]
    ])

    IO.run(matriz=A, p_value=p, filename='./resultados/error_relativo/in/ejemplo.txt', out_dir='./resultados/error_relativo/out/', time=True)

    solucion = IO.readFileOut(filename='./resultados/error_relativo/ejemplo.out')

    print('\n\n','error relativo test: ', _solucion - solucion)


    D = np.eye(5)
    rango = matriz.sum(axis=0)
    for i in range(5):
        D[i][i] = 1 / rango[i] if rango[i] != 0 else 0

    IpWD = np.eye(5) - p * A @ D



