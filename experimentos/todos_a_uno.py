import base.IO as IO
import base.utils as utils

import numpy as np
import pandas as pd


"""
descripcion:
    cómo afecta al puntaje de un nodo particular la variación en la cantidad
    de referencias y qué sucede con otro nodo testigo.
"""

# IO
EXPERIMENTO          = "todos_a_uno"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS           = f"{DIR}{EXPERIMENTO}.csv"
SUMMARY_UNO          = f"{DIR}{EXPERIMENTO}_summary_uno.csv"
SUMMARY_TESTIGO      = f"{DIR}{EXPERIMENTO}_summary_testigo.csv"
GRAFICO              = f"{DIR}{EXPERIMENTO}.png"

# fmt
COLS       = 'p_val,q_nodos,q_links,puntaje_uno,puntaje_testigo'
FMT_COLS   = "{0},{1},{2},{3},{4}\n"

# variables
N = 100   # cantidad total de nodos a alcanzar
p = 0.85  # valor p


# metodos
def correr_pagerank():

    for i in range(1, N + 1):

        W = np.zeros((N, N))
        W[0, 1:i] = 1

        caso = DIR_IN + "c"+ str(i) + ".txt"
        IO.createFileIn(caso, W)
        IO.run(caso, p, out_dir=DIR_OUT)


def medir():

    with open(RESULTADOS, "a", encoding="utf-8") as file:

        for i in range(1, N+1):

            caso = DIR_OUT + "c" + str(i) + ".out"
            p, solucion = IO.readFileOut(filename=caso)

            file.write(FMT_COLS.format(p, N, i, solucion[0], solucion[1])) 
            
 


if __name__ == "__main__":

    IO.createCSV(RESULTADOS, COLS)
    correr_pagerank()
    medir()

    res = pd.read_csv(RESULTADOS)
    res.puntaje_uno.describe().to_csv(SUMMARY_UNO)
    res.puntaje_testigo.describe().to_csv(SUMMARY_TESTIGO)
    
    utils.graficar(
        x=res.q_links.to_list()*2, 
        y=res.puntaje_uno.to_list() + res.puntaje_testigo.to_list(), 
        hue=["caso 'uno'"]*N + ["caso testigo"]*N, 
        xaxis="CANTIDAD DE REFERENCIAS", 
        yaxis="PUNTAJE", 
        filename=GRAFICO)
