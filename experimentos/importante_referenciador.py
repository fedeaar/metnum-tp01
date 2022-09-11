import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')
def importante_referenciador(n, p = 1 - 1e-4):
    pathIn, pathOut, pathRes = IO.createInOut("importante_referenciador")
    typeIn = ".txt"
    typeOut = ".out"
    resultFile = open(pathRes + "res.txt", "w")
    result = [0] * (n-1)


    tests = int(10)
    for t in range(tests) :
        for i in range(1, n):
            experiment = "t_"+ str(i)

            W = np.zeros((n,n))
            for j in range(1,n) :
                W[0][j] = 1
            for j in range(1, i) : 
                W[j][0] = 1
            
            opciones = []
            for j in range(1, n):
                for k in range(1, n):
                    if k == j: continue
                    opciones.append([j, k])

            
            for j in range(int(0.1 * len(opciones))) :
                vinculo = opciones.pop(np.random.randint(0,len(opciones)))
                W[vinculo[0]][vinculo[1]] = 1

            IO.createFileIn(pathIn + experiment + typeIn, W)
            IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

            p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

            result[i-1] += (solucion[0])
        

    for i in range(1, n):
        result[i-1] /= tests
        resultFile.write(str(result[i-1]) + '\n')
    resultFile.close()
    utils.plot(1, n, result)

importante_referenciador(20)