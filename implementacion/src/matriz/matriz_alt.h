#ifndef IMPLEMENTACION_MATRIZ_ALT_H
#define IMPLEMENTACION_MATRIZ_ALT_H

#include "../matriz.h"

using namespace std;


class alt {
protected:
    struct elem {
        size_t col = 0;
        double val = 0;
    };
    struct cache {
        size_t from = 0;
        size_t to = 0;
        size_t next = 0;
        size_t pos = 0;
    };
    const size_t _n, _m;         // tamaño
    vector<vector<elem>> _mat;   // matriz
    mutable vector<cache> _last; // cache

    // funciones privadas
    void updateLast(size_t row, size_t pos) const;
    size_t search(size_t row, size_t col) const;
    bool count(size_t row, size_t col) const;

public:
    // constructor
    alt(size_t n, size_t m);

    // interfaz
    double at(size_t row, size_t col) const;
    void set(size_t row, size_t col, double val);

    // iter
    class const_iterator;
    class iterator;

    iterator begin(size_t i, size_t j);
    const_iterator begin(size_t i, size_t j) const;
};


class alt::const_iterator {
protected:
    size_t _row, _col_pedida, _pos;
    const alt &_p;

public:
    explicit const_iterator(const alt &p, size_t row=0, size_t col=0);

    bool in_range() const;
    size_t row() const;
    size_t col() const;
    double at() const;
    void next(bool rowOrder=true);
};


class alt::iterator : public alt::const_iterator {
protected:
    alt &_p;

public:
    explicit iterator(alt &p, size_t row=0, size_t col=0);
    void set(double elem);
};

#endif //IMPLEMENTACION_MATRIZ_ALT_H
