from cgitb import text
import numpy as np
filename = "experimentos/scripts/data/input1.txt"

def readFile(filename):
    with open(filename) as f:
        mylist = f.read().splitlines()
        n = mylist[0]
        cantLinks = mylist[1]
        links = mylist[2:]
    return n, cantLinks, links

def createFile(filename, matrix):
    n = matrix.shape[0]
    cantLinks = np.count_nonzero(matrix != 0)
    links = np.where(matrix != 0)
    links = tuple(zip(*links))
    text = [n, cantLinks]
    for coord in links:
        text.append(str(coord[0]) + " " + str(coord[1]))
    with open("experimentos/scripts/output/" + filename + ".txt", 'wb') as file:
        np.savetxt(file, text, delimiter = "\n", fmt='%s')
    return links


mat = np.array([[1,1,0],
               [0,3,0],
               [1,1,1]])

print(createFile("hola1", mat))