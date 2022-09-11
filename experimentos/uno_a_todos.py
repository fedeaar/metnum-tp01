import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')
def uno_a_todos(n, p = 0.85):
    pathIn, pathOut, pathRes = IO.createInOut("uno_a_todos")
    typeIn = ".txt"
    typeOut = ".out"
    resultFile = open(pathRes + "res.txt", "w")
    resultFile.write("valor_p, nodo_apunta, nodo_1, nodo_n\n")
    result_0 = []
    result_1 = []
    result_n = []
    for i in range(1, n + 1):
        experiment = "t_"+ str(i)

        W = np.zeros((n,n))
        W[1:i, 0] = 1

        IO.createFileIn(pathIn + experiment + typeIn, W)
        IO.run(pathIn + experiment + typeIn, p, out_dir=pathOut)

        p, solucion = IO.readFileOut(filename=pathOut + experiment + typeOut)

        resultFile.write(f"{p}, {solucion[0]}, {solucion[1]}, {solucion[n-1]}\n")
        result_0.append(solucion[0])
        result_1.append(solucion[1])
        result_n.append(solucion[n-1])

    resultFile.close()
    utils.graficar(
        x=[x for x in range (1, n + 1)], 
        y=result_0,
        hue=["puntaje"]*n, 
        xaxis="cantidad de vínculos de salida", 
        yaxis="puntaje del nodo que apunta al resto", 
        filename=pathRes + "grafico_0" + ".png")

    utils.graficar(
        x=[x for x in range (1, n + 1)], 
        y=result_1,
        hue=["puntaje"]*n, 
        xaxis="cantidad de vínculos de salida", 
        yaxis="puntaje del nodo 1", 
        filename=pathRes + "grafico_1" + ".png")

    utils.graficar(
        x=[x for x in range (1, n + 1)], 
        y=result_n,
        hue=["puntaje"]*n, 
        xaxis="cantidad de vínculos de salida", 
        yaxis="puntaje del nodo n", 
        filename=pathRes + "grafico_n" + ".png")

uno_a_todos(100)