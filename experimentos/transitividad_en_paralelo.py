import numpy as np
import base

IO = base.IO
print('\n')
def transitividad_en_paralelo(n):
    pathIn, pathOut, pathRes = base.createInOut("transitividad_en_paralelo")
    typeIn = ".txt"
    typeOut = ".out"

    p = 1 - 1e-4
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(2, n+2):
        experiment = "t_"+ str(i)

        # creo IpWD
        W = np.full((n+2, n+2), 0)
        W[1][0] = 1
        for j in range(2, i):
            W[0][j] = 1

        IO.run(W, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)
        thisRes = solucion[1] - solucion[0]
        print(solucion[0], solucion[1])
        result.append(thisRes)
        resultFile.write(str(thisRes) + '\n')

    resultFile.close()
    base.plot(2, n+2, result)
    

transitividad_en_paralelo(100)
