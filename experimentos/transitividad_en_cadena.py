import numpy as np
import base

IO = base.IO
print('\n')
def transitividad_en_cadena(n):
    pathIn, pathOut = base.createInOut("transitividad_en_cadena")
    typeIn = ".txt"
    typeOut = ".out"

    p = 1
    result = []
    for i in range(n):
        experiment = "nodos_"+ str(i)

        # creo IpWD
        W = np.full((2*n, 2*n), 0)
        for j in range(i):
            W[j+1][j] = 1
        for j in range(n, 2*n):
            W[0][j] = 1

        IpWD = base.W_to_IpWD(W, 2*n, p)

        IO.run(IpWD, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        result.append(solucion[i])
    
    print(result)
    return result

transitividad_en_cadena(100)
