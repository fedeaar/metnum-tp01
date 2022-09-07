import numpy as np
import base

IO = base.IO
print('\n')
def todosConTodos(t):
    pathIn, pathOut = base.createInOut("todos_con_todos")
    typeIn = ".txt"
    typeOut = ".out"

    p = 1
    result = []
    for i in range(1, t):
        experiment = "nodos_"+ str(i)

        # creo IpWD
        unos = np.full((i, i), 1)
        I = np.eye(i)
        W = unos - I
        IpWD = base.W_to_IpWD(W, i, p)

        IO.run(IpWD, p, filename= pathIn + experiment + typeIn, out_dir= pathOut, debug=False)
        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        esperado = solucion[0]
        result.append(esperado)
        # compruebo que todos los elementos son iguales
        for x in solucion:
            if(abs(esperado-x) > base.EPSILON) :
                print("NO ES EL RESULTADO ESPERADO")
    
    print(result)
    return result

todosConTodos(100)
