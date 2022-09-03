#ifndef IMPLEMENTACION_PAGERANK_H
#define IMPLEMENTACION_PAGERANK_H

#include "matriz_base.h"
#include "../src/matriz_base.h"
#include "../src/matriz_alt.h"
#include "../src/matriz_llist.h"

#if ESTR == 1
    typedef base __ESTR__;
#elif ESTR == 2
    typedef alt __ESTR__;
#elif ESTR == 3
    typedef llist __ESTR__;
#else
    typedef alt __ESTR__;
#endif


namespace pagerank {
    struct coords {
        coords(size_t _i, size_t _j) : i(_i), j(_j) {}

        size_t i;
        size_t j;
    };
    struct in_file {
        in_file(size_t _p, size_t _l, double _val) : p_val(_val), paginas(_p), links(_l), relaciones() {}

        double p_val;
        size_t paginas;
        size_t links;
        vector<coords> relaciones;
    };

    struct out_file {
        explicit out_file(double _p_val) : p_val(_p_val), solucion() {}
        double p_val;
        vector<double> solucion;
    };

    vector<double> solve(in_file &params);

    vector<double> solve_optimizado(in_file &params);
};

#endif //IMPLEMENTACION_PAGERANK_H
