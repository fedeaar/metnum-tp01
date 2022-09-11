import base.IO as IO
import base.utils as utils

import os
import numpy as np


"""
descripcion: 
    medimos el error absoluto (L1), maximo y relativo para los tests de la cátedra.
"""

# IO
EXPERIMENTO          = "error_tests"
DIR_IN, DIR_OUT, DIR = IO.createInOut(EXPERIMENTO)    
RESULTADOS           = f"{DIR}{EXPERIMENTO}.csv"

TESTS_DIR = "../catedra/"
TESTS     = [x[:-4] for x in os.listdir(TESTS_DIR) if \
                    os.path.isfile(TESTS_DIR + x) and \
                    x[-4:] == ".txt" and \
                    x != "README.txt"]

# fmt
COLS       = 'test,error_abs,error_rel,error_max'
FMT_COLS   = "{0},{1},{2},{3}\n"


# metodos
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
        
        # error absoluto
        _p, xe = IO.readFileOut(in_file + ".out")

        assert(abs(p - _p) < 1e-4)
        error_abs = utils.norma_uno(x - xe)
        por_coordenada = x - xe
        error_max = utils.norma_inf(por_coordenada)

        with open(DIR + test + "_error_por_coordenada.txt", 'w', encoding="utf-8") as file:
            for y in por_coordenada:
                file.write(f"{y}\n")

        # error relativo
        _, _, W = IO.readFileIn(in_file)
        A = utils.W_to_A(W, p)
        Ax = A @ x.T
        error_rel = utils.norma_uno(Ax - x)
        
        with open(RESULTADOS, 'a', encoding="utf-8") as file:
            file.write(FMT_COLS.format(test, error_abs, error_rel, error_max))




if __name__ == "__main__":
    IO.createCSV(RESULTADOS, COLS)
    correr_pagerank()
    medir_errores()
