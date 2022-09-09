import numpy as np
import base

IO = base.IO
print('\n')

def todos_a_uno(n, p = 1):
    pathIn, pathOut, pathRes = base.createInOut("todos_a_uno")
    result = np.zeros((n, n))
    half = int(np.floor(n/2))
    result[:,half] = result[:,half] + 1
    
    IO.run(result, p, filename = pathIn + "todos_a_uno" + ".txt", out_dir = pathOut, debug=False)
    return result

print(todos_a_uno(25))