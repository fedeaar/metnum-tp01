import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')

def todos_a_uno(n, p = 1 - 1e-4):
    pathIn, pathOut, pathRes = IO.createInOut("todos_a_uno")
    typeIn = ".txt"
    typeOut = ".out"
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(1, n + 1):
        experiment = "t_"+ str(i)

        W = np.zeros((n,n))
        for j in range(1, i):
            W[0][j] = 1

        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        resultFile.write(str(solucion[0]) + '\n')
        result.append(solucion[0])

    resultFile.close()
    utils.plot(1, n + 1, result)

todos_a_uno(400)