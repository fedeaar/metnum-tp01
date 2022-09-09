import numpy as np
import base

IO = base.IO
print('\n')
def sin_links(t):
    pathIn, pathOut, pathRes = base.createInOut("sin_links")
    typeIn = ".txt"
    typeOut = ".out"

    resultFile = open(pathRes + "res.txt", "w")
    result = []
    p = 1 - 1e-4
    for i in range(1, t+1):
        experiment = "t_"+ str(i)

        # creo IpWD
        W = np.zeros((i, i))

        IO.run(W, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        result.append(solucion[0])
        resultFile.write(str(solucion[0]) + '\n')

    resultFile.close()
    base.plot(1, t+1, result)
    
sin_links(100)
