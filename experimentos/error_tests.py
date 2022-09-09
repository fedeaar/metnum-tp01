import pagerank_scripts.IO as IO
import pagerank_scripts.utils as utils

import os
import numpy as np


"""
descripcion: 
    medimos el error absoluto y relativo para los tests de la cátedra.
"""

# IO
EXPERIMENTO          = "error_tests"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS           = f"{DIR}{EXPERIMENTO}.csv"

TESTS_DIR = "../implementacion/tests/files/"
TESTS     = [x[:-4] for x in os.listdir(TESTS_DIR) if \
                    os.path.isfile(TESTS_DIR + x) and \
                    x[-4:] == ".txt" and \
                    x != "README.txt"]

# fmt
COLS       = 'test,error_abs,error_rel'
FMT_COLS   = "{0},{1},{2}\n"


# metodos
def crear_csv(): 

    if not os.path.exists(RESULTADOS):
        with open(RESULTADOS, "w", encoding="utf-8") as file:
            # columnas
            file.write(COLS  + '\n')


def correr_pagerank():

    for test in TESTS: 
        in_file = TESTS_DIR + test + ".txt"
        p, x = IO.readFileOut(in_file + ".out")
        IO.run(filename=in_file, 
            p_value=p,
            out_dir=DIR_OUT)


def medir_errores():

    for test in TESTS:

        in_file = TESTS_DIR + test + ".txt"
        p, x   = IO.readFileOut(DIR_OUT + test + ".out")
        
        # error relativo
        _p, xe = IO.readFileOut(in_file + ".out")
        assert(p == _p)
        error_rel = utils.norma_uno(x - xe) # tomamos el error máximo
        
        # error absoluto
        _, _, W = IO.readFileIn(in_file)
        A = utils.W_to_A(W, p)
        Ax = A @ x.T
        error_abs = utils.norma_uno(Ax - x) # tomamos el error máximo
        
        with open(RESULTADOS, 'a', encoding="utf-8") as file:
            file.write(FMT_COLS.format(test, error_abs, error_rel))




if __name__ == "__main__":
    # crear_csv()
    # correr_pagerank()
    medir_errores()
