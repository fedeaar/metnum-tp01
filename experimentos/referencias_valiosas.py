import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')
def referencias_valiosas(n):
    pathIn, pathOut, pathRes = IO.createInOut("referencias_valiosas")
    typeIn = ".txt"
    typeOut = ".out"

    p = 1 - 1e-4
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(2, n+2):
        experiment = "t_"+ str(i)

        # creo IpWD
        W = np.zeros((n+2, n+2))
        W[1][0] = 1
        for j in range(2, i):
            W[0][j] = 1

        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)
        thisRes = solucion[1]
        result.append(thisRes)
        resultFile.write(str(thisRes) + '\n')
    resultFile.close()
    utils.plot(2, n+2, result)
    

referencias_valiosas(100)
