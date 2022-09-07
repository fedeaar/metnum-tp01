import numpy as np
import base

IO = base.IO
print('\n')
def transitividad_en_paralelo(n):
    pathIn, pathOut = base.createInOut("transitividad_en_paralelo")
    typeIn = ".txt"
    typeOut = ".out"

    n+=2
    p = 1
    amigo = []
    gordo = []
    for i in range(2, n):
        experiment = "nodos_"+ str(i)

        # creo IpWD
        W = np.full((n, n), 0)
        W[1][0] = 1
        for j in range(2, i):
            W[0][j] = 1
        IpWD = base.W_to_IpWD(W, n, p)

        IO.run(IpWD, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        gordo.append(solucion[0] - solucion[1])
    
    print(gordo)
    print(amigo)
    return gordo, amigo

transitividad_en_paralelo(100)
