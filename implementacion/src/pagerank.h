#ifndef IMPLEMENTACION_PAGERANK_H
#define IMPLEMENTACION_PAGERANK_H

#include "matriz.h"


namespace pagerank {

    /** ESTRUCTURAS DE DATOS */
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

    /** CONSTRUIR */
    template<class R> matriz<R> make(const in_file &params);

    /** PAGERANK */
    template<class R> vector<double> solve(const matriz<R>& mat);
};


#include "./impl/pagerank.hpp"
#endif //IMPLEMENTACION_PAGERANK_H
