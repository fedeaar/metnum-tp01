import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import os
import numpy as np
import pandas as pd
import seaborn as sns
sns.set(rc={'figure.figsize':(14, 7)})


"""
descripcion: 
    medimos el tiempo de ejecución para 100 casos de grafos 100x100 en función de la 
    cantidad de ejes.

    Cada grafo 'g' se genera de la siguiente manera:

        Sobre un total de 100 nodos, 

        - se pobla una matriz 99x100 = 0 con unos en las primeras e posiciones, donde
        'e' es la cantidad de ejes a testar.

        - se utiliza el algoritmo de shuffle de numpy, sobre el generador PCG64 para 
        distribuir aleatoriamente los unos en la matriz.
        
        - se expande la misma con ceros en la diagonal para resultar en una matriz 
        100x100 (ya que nuestro algoritmo descarta los autodireccionamientos, se 
        utilizó este procedimiento para garantizar la cantidad de ejes en los grafos 
        generados). 

    Se utiliza p = 0.85, siguiendo el uso de google [langville].

    Para cada valor de e en el intervalo [0, 99*100], se calcula x = PageRank(g, p) y 
    se procede a medir el tiempo de ejecución.
"""


# IO
EXPERIMENTO = "tiempo_ejecucion"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS = f"{DIR}{EXPERIMENTO}.csv"
SUMMARY    = f"{DIR}{EXPERIMENTO}_summary.csv"
GRAFICO    = f"{DIR}{EXPERIMENTO}.png"

# fmt
COLS       = 'q_links,tiempo_us,caso'
FMT_COLS   = "{0},{1},{2}\n"
FMT_name   = "x{x}_c{caso}"
FMT_I      = DIR_IN  + FMT_name + ".txt"
FMT_O      = DIR_OUT + FMT_name + ".time"

# variables
N       = 100   # cantidad de páginas
P       = 0.85  # valor p
XLIM    = N * (N - 1)
CASOS   = 100   # cantidad de casos a considerar por cada valor de la variable independiente     
SEED    = 1     # para garantizar la reproducibilidad del experimento


# metodos
def crear_csv(): 

    if not os.path.exists(RESULTADOS):
        with open(RESULTADOS, "w", encoding="utf-8") as file:
            # columnas
            file.write(COLS  + '\n')


def crear_casos():

    max_links = (N-1) * N
    for c in range(CASOS):
        for l in range(max_links):

            seed = l + c*max_links                   # para que sea reproducible
            W = utils.random_W(N, l, SEED + seed)    # PCG64

            IO.createFileIn(FMT_I.format(x=l, caso=c), W)  # guardamos el caso


def correr_pagerank():

    for c in range(CASOS):
        for l in range(XLIM):

            file_in  = FMT_I.format(x=l, caso=c)
            IO.run(filename=file_in, 
                p_value=P,
                out_dir=DIR_OUT,
                time_it=True)


def medir_errores():

    for c in range(CASOS):
        for l in range(XLIM):

            time = IO.readTime(FMT_O.format(x=l, caso=c))
    
            with open(RESULTADOS, 'a', encoding="utf-8") as file:
                file.write(FMT_COLS.format(x, time, c))


def graficar(df):

    plot = sns.lineplot(data=df, x="q_links", y="tiempo_us")
    plot.set_xlabel("cantidad de links", fontsize=16, labelpad=16)
    plot.set_ylabel("tiempo (microsegundos)", fontsize=16, labelpad=16)    
    fig  = plot.get_figure()
    fig.savefig(GRAFICO) 




if __name__ == "__main__":

    crear_csv()
    crear_casos()
    correr_pagerank()
    medir_errores()

    res = pd.read_csv(RESULTADOS)
    res["tiempo_us"].describe().to_csv(SUMMARY)
    
    graficar(res)
