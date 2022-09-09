import numpy as np
import base

IO = base.IO
print('\n')

def todos_a_uno(n, p = 1 - 1e-4):
    pathIn, pathOut, pathRes = base.createInOut("todos_a_uno")
    typeIn = ".txt"
    typeOut = ".out"
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(1, n + 1):
        experiment = "t_"+ str(i)

        W = np.zeros((i,i))
        half = int(np.floor(i/2))
        W[:,half] = W[:,half] + 1

        IO.run(W, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        resultFile.write(str(solucion[0]) + '\n')
        result.append(solucion[0])

    resultFile.close()
    base.plot(1, n + 1, result)

todos_a_uno(100)