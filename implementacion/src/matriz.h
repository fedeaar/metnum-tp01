/**
 SOBRE EL DISEÑO:
 *
 *      matriz<R> busca ser una modulo base para la implementación de matrices numericas.
 *
 *      El objetivo es que cualquier clase derivada pueda modificar la estructura subyacente
 *      sin tener que reimplementar el núcleo de las operaciones, salvo que así se desee para
 *      su optimización.
 *
 *      Para ello, se tomaron dos decisiones, principalmente:
 *
 *      - El acceso a la estructura se limita a los constructores y a los getters / setters:
 *      shape(), at(), set() y reindex(). Estas funciones son las únicas que se deberán
 *      sobreescribir. En particular, at() siempre deberá retornar una copia del elemento. La
 *      única forma de modificar una posición deberá ser por medio de set().
 *
 *      - toda operación es transparente referencialmente y construye la matríz resultado de
 *      izquierda a derecha, arriba para abajo. Para varias interfaces contempladas, generar
 *      una copia de esta manera es más rápido que modificar la estructura actual.
 */

#ifndef IMPLEMENTACION_MATRIZ_H
#define IMPLEMENTACION_MATRIZ_H

#include <cstdlib>
#include <cassert>
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;


template<class T>
class vlist;

/** ====================================================
 * Una matriz.
 * @tparam R la representacion interna
 * @tparam T numerico. Implementa: =, <, +, -, *, /, <<.
 ======================================================= */
template<class T=double, class R=vlist<T>>
class matriz {
private:
    /**
     ESTRUCTURA
     */
    R _rep;

protected:
// === ITERADORES === //
    /**
     CONST ITERATOR
     * un iterador constante genérico, puede recorrer toda la matriz.
     */
    class const_iterator {
    protected:
        /**
         ESTRUCTURA
         */
        size_t _row, _col;
        const matriz<T, R> &_p;

    public:
    // === CONSTRUCTORES / DESTRUCTOR === //
        /**
         CONSTRUCTOR
         * @param row 0 <= row < n, fila inicial.
         * @param col 0 <= col < m, columna inicial.
         */
        explicit const_iterator(const matriz<T, R> &p, size_t row=0, size_t col=0);

        /**
         DESTRUCTOR
         * default
         */
        ~const_iterator();


    // === OPERADORES === //
        /**
         EQUIV.
         */
        bool operator==(const const_iterator &b);

        /**
         IN RANGE
         * @return true si el iterador apunta a una posición válida en la matriz.
         */
        bool in_range();


    // === GETTERS / SETTERS === //
        /**
         ROW
         * @return la fila actual del iterador.
         */
        size_t row();

        /**
         COL
         * @return la columna actual del iterador.
         */
        size_t col();

        /**
         AT
         * @return una copia del elemento en la posición actual del iterador.
         */
        T at();

        /**
         NEXT
         * avanza el iterador.
         * @param rowOrder si true itera por fila, sino por columna.
         * @param wrap si true avanza a la proxima fila, o columna, al terminar la actual.
         */
        void next(bool rowOrder=true, bool wrap=true);

        /**
         NEXT DIAGONAL
         * avanza el iterador diagonalmente.
         */
        void next_diagonal();
    };

    /**
     ITERATOR
     * un iterador genérico, puede recorrer toda la matriz.
     */
     class iterator : public const_iterator {
     protected:
         /**
         ESTRUCTURA
         */
         matriz<T, R> &_p;

     public:
     // === CONSTRUCTORES / DESTRUCTOR === //
         /**
          CONSTRUCTOR
          * @param row 0 <= row < n, fila inicial.
          * @param col 0 <= col < m, columna inicial.
          */
         explicit iterator(matriz<T, R> &p, size_t row=0, size_t col=0);


     // === GETTERS / SETTERS === //
         /**
          SET
          * modifica el elemento en la posición actual del iterador.
          * @param elem el elemento a insertar.
          */
         void set(T elem);
     };

public:
// === CONSTRUCTORES / DESTRUCTOR === //
    /**
     CONSTRUCTORES
     */
    matriz(size_t n, size_t m);
    template<class S>
    explicit matriz(const matriz<T, S> &b);
    matriz(const initializer_list<initializer_list<T>> &b);

    /**
     DESTRUCTOR
     * default
     */
    ~matriz();


// === INTERFAZ === //

    const size_t &n() const;
    const size_t &m() const;
    T at(size_t row, size_t col) const;
    void set(size_t row, size_t col, T elem);
    void swap(size_t i1, size_t i2, bool rowOrder);


// === OPERADORES === //
    /**
     ASSIGN
     */
    template<class S>
    matriz &operator=(const matriz<T, S> &b);
    matriz &operator=(const initializer_list<initializer_list<T>> &b);

    /**
     SUMA
     */
    template<class S>
    matriz operator+(const matriz<T, S> &b) const;

    /**
     RESTA
     */
    template<class S>
    matriz operator-(const matriz<T, S> &b) const;

    /**
     PRODUCTO POR ESCALAR
     */
    matriz operator*(const T &b) const;

    /**
     PRODUCTO
     * @param b es una matriz con M filas.
     */
    template<class S>
    matriz operator*(const matriz<T, S> &b) const;

    /**
     EQ
     * @param epsilon cota de error máxima
     * @return true si para cada a_ij en la matriz y b_ij en b, | a_ij - b_ij | < epsilon.
     */
    template<class S>
    bool eq(const matriz<T, S> &b, double epsilon=1e-4) const;


// === GAUSS === //
    /**
     GAUSS SWAP
     * @param i1 0 <= i1 < n ó m según el orden. Fila o columna a intercambiar.
     * @param i2 0 <= i2 < n ó m según el orden. Segunda fila o columna a intercambiar.
     * @param rowOrder si true intercambia por fila, sino por columna.
     */
    matriz gauss_swap(size_t i1, size_t i2, bool rowOrder=true) const;

    /**
     GAUSS MULT
     * OBS: multiplcar por columna NO resulta en una matriz equivalente.
     * @param i 0 <= i < n ó m según el orden. Fila o columna a multiplicar.
     * @param val un escalar.
     * @param rowOrder si true intercambia por fila, sino por columna.
     */
    matriz gauss_mult(size_t i, const T &val, bool rowOrder=true) const;

    /**
     GAUSS SUM
     * OBS: sumar por columna NO resulta en una matriz equivalente.
     * @param i1 0 <= i < n ó m según el orden, fila o columna destino de la suma.
     * @param i2 0 <= j < n ó m según el orden, fila o columna fuente de la suma.
     * @param val un escalar.
     * @param rowOrder si true intercambia por fila, sino por columna.
     * @returns Una matriz M' casi equivalente a la instancia, salvo para la fila o columna M'_i1,
     * que ahora satisface M'_i1 = M_i1 + M_i2 * val.
     */
    matriz gauss_sum(size_t i1, size_t i2, const T &val, bool rowOrder=true) const;

    /**
     ELIMINACION GAUSSIANA
     * pre: A_ii != 0 para i: 0 ... N y b.size() == N
     * @param b vector solucion, se modifica para ser solucion de la matriz resultante.
     * @return una matriz triangular superior equivalente a la actual.
     */
    matriz gauss_elim() const;
    matriz gauss_elim(vector<T> &b) const;

    /**
     SOLVE
     * pre: A_ii != 0 para i: 0 ... N despues de triangular y N == M y b.size() == N.
     * @return una solución al sistema Ax = b.
     */
    vector<T> solve(const vector<T> &b);


// === BEGIN / END === //
    /**
     BEGIN
     * @param i 0 <= i < n, fila inicial.
     * @param j 0 <= j < m, columna inicial.
     * @return un iterador para la posición dada.
     */
    iterator begin(size_t i=0, size_t j=0);
    const_iterator begin(size_t i=0, size_t j=0) const;

    /**
     END
     * @return un iterador fuera de rango, equivalente a cualquier iterador
     * que no satisface 0 <= i < n && 0 <= j < m.
     */
    iterator end();
    const_iterator end() const;


// === STREAM === //
    /**
     PRINT
     */
    ostream& print(ostream &os) const;
};




//
// OVERLOADS
//

/**
 << OVERLOAD
 * permite imprimir una matriz, ej. cout << A.
 */
template<class T=double, class R=vlist<T>>
ostream &operator<<(ostream &os, const matriz<T, R> &mat);

/**
 PRODUCTO POR ESCALAR
 * overload global para R * matriz (orden inverso de los operandos).
 */
template<class T=double, class R=vlist<T>>
matriz<T, R> operator*(const T &b, const matriz<T, R> &a);


//
// OTRAS FUNCIONES
//

/**
 IDENTIDAD
 * @return una matriz identidad n * n.
 */
template<class T=double, class R=vlist<T>>
matriz<T, R> identity(size_t n);

/**
 DIAGONAL
 * @return una matriz diagonal con los elementos de v.
 */
template<class T=double, class R=vlist<T>>
matriz<T, R> diagonal(const vector<T> &v);


#include "matriz-repr.h"
#include "impl/matriz/matriz.hpp"
#include "impl/matriz/matriz-interfaz.hpp"
#include "impl/matriz/matriz-operadores.hpp"
#include "impl/matriz/matriz-iteradores.hpp"
#include "impl/matriz/matriz-gauss.hpp"
#endif //IMPLEMENTACION_MATRIZ_H
