import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

from turtle import circle
import numpy as np

print('\n')
def circular(n):
    pathIn, pathOut, pathRes = IO.createInOut("circular")
    typeIn = ".txt"
    typeOut = ".out"

    p = 1 - 1e-4
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(1, n+1):
        experiment = "t_"+ str(i)

        # creo IpWD
        W = np.zeros((i, i))
        for j in range(i):
            W[j][(j+1)%i] = 1


        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)
        
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        resultFile.write(str(solucion[0]) + '\n')
        result.append(solucion[0])

    
    resultFile.close()
    utils.plot(1, n+1, result)

circular(100)
