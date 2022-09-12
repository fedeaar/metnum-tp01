import os
import subprocess as sub
import numpy as np


# GLOBALES
EXE_PATH = '../build/tp1'      # si se compilo de otra manera o con otro nombre, cambiar por la direccion correcta
WSL = True                     # dejar true solo si se utilizó wsl para compilar el programa, false sino


def readFileIn(filename):

    with open(filename) as file:
        data = file.read().splitlines()
        n         = int(data[0])
        cantLinks = int(data[1])
        links     = [x.split(' ') for x in data[2:]]
        matriz    = np.full((n, n), 0)
        for link in links:
            if (len(link) == 2):
                matriz[int(link[1]) - 1][int(link[0]) - 1] = 1

    return n, cantLinks, matriz


def readFileOut(filename):

    with open(filename) as file:
        data  = file.read().splitlines()
        p_val = float(data[0])
        resultado = np.array([float(x) for x in data[1:]])

    return p_val, resultado


def readMatriz(filename):

    with open(filename) as file:
        data   = [x.split(', ') for x in file.read().splitlines()]
        matriz = np.array(data)  

    return matriz


def readTime(filename):

    with open(filename) as file:
        data = [x for x in file.read().splitlines()]
        time = int(data[1])

    return time


def createFileIn(filename, matrix):

    n         = matrix.shape[0]
    cantLinks = np.count_nonzero(matrix != 0)
    links     = np.where(matrix != 0)
    links     = tuple(zip(*links))
    text      = [n, cantLinks]
    for coord in links:
        text.append(str(coord[1] + 1) + " " + str(coord[0] + 1))

    with open("./" + filename + ("" if filename[-4:] == ".txt" else ".txt"), 'wb') as file:
        np.savetxt(file, text, delimiter="\n", fmt='%s')

    return links


def createInOut(filename):
    
    path = "./resultados/" + filename + '/'
    pathIn =  path + "in/"
    pathOut = path + "out/"
    if not os.path.exists(pathIn):
        os.makedirs(pathIn)
    if not os.path.exists(pathOut):
        os.makedirs(pathOut)
        
    return pathIn, pathOut, path


def createCSV(filename, columnas): 

    with open(filename, "w", encoding="utf-8") as file:
        file.write(columnas + '\n')


def run(filename, p_value, 
        out_dir="./", precision=15, save_as=None, time_it=False, save_m=False, 
        exe_path=EXE_PATH):

    call_params = [
        "wsl" if WSL else "",   
        exe_path, 
        filename, str(p_value), 
        f"-out={out_dir}",
        f'{f"-save_as={save_as}" if save_as else ""}', 
        f"-presicion={precision}", 
        f'{"-time_it" if time_it else ""}',
        f'{"-save_m" if save_m else ""}'
    ]
    sub.check_call(call_params)
