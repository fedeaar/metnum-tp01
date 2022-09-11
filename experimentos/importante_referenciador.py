import base.IO as IO
import base.utils as utils

import numpy as np
import pandas as pd


"""
descripcion:
    cómo se comporta el puntaje de un nodo importante a medida que 
    referencia a más sitios, se realizaron 25 tests aleatorios. 
"""

# IO
EXPERIMENTO          = "importante_referenciador"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS           = f"{DIR}{EXPERIMENTO}.csv"
SUMMARY              = f"{DIR}{EXPERIMENTO}_summary.csv"
GRAFICO              = f"{DIR}{EXPERIMENTO}.png"

# fmt
COLS       = 'p_val,puntaje,q_refs,caso'
FMT_COLS   = "{0},{1},{2},{3}\n"

# variables
N = 100   # cantidad total de nodos a alcanzar
p = 0.85  # valor p
CASOS = 25

# metodos
def correr_pagerank():

    for t in range(CASOS) :
        for i in range(1, N):
            
            caso = DIR_IN + "x" + str(i) + "_c" + str(t) + ".txt"

            W = np.zeros((N, N))
            for j in range(1, N):
                W[0][j] = 1
            for j in range(1, i): 
                W[j][0] = 1
            
            opciones = []
            for j in range(1, N):
                for k in range(1, N):
                    if k == j: continue
                    opciones.append([j, k])

            for j in range(int(0.1 * len(opciones))):
                vinculo = opciones.pop(np.random.randint(0, len(opciones)))
                W[vinculo[0]][vinculo[1]] = 1

            IO.createFileIn(caso, W)
            IO.run(caso, p, out_dir=DIR_OUT)


def medir():

    with open(RESULTADOS, "a", encoding="utf-8") as file:

        for t in range(CASOS) :
            for i in range(1, N):

                caso = DIR_OUT + "x" + str(i) + "_c" + str(t) + ".out"
                p, solucion = IO.readFileOut(filename=caso)

                file.write(FMT_COLS.format(p, solucion[0], i, t)) 
            
 


if __name__ == "__main__":

    IO.createCSV(RESULTADOS, COLS)
    correr_pagerank()
    medir()

    res = pd.read_csv(RESULTADOS)
    res.puntaje.describe().to_csv(SUMMARY)
    
    utils.graficar(
        x=res.q_refs,
        y=res.puntaje, 
        hue=["referenciador"]*(N-1)*25, 
        xaxis="CANTIDAD DE REFERENCIAS HECHAS", 
        yaxis="PUNTAJE", 
        filename=GRAFICO)
