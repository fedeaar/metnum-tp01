import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


def todos_a_uno(n, p=0.85):
    pathIn, pathOut, pathRes = IO.createInOut("todos_a_uno")
    typeIn = ".txt"
    typeOut = ".out"
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    result1 = []
    for i in range(1, n + 1):
        experiment = "t_"+ str(i)
 
        W = np.zeros((n,n))
        W[0, 1:i] = 1

        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        resultFile.write(str(solucion[0]) + '\n')
        result.append(solucion[0])
        result1.append(solucion[1])

    resultFile.close()
    utils.graficar(
        x=[x for x in range(1, n + 1)]*2, 
        y=result + result1,
        hue=["nodo 'uno'"]*n + ["nodo testigo"]*n,
        xaxis="cantidad de referencias",
        yaxis="puntaje",
        filename=pathRes+"grafico.png")

todos_a_uno(100)