import numpy as np
import base

IO = base.IO
print('\n')
def arbol_binario(pisos):
    pathIn, pathOut, pathRes = base.createInOut("arbol_binario")
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


    IO.run(W, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
    p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)
    for j in range(pisos):
        result.append(solucion[(1 << j)-1])
        resultFile.write(str(solucion[(1 << j)-1]) + '\n')

    resultFile.close()
    base.plot(0, pisos, result)

arbol_binario(6)
