#ifndef IMPLEMENTACION_REPRESENTACIONES_H
#define IMPLEMENTACION_REPRESENTACIONES_H

#include <vector>
#include <cassert>
#include "matriz.h"

using namespace std;


template<class T>
class base {
protected:
    const size_t _n, _m;        // tamaño
    vector<vector<T>> _mat;     // matriz
    vector<size_t> _row, _col;  // indice de filas, columnas

public:
    base(size_t n, size_t m);

    const size_t &n() const;
    const size_t &m() const;
    T at(size_t row, size_t col) const;
    void set(size_t row, size_t col, T elem);
    void swap(size_t i1, size_t i2, bool rowOrder);
};


template<class T>
class alt {
protected:
    struct elem {
        int col = 0;
        T val {};
    };
    struct cache {
        int from = 0;
        int to = 0;
        int next = 0;
        int pos = 0;
    };
    size_t _n, _m;               // tamaño
    vector<vector<elem>> _mat;   // matriz
    mutable vector<cache> _last; // cache

    void updateLast(size_t row, size_t pos) const;
    size_t search(size_t row, size_t col) const;

public:
    alt(size_t n, size_t m);

    const size_t &n() const;
    const size_t &m() const;
    T at(size_t row, size_t col) const;
    void set(size_t row, size_t col, T val);
    void swap(size_t i1, size_t i2, bool rowOrder);

    class iterador_rapido {
    protected:
        size_t _row, _pos;
        const alt<T> &_p;

    public:
        iterador_rapido(const alt<T> &p, size_t row, size_t col);
        T at();
        void next(bool wrap=true);
        bool in_range();
        size_t col();
        size_t row();
    };

    iterador_rapido begin(size_t i=0, size_t j = 0) const;
};

#include "impl/matriz/matriz-repr-base.hpp"
#include "impl/matriz/matriz-repr-alt.hpp"
#endif //IMPLEMENTACION_REPRESENTACIONES_H
