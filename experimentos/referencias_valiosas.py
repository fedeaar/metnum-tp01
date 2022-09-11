import base.IO as IO
import base.utils as utils

import numpy as np
import pandas as pd


"""
descripcion:
    cómo se comporta el puntaje de un nodo a medida que cambia el de uno 
    que lo referencia.
"""

# IO
EXPERIMENTO          = "referencias_valiosas"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS           = f"{DIR}{EXPERIMENTO}.csv"
SUMMARY              = f"{DIR}{EXPERIMENTO}_summary_referenciado.csv"
SUMMARY_R            = f"{DIR}{EXPERIMENTO}_summary_referenciador.csv"
GRAFICO              = f"{DIR}{EXPERIMENTO}"

# fmt
COLS       = 'p_val,puntaje_referenciador,puntaje_referenciado,q_refs'
FMT_COLS   = "{0},{1},{2},{3}\n"

# variables
N = 100   # cantidad total de nodos a alcanzar
P = [0, 0.25, 0.50, 0.75, 1 - 1e-4]  # valor p


# metodos
def correr_pagerank():

    for pos, p in enumerate(P):
        for i in range(2, N + 3):

            # creo IpWD
            W = np.zeros((N+2, N+2))
            W[1][0] = 1
            for j in range(2, i):
                W[0][j] = 1

            caso = DIR_IN + "c" + str(pos) + "_x" + str(i) + ".txt"
            IO.createFileIn(caso, W)
            IO.run(caso, p, out_dir=DIR_OUT)


def medir():

    with open(RESULTADOS, "a", encoding="utf-8") as file:
        
        for p in range(len(P)):
            for i in range(2, N + 3):

                caso = DIR_OUT + "c" + str(p) + "_x" + str(i) + ".out"
                _p, solucion = IO.readFileOut(filename=caso)

                file.write(FMT_COLS.format(_p, solucion[0], solucion[1], i - 2))
            
 


if __name__ == "__main__":

    IO.createCSV(RESULTADOS, COLS)
    correr_pagerank()
    medir()

    res = pd.read_csv(RESULTADOS)
    res.puntaje_referenciado.describe().to_csv(SUMMARY)
    res.puntaje_referenciador.describe().to_csv(SUMMARY_R)
    
    for p in P:
        df = res.query(f"p_val == {p}", engine="python")
        utils.graficar(
            x=df.q_refs.to_list()*2,
            y=df.puntaje_referenciador.to_list() + df.puntaje_referenciado.to_list(), 
            hue=["página '1', referenciadora"]*(N+1) + ["página '2', referenciada"]*(N+1), 
            xaxis="CANTIDAD DE REFERENCIAS A '1'", 
            yaxis="PUNTAJE", 
            filename=GRAFICO + "_p" + str(p) + ".png")
