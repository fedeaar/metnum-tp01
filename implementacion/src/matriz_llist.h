#ifndef IMPLEMENTACION_MATRIZ_LLIST_H
#define IMPLEMENTACION_MATRIZ_LLIST_H

#include "matriz.h"

#include <list>

class llist {
protected:
    struct elem {
        elem* nextInRow = nullptr;
        elem* prevInRow = nullptr;
        elem* nextInCol = nullptr;
        elem* prevInCol = nullptr;
        double val = 0;
        size_t row = -1;
        size_t col = -1;
    };
    const size_t _n, _m;           // tamaño
    vector<elem*> _inicioRow;      // extremos
    vector<elem*> _inicioCol;
    vector<elem*> _finCol;
    vector<elem*> _finRow;
    mutable vector<elem*> _last;   // cache

    // funciones
    elem* search(size_t row, size_t col, bool dir) const;
    void remove(elem* x);
    void set(elem* x, double val);

public:
    // constructor
    llist(size_t n, size_t m);

    // interfaz
    double at(size_t row, size_t col) const;
    void set(size_t row, size_t col, double elem);

    // iter
    class const_iterator;
    class iterator;

    iterator begin(size_t i, size_t j);
    const_iterator begin(size_t i, size_t j) const;
};


class llist::const_iterator {
protected:
    elem* _actual;
    const llist &_p;

public:
    const_iterator(const llist &p, size_t row=0, size_t col=0);

    bool in_range() const;
    size_t row() const;
    size_t col() const;
    double at() const;
    void next(bool rowOrder=true);
};


class llist::iterator : public llist::const_iterator {
protected:
    llist &_p;

public:
    explicit iterator(llist &p, size_t row=0, size_t col=0);
    void set(double elem);
};


#endif //IMPLEMENTACION_MATRIZ_LLIST_H
