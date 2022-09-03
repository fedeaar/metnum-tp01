#ifndef IMPLEMENTACION_MATRIZ_BASE_H
#define IMPLEMENTACION_MATRIZ_BASE_H

#include "matriz.h"

using namespace std;


class base {
protected:
    const size_t _n, _m;            // tamaño
    vector<vector<double>> _mat;    // matriz

public:
    // constructor
    base(size_t n, size_t m);

    // interfaz
    double at(size_t row, size_t col) const;
    void set(size_t row, size_t col, double elem);

    // iter
    class const_iterator;
    class iterator;

    iterator begin(size_t i, size_t j);
    const_iterator begin(size_t i, size_t j) const;
};


class base::const_iterator {
protected:
    size_t _row, _col;
    const base &_p;

public:
    explicit const_iterator(const base &p, size_t row=0, size_t col=0);

    bool in_range() const;
    size_t row() const;
    size_t col() const;
    double at() const;
    void next(bool rowOrder=true);
};


class base::iterator : public base::const_iterator {
protected:
    base &_p;

public:
    explicit iterator(base &p, size_t row=0, size_t col=0);
    void set(double elem);
};

#endif //IMPLEMENTACION_MATRIZ_BASE_H
