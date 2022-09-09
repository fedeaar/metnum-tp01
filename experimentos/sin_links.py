import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')
def sin_links(t):
    pathIn, pathOut, pathRes = IO.createInOut("sin_links")
    typeIn = ".txt"
    typeOut = ".out"

    resultFile = open(pathRes + "res.txt", "w")
    result = []
    p = 1 - 1e-4
    for i in range(1, t+1):
        experiment = "t_"+ str(i)

        # creo IpWD
        W = np.zeros((i, i))

        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        result.append(solucion[0])
        resultFile.write(str(solucion[0]) + '\n')

    resultFile.close()
    utils.plot(1, t+1, result)
    
sin_links(100)
