import numpy as np
import subprocess as sub


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
        matriz = np.array(mylist);
    return matriz


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


def run(matriz, p_value, filename, out_dir='.gen/out', debug=True, exe_path='./build/pagerank'):
    createFileIn(filename, matriz)
    sub.check_call([
        'wsl', 
        exe_path,
        filename,
        str(p_value), 
        f'-out={out_dir}', 
        f'{"-debug" if debug else ""}'])
