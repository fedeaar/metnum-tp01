from ast import If
import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')
def aislado(n, p = 1-1e-4):
    # tomando un nodo cualquiera, excepto el aislado, cada una de las posibles 
    # conexiones con otros nodos(excepto el aislado) tiene una probabilidad p2 de existir
    pathIn, pathOut, pathRes = IO.createInOut("aislado")
    typeIn = ".txt"
    typeOut = ".out"

    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(0, n):
        experiment = "t_"+ str(i)
        
        W = np.zeros((2*n, 2*n))
        opciones = []

        for j in range(n, 2*n) :
            W[0][j] = 1

        for j in range(1, n):
            for k in range(1, n):
                if k == j: continue
                opciones.append([j, k])

        for j in range(i) :
            vinculo = opciones.pop(np.random.randint(0,len(opciones)))
            W[vinculo[0]][vinculo[1]] = 1

        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)
        if(solucion[0] < 0.1) : print(W)
        result.append(solucion[0])
        resultFile.write(str(solucion[0]) + '\n')

    resultFile.close()
    utils.plot(0, n, result)
    
aislado(10)
