import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')
def todosConTodos(t):
    pathIn, pathOut, pathRes = IO.createInOut("todos_con_todos")
    typeIn = ".txt"
    typeOut = ".out"

    p = 1 - 1e-4
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(1, t+1):
        experiment = "t_"+ str(i)

        W = np.ones((i,i)) - np.eye(i)

        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        resultFile.write(str(solucion[0]) + '\n')
        result.append(solucion[0])

    resultFile.close()
    utils.plot(1, t+1, result)

todosConTodos(100)
