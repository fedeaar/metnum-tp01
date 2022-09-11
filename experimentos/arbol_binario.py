import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')
def arbol_binario(pisos):
    pathIn, pathOut, pathRes = IO.createInOut("arbol_binario")
    typeIn = ".txt"
    typeOut = ".out"

    n = 2**pisos-1
    p = 1 - 1e-4
    result = []
    resultFile = open(pathRes + "res.txt", "w")
    experiment = "t"

    # creo IpWD
    W = np.zeros((n, n))
    for j in range(1, n):
        W[(j+1)//2-1][j] = 1

    IO.createFileIn(pathIn + experiment + typeIn, W)
    IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

    p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)
    
    for j in range(pisos):
        result.append(solucion[(1 << j)-1])
        resultFile.write(str(solucion[(1 << j)-1]) + '\n')

    resultFile.close()
    utils.plot(0, pisos, result)

arbol_binario(13)
