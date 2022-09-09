import os
from turtle import down, left, right, up
import pagerank_scripts.IO as IO
import numpy as np
import matplotlib.pyplot as plt

EPSILON = 1e-4

def W_to_IpWD(W, n, p): 
    I = np.eye(n)
    D = np.eye(n)
    rango = W.sum(axis=0)
    for i in range(n):
        D[i][i] = 1 / rango[i] if rango[i] != 0 else 0

    return I - p * W @ D

def solve(IpWD, n, resultado):
    sol_np = np.linalg.solve(IpWD, np.full((n, 1), 1))
    sol_np = sol_np / np.sum(sol_np)
    print('\n', 'error relativo con numpy: ', sol_np.T - resultado) 

def createInOut(experiment):
    pathIn = "./resultados/"+ experiment + "/in/"
    pathOut = "./resultados/"+ experiment + "/out/"
    pathRes = "./resultados/"+ experiment + "/"
    if not os.path.exists(pathIn):
        os.makedirs(pathIn)
    if not os.path.exists(pathOut):
        os.makedirs(pathOut)
    if not os.path.exists(pathRes):
        os.makedirs(pathRes)
    return pathIn, pathOut, pathRes

def plot(desde, hasta, y): 
    plt.style.use('_mpl-gallery')

    # plot
    fig, ax = plt.subplots()
    x = range(desde, hasta)
    ax.plot(x, y, linewidth=2.0)

    ax.set(xlim=(desde, hasta-1), xticks=np.arange(desde, hasta, step= (hasta - desde)/10),
        ylim=(0, 1), yticks = np.arange(0, 1, step=0.1))
    plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.1)

    plt.show()
