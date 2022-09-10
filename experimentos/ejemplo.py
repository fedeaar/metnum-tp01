import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils
import numpy as np
from scipy.linalg import lu


tests_path = "../implementacion/tests/files/"

paginas, q_links, matriz = IO.readFileIn(filename=tests_path + "test_aleatorio.txt") 
p_value, solucion        = IO.readFileOut(filename=tests_path + "test_aleatorio.txt.out")

# IO.run(matriz=matriz, p_value=p_value, filename='./gen/in/ejemplo.txt', out_dir='./gen/out', debug=False)

# _p_value, _solucion = IO.readFileOut(filename='./gen/out/ejemplo.out')
ipwd = utils.W_to_IpWD(matriz, paginas, p_value)
e = np.full((paginas, 1), 1)
ipwd = np.concatenate([ipwd, e], axis=1)
print(ipwd)
print(lu(ipwd)[2])