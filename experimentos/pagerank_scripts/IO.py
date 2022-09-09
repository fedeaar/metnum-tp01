import os
import subprocess as sub
import numpy as np


def readFileIn(filename):
    with open(filename) as f:
        mylist = f.read().splitlines()
        n = int(mylist[0])
        cantLinks = int(mylist[1])
        links = [x.split(' ') for x in mylist[2:]]
        matriz = np.full((n, n), 0)
        for link in links:
            if (len(link) == 2):
                matriz[int(link[1]) - 1][int(link[0]) - 1] = 1

    return n, cantLinks, matriz


def readFileOut(filename):
    with open(filename) as f:
        mylist = f.read().splitlines()
        p_val = float(mylist[0])
        resultado = np.array([float(x) for x in mylist[1:]])

    return p_val, resultado


def readMatriz(filename):
    with open(filename) as f:
        mylist = [x.split(', ') for x in f.read().splitlines()]
        matriz = np.array(mylist)

    return matriz


def readTime(filename):
    with open(filename) as f:
        mylist = [x for x in f.read().splitlines()]
        time = int(mylist[1])

    return time


def createFileIn(filename, matrix):
    n = matrix.shape[0]
    cantLinks = np.count_nonzero(matrix != 0)
    links = np.where(matrix != 0)
    links = tuple(zip(*links))
    text = [n, cantLinks]
    for coord in links:
        text.append(str(coord[1] + 1) + " " + str(coord[0] + 1))
    with open("./" + filename + ("" if filename[-4:] == ".txt" else ".txt"), 'wb') as file:
        np.savetxt(file, text, delimiter="\n", fmt='%s')

    return links


def createInOut(experimento):
    path = "./resultados/"  + experimento + "/"
    pathIn =  path + "in/"
    pathOut = path + "out/"
    if not os.path.exists(pathIn):
        os.makedirs(pathIn)
    if not os.path.exists(pathOut):
        os.makedirs(pathOut)
        
    return pathIn, pathOut, path


def run(filename, p_value, 
        out_dir='./', save_as=None, precision=15, time_it=False, save_m=False, exe_path='./build/pagerank'):

    call_params = [
        'wsl', exe_path, filename, str(p_value), 
        f'-out={out_dir}',
        f'{f"-save_as={save_as}" if save_as else ""}', 
        f'-presicion={precision}', 
        f'{"-time_it" if time_it else ""}',
        f'{"-save_m" if save_m else ""}'
    ]
    sub.check_call(call_params)
