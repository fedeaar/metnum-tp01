#ifndef IMPLEMENTACION_MATRIZ_H
#define IMPLEMENTACION_MATRIZ_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;


const double EPSILON = 1e-4;


template<class R>
class matriz {
protected:
    // estructura
    const size_t _n, _m;
    R _rep;

public:
    // constructores
    matriz(size_t n, size_t m);
    template<class S> explicit matriz(const matriz<S> &b);
    matriz(const initializer_list<initializer_list<double>> &b);

    // interfaz
    size_t n() const;
    size_t m() const;
    double at(size_t row, size_t col) const;
    void set(size_t row, size_t col, double elem);

    // operadores
    template<class S> matriz &operator=(const matriz<S> &b);
    matriz &operator=(const initializer_list<initializer_list<double>> &b);

    template<class S> matriz operator+(const matriz<S> &b) const;
    template<class S> matriz operator-(const matriz<S> &b) const;
    matriz operator*(double b) const;
    template<class S> matriz operator*(const matriz<S> &b) const;
    template<class S> bool eq(const matriz<S> &b, double epsilon=EPSILON) const;

    // gauss
    matriz gauss_elim() const;
    matriz gauss_elim(vector<double> &b) const;
    vector<double> solve(const vector<double> &b) const;

    // iter
    typename R::iterator begin(size_t i=0, size_t j=0);
    typename R::const_iterator begin(size_t i=0, size_t j=0) const;

    // otros
    ostream& print(ostream &os) const;
    void clear();
};


//
// OVERLOADS
//

template<class R>
ostream &operator<<(ostream &os, const matriz<R> &mat);

template<class R>
matriz<R> operator*(double b, const matriz<R> &a);


//
// OTRAS FUNCIONES
//
template<class R>
matriz<R> diagonal(const vector<double> &v);

template<class R>
matriz<R> identity(size_t n);


#include "impl/matriz.hpp"

#endif //IMPLEMENTACION_MATRIZ_H
