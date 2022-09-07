import os
import pagerank_scripts.IO as IO
import numpy as np

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
    if not os.path.exists(pathIn):
        os.makedirs(pathIn)
    if not os.path.exists(pathOut):
        os.makedirs(pathOut)
    return pathIn, pathOut