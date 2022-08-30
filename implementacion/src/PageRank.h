#ifndef IMPLEMENTACION_PAGERANK_H
#define IMPLEMENTACION_PAGERANK_H

#include "Matriz.h"
#include <vector>


namespace PageRank {

    struct coords {
        coords(size_t _i, size_t _j) : i(_i), j(_j) {}

        size_t i;
        size_t j;
    };
    struct params {
        params(size_t _p, size_t _l, double _val) : p_val(_val), paginas(_p), links(_l), relaciones(_l) {}

        double p_val;
        size_t paginas;
        size_t links;
        vector<coords> relaciones;
    };


    vector<double> solve(params& p);
};

#endif //IMPLEMENTACION_PAGERANK_H
