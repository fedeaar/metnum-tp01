import numpy as np
import base
import matplotlib.pyplot as plt


IO = base.IO
print('\n')
def transitividad_en_cadena(n):
    pathIn, pathOut, pathRes = base.createInOut("transitividad_en_cadena")
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


        IO.run(W, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        result.append(solucion[i])
        resultFile.write(str(solucion[i]) + '\n')
    
    resultFile.close()
    base.plot(0, n, result)

transitividad_en_cadena(100)
