import base.IO

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(rc={'figure.figsize':(14, 7)}, font="Times New Roman")



# GLOBALES
EPSILON = 1e-4


def W_to_D(W):

    n = W.shape[0]
    D = np.full((n, n), 0, dtype=np.double)
    rango = W.sum(axis=0)
    for i in range(n):
        D[i][i] = 1 / rango[i] if rango[i] != 0 else 0

    return D


def W_to_IpWD(W, n, p): 

    I = np.eye(n)
    D = W_to_D(W)

    return I - p * W @ D


def W_to_A(W, p):

    n = W.shape[0]
    D = W_to_D(W)
    e = np.full((n, 1), 1, dtype=np.double)
    z = np.full((n, 1), 0, dtype=np.double)
    for i in range(n):
        z[i] = (1 - p) / n if D[i][i] != 0 else 1 / n    

    return p * W @ D + e @ z.T


def random_W(n, cantidad, seed=0):

    sz = (n-1)*n
    W  = np.zeros(sz, dtype=np.double)
    W[:cantidad] = 1

    rng = np.random.default_rng(seed if seed else None)
    rng.shuffle(W)
    
    for i in range(0, sz, n + 1):
        W = np.concatenate((W[:i], [0], W[i:]))
    W = np.append(W, 0)
    W = W.reshape((n, n))

    return W 


def norma_inf(x):

    return np.linalg.norm(x, np.inf)


def norma_uno(x):

    return np.linalg.norm(x, 1)


def solve(A, b):

    x = np.linalg.solve(A, b)
    
    return x


def graficar(x, y, hue, xaxis, yaxis, filename):
    
    plt.figure()
    df   = pd.DataFrame({"x":x, "y":y, "hue":hue})
    plot = sns.lineplot(data=df, x="x", y="y", hue="hue")
    
    plot.set_xlabel(xaxis, fontsize=18, labelpad=12)
    plot.set_ylabel(yaxis, fontsize= 18, labelpad=20) 
    plt.tick_params(axis='both', which='major', labelsize=16)
    plt.legend(title=None)

    fig = plot.get_figure()
    fig.savefig(filename)
