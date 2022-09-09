from turtle import circle
import numpy as np
import base

IO = base.IO
print('\n')
def circular(n):
    pathIn, pathOut, pathRes = base.createInOut("circular")
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


        IO.run(W, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        resultFile.write(str(solucion[0]) + '\n')
        result.append(solucion[0])

    
    resultFile.close()
    base.plot(1, n+1, result)

circular(100)
