import numpy as np
import matplotlib.pyplot as plt

import pagerank_scripts.IO


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


def random_W(n, q, seed=0):
    sz = (n-1)*n
    W  = np.zeros(sz, dtype=np.double)
    W[:q] = 1
    rng = np.random.default_rng(seed if seed else None)
    rng.shuffle(W)
    for i in range(0, sz, n + 1):
        W = np.concatenate((W[:i], [0], W[i:]))
    W = np.append(W, 0)
    W = W.reshape((n, n))

    return W 


def norma_inf(x):
    return np.linalg.norm(x, np.inf)


def solve(A, b):
    x = np.linalg.solve(A, b)
    
    return x


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