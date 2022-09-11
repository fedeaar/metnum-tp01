import base.IO as IO
import base.utils as utils

import numpy as np
import pandas as pd


"""
descripcion:
    cómo se diluye el puntaje del ultimo eslabón de una cadena de nodos, 
    donde el primero es importante. 
"""

# IO
EXPERIMENTO          = "transitividad_en_cadena"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS           = f"{DIR}{EXPERIMENTO}.csv"
SUMMARY              = f"{DIR}{EXPERIMENTO}_summary.csv"
GRAFICO              = f"{DIR}{EXPERIMENTO}.png"

# fmt
COLS       = 'p_val,puntaje_ultimo,largo_cadena'
FMT_COLS   = "{0},{1},{2}\n"

# variables
N = 100   # cantidad total de nodos a alcanzar
p = 0.85  # valor p


# metodos
def correr_pagerank():

    for i in range(1, N + 1):

        W = np.full((2*N, 2*N), 0)
        for j in range(i):
            W[j+1][j] = 1
        for j in range(N, 2*N):
            W[0][j] = 1

        caso = DIR_IN + "c"+ str(i) + ".txt"
        IO.createFileIn(caso, W)
        IO.run(caso, p, out_dir=DIR_OUT)


def medir():

    with open(RESULTADOS, "a", encoding="utf-8") as file:

        for i in range(1, N + 1):

            caso = DIR_OUT + "c" + str(i) + ".out"
            p, solucion = IO.readFileOut(filename=caso)

            file.write(FMT_COLS.format(p, solucion[i - 1], i - 1)) 
            
 


if __name__ == "__main__":

    IO.createCSV(RESULTADOS, COLS)
    correr_pagerank()
    medir()

    res = pd.read_csv(RESULTADOS)
    res.puntaje_ultimo.describe().to_csv(SUMMARY)
    
    utils.graficar(
        x=res.largo_cadena,
        y=res.puntaje_ultimo, 
        hue=["ultimo eslabón"]*N, 
        xaxis="LARGO DE LA CADENA", 
        yaxis="PUNTAJE", 
        filename=GRAFICO)
