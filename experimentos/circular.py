import base.IO as IO
import base.utils as utils

import numpy as np
import pandas as pd


"""
descripcion:
    cómo afectan al puntaje las relaciones circulares, en función
    de la cantidad de nodos.
"""

# IO
EXPERIMENTO          = "circular"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS           = f"{DIR}{EXPERIMENTO}.csv"
SUMMARY              = f"{DIR}{EXPERIMENTO}_summary.csv"
GRAFICO              = f"{DIR}{EXPERIMENTO}.png"

# fmt
COLS       = 'p_val,puntaje_testigo,q_nodos'
FMT_COLS   = "{0},{1},{2}\n"

# variables
N = 100   # cantidad total de nodos a alcanzar
p = 0.85  # valor p


# metodos
def correr_pagerank():

    for i in range(1, N + 1):

        W = np.zeros((i,i))
        for j in range(i):
            W[j][(j+1)%i] = 1

        caso = DIR_IN + "c"+ str(i) + ".txt"
        IO.createFileIn(caso, W)
        IO.run(caso, p, out_dir=DIR_OUT)


def medir():

    with open(RESULTADOS, "a", encoding="utf-8") as file:

        for i in range(1, N+1):

            caso = DIR_OUT + "c" + str(i) + ".out"
            p, solucion = IO.readFileOut(filename=caso)

            file.write(FMT_COLS.format(p, solucion[0], i)) 
            
 


if __name__ == "__main__":

    IO.createCSV(RESULTADOS, COLS)
    correr_pagerank()
    medir()

    res = pd.read_csv(RESULTADOS)
    res.puntaje_testigo.describe().to_csv(SUMMARY)
    
    utils.graficar(
        x=res.q_nodos, 
        y=res.puntaje_testigo, 
        hue=["caso testigo"]*N, 
        xaxis="CANTIDAD DE PÁGINAS", 
        yaxis="PUNTAJE", 
        filename=GRAFICO)
