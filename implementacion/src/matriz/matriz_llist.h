#ifndef IMPLEMENTACION_MATRIZ_LLIST_H
#define IMPLEMENTACION_MATRIZ_LLIST_H

#include "../matriz.h"

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
    elem* inicioRow(size_t row) const;
    elem* finRow(size_t row) const;
    elem* inicioCol(size_t col) const;
    elem* finCol(size_t col) const;
    elem* search(size_t row, size_t col, bool dir) const;
    void remove(elem* x);
    // void set(elem* x, double val);

public:
    // constructor
    llist(size_t n, size_t m);

    // interfaz
    double at(size_t row, size_t col) const;
    void set(size_t row, size_t col, double elem);

    // iter
    class const_iterator;
    class iterator;

    iterator begin(size_t i=0, size_t j=0);
    iterator begin(const iterator &it); // obs: ninguna funcion de matriz inicializa por it
    const_iterator begin(size_t i=0, size_t j=0) const;
    const_iterator begin(const const_iterator &it) const; // obs: ninguna funcion de matriz inicializa por it
};


class llist::const_iterator {
protected:
    elem* _actual;
    const llist &_p;

public:
    explicit const_iterator(const llist &p, size_t row=0, size_t col=0);
    const_iterator(const const_iterator &p); // obs: ninguna funcion de matriz inicializa por it

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
    iterator(const iterator &p); // obs: ninguna funcion de matriz inicializa por it

    void set(double elem);
    void remove(bool rowOrder=true); // obs: ninguna funcion de matriz usa remove
};


#endif //IMPLEMENTACION_MATRIZ_LLIST_H
