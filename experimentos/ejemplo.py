import pagerank_scripts.IO as IO
import numpy as np

tests_path = "../implementacion/tests/files/"

paginas, q_links, matriz = IO.readFileIn(filename=tests_path + "test_15_segundos.txt") 
p_value, solucion        = IO.readFileOut(filename=tests_path + "test_15_segundos.txt.out")

IO.run(matriz=matriz, p_value=p_value, filename='./gen/in/ejemplo.txt', out_dir='./gen/out', debug=False)

_p_value, _solucion = IO.readFileOut(filename='./gen/out/ejemplo.out')

print('\n\n','error relativo test: ', _solucion - solucion)


D = np.eye(2000)
rango = matriz.sum(axis=0)
for i in range(200):
    D[i][i] = 1 / rango[i] if rango[i] != 0 else 0

IpWD = np.eye(2000) - _p_value * matriz @ D

sol_np = np.linalg.solve(IpWD, np.full((2000, 1), 1))
sol_np = sol_np / np.sum(sol_np)

print('\n', 'error relativo con numpy: ', sol_np.T - _solucion)
