import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import numpy as np


print('\n')
def todos_a_uno(n, p = 1):
    pathIn, pathOut, pathRes = IO.createInOut("todos_a_uno")
    result = np.zeros((n, n))
    half = int(np.floor(n/2))
    result[:,half] = result[:,half] + 1
    
    IO.createFileIn(pathIn + "todos_a_uno" + ".txt", W)
    IO.run(pathIn + "todos_a_uno" + ".txt", p, out_dir=pathOut)
    return result

print(todos_a_uno(25))