#ifndef IMPLEMENTACION_MATRIZ_H
#define IMPLEMENTACION_MATRIZ_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;


const double EPSILON = 1e-4;


/**
 SOBRE EL DISEÑO:
 *
 *      matriz<R> busca ser una modulo base para la implementación de matrices de tipo real.
 *
 *      El objetivo es que esta clase sirva como 'caparazón' para cualquier representación
 *      particular de matriz sín tener que reimplementar el núcleo de las operaciones.
 *
 *      Para ello, se tomaron dos decisiones, importantes:
 *
 *      - El acceso a la estructura subyacente se limita a los getters / setters: at(), set()
 *      y a los iteradores. Estas funciones son las que funcionarán como interfáz interna 
 *      con la representación elegida.
 *
 *      - Toda operación es transparente referencialmente y construye la matríz resultado de
 *      izquierda a derecha, arriba para abajo. Para varias interfaces contempladas, generar
 *      una copia de esta manera es más rápido que modificar la estructura actual.
 *
 *      Un ejemplo de los requerimientos de la estructura se encuentra en ./matriz/matriz_base.h
 */


/**
 * Una matriz de double
 * @tparam R la estructura subyacente.
 */
template<class R>
class matriz {
protected:
    /** ESTRUCTURA */
    const size_t _n, _m;
    R _rep;

public:
    /** CONSTRUCTORES */
    matriz(size_t n, size_t m);
    template<class S> explicit matriz(const matriz<S> &b);
    matriz(const initializer_list<initializer_list<double>> &b);

    /** INTERFAZ */
    size_t n() const;
    size_t m() const;
    double at(size_t row, size_t col) const;
    void set(size_t row, size_t col, double elem);

    /** OPERADORES */
    template<class S> matriz &operator=(const matriz<S> &b);
    matriz &operator=(const initializer_list<initializer_list<double>> &b);

    template<class S> matriz operator+(const matriz<S> &b) const;
    template<class S> matriz operator-(const matriz<S> &b) const;
    matriz operator*(double b) const;
    template<class S> matriz operator*(const matriz<S> &b) const;
    template<class S> bool eq(const matriz<S> &b, double epsilon=EPSILON) const;

    /** OPERACIONES GAUSS */
    matriz gauss_elim() const;
    matriz gauss_elim(vector<double> &b) const;
    vector<double> solve(const vector<double> &b) const;

    /** ITERADORES */
    typename R::iterator begin(size_t i=0, size_t j=0);
    typename R::const_iterator begin(size_t i=0, size_t j=0) const;

    /** OTROS */
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
