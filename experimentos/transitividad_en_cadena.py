import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np
import matplotlib.pyplot as plt


print('\n')
def transitividad_en_cadena(n):
    pathIn, pathOut, pathRes = IO.createInOut("transitividad_en_cadena")
    typeIn = ".txt"
    typeOut = ".out"

    p = 1 - 1e-4
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(n):
        experiment = "t_"+ str(i)

        # creo IpWD
        W = np.full((2*n, 2*n), 0)
        for j in range(i):
            W[j+1][j] = 1
        for j in range(n, 2*n):
            W[0][j] = 1

        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        result.append(solucion[i])
        resultFile.write(str(solucion[i]) + '\n')
    
    resultFile.close()
    utils.graficar(
        x=[x for x in range(0, n)], 
        y=result, 
        hue=["test_base"]*n, 
        xaxis="cantidad de links en cadena", 
        yaxis="puntaje", 
        filename=pathRes + "grafico" + ".png")

transitividad_en_cadena(20)
