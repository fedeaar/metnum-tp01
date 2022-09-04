import pagerank_scripts.IO as IO


tests_path = "../implementacion/tests/files/"

paginas, q_links, matriz = IO.readFileIn(filename=tests_path + "test_aleatorio.txt") 
p_value, solucion        = IO.readFileOut(filename=tests_path + "test_aleatorio_desordenado.txt.out")

IO.run(matriz=matriz, p_value=p_value, filename='./gen/in/ejemplo.txt', out_dir='./gen/out', debug=True)

_p_value, _solucion = IO.readFileOut(filename='./gen/out/resultado.txt')

print('\n','error relativo test: ', _solucion - solucion)
