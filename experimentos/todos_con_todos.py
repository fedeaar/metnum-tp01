import numpy as np
import base

IO = base.IO
print('\n')
def todosConTodos(t):
    pathIn, pathOut, pathRes = base.createInOut("todos_con_todos")
    typeIn = ".txt"
    typeOut = ".out"

    p = 1 - 1e-4
    resultFile = open(pathRes + "res.txt", "w")
    result = []
    for i in range(1, t+1):
        experiment = "t_"+ str(i)

        W = np.ones((i,i)) - np.eye(i)

        IO.run(W, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        resultFile.write(str(solucion[0]) + '\n')
        result.append(solucion[0])

    resultFile.close()
    base.plot(1, t+1, result)

todosConTodos(100)
