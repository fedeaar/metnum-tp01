#ifndef IMPLEMENTACION_REPRESENTACIONES_H
#define IMPLEMENTACION_REPRESENTACIONES_H

#include <vector>
#include <list>
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

// template<class T>
// class llist {
// protected:
//     struct elem {
//         elem* nextInRow = nullptr;
//         elem* prevInRow = nullptr;
//         elem* nextInCol = nullptr;
//         elem* prevInCol = nullptr;
//         T val {};
//         size_t row = -1;
//         size_t col = -1;
//     };

//     size_t _n, _m;               // tamaño
//     vector<elem*> _last; // cache
//     elem* search(size_t row, size_t col, bool dir) const;

//     vector<elem*> _inicioRow;  
//     vector<elem*> _inicioCol;  
//     vector<elem*> _finCol;  
//     vector<elem*> _finRow; 
// public:
//     llist(size_t n, size_t m);

//     elem* inicioRow(size_t row);
//     elem* finRow(size_t row);
//     elem* inicioCol(size_t col);
//     elem* finCol(size_t col);
//     const size_t &n() const;
//     const size_t &m() const;
//     T at(size_t row, size_t col) const;
//     void remove(elem* x);
//     void set(size_t row, size_t col, T val);
//     void set(elem* x, T val);
//     void swap(size_t i1, size_t i2, bool rowOrder);

//     class iterador_rapido {
//     protected:
//         elem* _actual;
//         const llist<T> &_p;

//     public:
//         iterador_rapido(const llist<T> &p, size_t row, size_t col);
//         iterador_rapido(const iterador_rapido& it);
//         T at();
//         void next(bool wrap=true);
//         void nextInCol();
//         void remove(bool dir=true);
//         void set(T val);
//         bool in_range();
//         size_t col();
//         size_t row();
//     };

//     iterador_rapido begin(size_t i=0, size_t j = 0) const;
//     iterador_rapido begin(const iterador_rapido& it) const;
// };

template<class T>
class vlist {
protected:
    size_t _n, _m;
public:
    struct elem {
        T val {};
        size_t col = -1;
    };
    vector<list<elem>> _mat;
    vlist(size_t n, size_t m);

    const size_t &n() const;
    const size_t &m() const;
    T at(size_t row, size_t col) const;
    void set(size_t row, size_t col, T val);
    void set(typename list<elem>::iterator it, size_t row, size_t col, T val);
    void swap(size_t i1, size_t i2, bool rowOrder);

    class iterador_rapido {
    protected:
        size_t _row;
        size_t _col;
        const vlist<T> &_p;

    public:
        iterador_rapido(const vlist<T> &p, size_t row, size_t col);
        T at();
        void next(bool wrap=true);
        bool in_range();
        size_t col();
        size_t row();
    };

    iterador_rapido begin(size_t i=0, size_t j = 0) const;
    iterador_rapido begin(const iterador_rapido& it) const;
};

template<class T>
bool compCero(T a) {
    return abs((double) a) < 1e-4;
}
#include "impl/matriz/matriz-repr-base.hpp"
#include "impl/matriz/matriz-repr-vlist.hpp"
// #include "impl/matriz/matriz-repr-list.hpp"
#include "impl/matriz/matriz-repr-alt.hpp"
#endif //IMPLEMENTACION_REPRESENTACIONES_H
