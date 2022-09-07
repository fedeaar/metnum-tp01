from unittest import result
import numpy as np
import base

IO = base.IO
print('\n')
def arbol_binario(pisos):
    pathIn, pathOut = base.createInOut("arbol_binario")
    typeIn = ".txt"
    typeOut = ".out"

    n = 2**pisos-1
    p = 1
    result = []
    experiment = "nodos"

    # creo IpWD
    W = np.full((n, n), 0)
    for j in range(1, n):
        W[(j+1)//2-1][j] = 1

    IpWD = base.W_to_IpWD(W, n, p)

    IO.run(IpWD, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
    p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)
    for j in range(pisos):
        result.append(solucion[(1 << j)-1])
    print(result)
    return result

arbol_binario(13)
