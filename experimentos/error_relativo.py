import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import os
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(rc={'figure.figsize':(14, 7)}, font="Times New Roman")


"""
descripcion: 
    medimos el error relativo para 100 casos de grafos en función del valor de p.

    Cada grafo 'g' se genera de la siguiente manera:

        Sobre un total de 100 nodos, 
        
        - se elige la cantidad de ejes 'e' del sistema uniformemente sobre el intervalo 
        [0, 1/4 * (100^2 - 100)), donde (100^2 - 100) representa el máximo de ejes 
        posible en un grafo dirigido que no permite auto-direccionamiento y 1/4 es un 
        valor arbitrario elegido para acercar los grafos a las carácteristicas de 
        ralidad esperables en una web.

        - se pobla una matriz 99x100 = 0 con unos en las primeras e posiciones.

        - se utiliza el algoritmo de shuffle de numpy, sobre el generador PCG64 para 
        distribuir aleatoriamente los unos en la matriz.
        
        - se expande la misma con ceros en la diagonal para resultar en una matriz 
        100x100 (ya que nuestro algoritmo descarta los autodireccionamientos, se 
        utilizó este procedimiento para garantizar la cantidad de ejes en los grafos 
        generados). 

    Para cada valor de p en el intervalo [0, 1), de a saltos de 0.01, se calcula 
    x = PageRank(g, p) y se procede a medir el error relativo |Ax - x| donde se toma
    la norma infinito como medida del error. Se considera que esta es una buena opción,
    ya que nos interesa conocer el error máximo resultante del procedimiento.
"""


# IO
EXPERIMENTO = "error_relativo_x_p_val"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS = f"{DIR}{EXPERIMENTO}.csv"
SUMMARY    = f"{DIR}{EXPERIMENTO}_summary.csv"
MINMAX     = f"{DIR}{EXPERIMENTO}_picos.csv"
GRAFICO    = f"{DIR}{EXPERIMENTO}.png"

# fmt
COLS       = 'p_val,error,caso'
FMT_COLS   = "{0},{1},{2}\n"
FMT_I      = DIR_IN  + "c{caso}.txt"
FMT_name   = "x{x}_c{caso}"
FMT_O      = DIR_OUT + FMT_name + ".out"

# variables
N       = 100   # cantidad de páginas
RALIDAD = 1/4   # cantidad maxima de links sobre el total
XLIM    = 100   # [0, XLIM] = rango de valores a tomar de la variable independiente
CASOS   = 100   # cantidad de casos a considerar por cada valor de la variable independiente     
SEED    = 1     # para garantizar la reproducibilidad del experimento


# metodos
def crear_csv(): 

    if not os.path.exists(RESULTADOS):
        with open(RESULTADOS, "w", encoding="utf-8") as file:
            # columnas
            file.write(COLS  + '\n')


def crear_casos():

    max_links = RALIDAD * (N-1) * N
    for c in range(CASOS):
        
        np.random.seed(SEED + c)                  # para que sea reproducible

        u = np.random.random_sample()             # uniforme [0, 1)
        l = int(max_links * u)                    # links en [0, max_links)
        W = utils.random_W(N, l, SEED + c)        # PCG64

        IO.createFileIn(FMT_I.format(caso=c), W)  # guardamos el caso


def correr_pagerank():

    for _p in range(XLIM):
        p = _p / XLIM
        
        for t in range(CASOS):    
            file_in  = FMT_I.format(caso=t)
            out_name = FMT_name.format(x=_p, caso=t)

            IO.run(filename=file_in, 
                p_value=p,
                out_dir=DIR_OUT,
                save_as=out_name)


def medir_errores():

    for _p in range(XLIM):
        for c in range(CASOS):

            p, x    = IO.readFileOut(FMT_O.format(x=_p, caso=c))
            n, l, W = IO.readFileIn(FMT_I.format(caso=c))
            
            A = utils.W_to_A(W, p)
            Ax = A @ x.T
            error = utils.norma_uno(Ax - x) # tomamos el error máximo
    
            with open(RESULTADOS, 'a', encoding="utf-8") as file:
                file.write(FMT_COLS.format(p, error, c))


def graficar(df):
    hue = ["promedio"]*len(df.error)
    plot = sns.lineplot(data=df, x="p_val", y="error", hue=hue)
    plot.set_xlabel("VALOR DE P", fontsize=18, labelpad=12)
    plot.set_ylabel("ERROR   RELATIVO", fontsize= 18, labelpad=20) 
    plt.tick_params(axis='both', which='major', labelsize=16)
    fig  = plot.get_figure()
    fig.savefig(GRAFICO) 


def minmax(df):

    local = res.groupby("p_val").mean()
    local['min'] =  local.error[(local.error.shift(1) > local.error) & (local.error.shift(-1) > local.error)]
    local['max'] =  local.error[(local.error.shift(1) < local.error) & (local.error.shift(-1) < local.error)]
    minmax = local.query("not min.isna() or not max.isna()", engine='python')
    minmax['pico'] = minmax['min'].apply(lambda x: 'min' if not pd.isna(x) else 'max')
    minmax[['error', 'pico']].rename(columns={"error":"error_avg"}).to_csv(MINMAX)


def summary(df):
    res["error"].describe().to_csv(SUMMARY)




if __name__ == "__main__":

    # crear_csv()
    # crear_casos()
    # correr_pagerank()
    # medir_errores()

    res = pd.read_csv(RESULTADOS)
    graficar(res)
    # minmax(res)
    # summary(res)
