//
// Estructura base para una matríz
//

/**
 SOBRE EL DISEÑO:
 *
 *      Matriz<n, m, T> busca ser una modulo base para la implementación de matrices.
 *
 *      El objetivo es que cualquier clase derivada pueda modificar la estructura subyacente
 *      sin tener que reimplementar el núcleo de las operaciones, salvo que así se desee para
 *      su optimización.
 *
 *      Para ello, se tomaron dos decisiones, principalmente:
 *
 *      - El acceso a la estructura se limita a los constructores y a los getters / setters:
 *      at(), set() y reindex(). Estas funciones son las únicas que se deberán sobreescribir.
 *      En particular, at() siempre deberá retornar una copia del elemento. La única forma de
 *      modificar una posición deberá ser por medio de set().
 *
 *      - toda operación es transparente referencialmente y construye la matríz resultado de
 *      izquierda a derecha, arriba para abajo. Para varias interfaces contempladas, generar
 *      una copia de esta manera es más rápido que modificar la estructura actual.
 */


#ifndef IMPLEMENTACION_MATRIZ_H
#define IMPLEMENTACION_MATRIZ_H

#include <cstdlib>
#include <cassert>
#include <array>
#include <numeric>

using namespace std;


/** ==================================================
 * Una matriz.
 * @tparam n > 0, cantidad de filas.
 * @tparam m > 0, cantidad de columnas.
 * @tparam T implementa: =, <, +, -, *. <<.
 ===================================================== */
template<size_t n, size_t m, class T>
class Matriz {
private:
    /**
     ESTRUCTURA
     */
    array<array<T, m>, n> _m;   // matriz
    array<size_t, n> _row;      // indice de filas
    array<size_t, m> _col;      // indice de columnas

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
        const Matriz<n, m, T> &_p;

    public:
        // === CONSTRUCTORES / DESTRUCTOR === //
        /**
         CONSTRUCTOR
         * @param row 0 <= row < n, fila inicial.
         * @param col 0 <= col < m, columna inicial.
         */
        explicit const_iterator(const Matriz<n, m, T> &p, size_t row=0, size_t col=0);

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
         * @param rowOrder si true avanza por fila, sino por columna.
         * @param wrap si true avanza a la proxima fila, o columna, al terminar la actual.
         */
        void next(bool rowOrder=true, bool wrap=true);
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
         Matriz<n, m, T> &_p;

     public:
         // === CONSTRUCTORES / DESTRUCTOR === //
         /**
          CONSTRUCTOR
          * @param row 0 <= row < n, fila inicial.
          * @param col 0 <= col < m, columna inicial.
          */
         explicit iterator(Matriz<n, m, T> &p, size_t row=0, size_t col=0);


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
     * default, por copia, por array.
     */
    Matriz();
    Matriz(const Matriz& b);
    Matriz(const initializer_list<initializer_list<T>> &b);

    /**
     DESTRUCTOR
     * default
     */
    ~Matriz();


    // === OPERADORES === //
    /**
     ASSIGN
     */
    Matriz &operator=(const Matriz &b);
    Matriz &operator=(const std::initializer_list<initializer_list<T>> &b);

    /**
     SUMA
     */
    Matriz operator+(const Matriz &b) const;

    /**
     RESTA
     */
    Matriz operator-(const Matriz &b) const;

    /**
     PRODUCTO POR ESCALAR
     */
    Matriz operator*(const T &b) const;

    /**
     PRODUCTO
     * @param b es una matriz con M filas.
     */
    template<size_t l>
    Matriz<n, l, T> operator*(const Matriz<m, l, T> &b) const;

    /**
     EQ
     * @param epsilon cota de error máxima
     * @return true si para cada a_ij en la matriz y b_ij en b, | a_ij - b_ij | < epsilon.
     */
    bool eq(const Matriz &b, double epsilon=1e-4) const;


    // === GAUSS === //
    /**
     GAUSS SWAP
     * @param i1 0 <= i1 < n ó m según el orden. Fila o columna a intercambiar.
     * @param i2 0 <= i2 < n ó m según el orden. Segunda fila o columna a intercambiar.
     * @param rowOrder si true intercambia por fila, sino por columna.
     */
    Matriz gauss_swap(size_t i1, size_t i2, bool rowOrder=true) const;

    /**
     GAUSS MULT
     * OBS: multiplcar por columna NO resulta en una matriz equivalente.
     * @param i 0 <= i < n ó m según el orden. Fila o columna a multiplicar.
     * @param val un escalar.
     * @param rowOrder si true intercambia por fila, sino por columna.
     */
    Matriz gauss_mult(size_t i, const T &val, bool rowOrder= true) const;

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
    Matriz gauss_sum(size_t i1, size_t i2, const T &val, bool rowOrder=true) const;

    /**
     ELIMINACION GAUSSIANA
     * pre: n = m && M_ii != 0 para i: 0 ... N.
     * @return una matriz triangular superior equivalente a la actual.
     */
    Matriz gauss_elim() const; // TODO


    // === GETTERS / SETTERS === //
    /**
     SET
     * modifica el elemento en la posición dada.
     * @param row 0 <= i < n, fila del elemento a guardar.
     * @param col 0 <= j < m, columna del elemento a guardar.
     */
    void set(size_t row, size_t col, T elem);

    /**
     REINDEX
     * modifica el orden de las filas o columnas.
     * @param i1 0 <= i < n ó m según el orden, fila o columna por la que intercambiar.
     * @param i2 0 <= j < n ó m según el orden, fila o columna por la que intercambiar.
     * @param rowOrder si true intercambia por fila, sino por columna.
     */
    void reindex(size_t i1, size_t i2, bool rowOrder=true);

    /**
     AT
     * @param row 0 <= i < n, fila del elemento a guardar.
     * @param col 0 <= j < m, columna del elemento a guardar.
     * @return una copia del elemento que está en la posición dada.
     */
    T at(size_t row, size_t col) const;


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
    ostream& print(ostream& os) const;
};


/**
 << OVERLOAD
 * permite imprimir una matriz, ej. cout << A.
 */
template<size_t n, size_t m, class T>
ostream &operator<<(ostream &os, const Matriz<n, m, T>& _m);

/**
 PRODUCTO POR ESCALAR
 * overload global para T * Matriz (orden inverso de los operandos).
 */
template<size_t n, size_t m, class T>
Matriz<n, m, T> operator*(const T &b, const Matriz<n, m, T> &a);


#include "./impl/Matriz.hpp"
#include "./impl/Matriz-iteradores.hpp"
#include "./impl/Matriz-gauss.hpp"
#endif //IMPLEMENTACION_MATRIZ_H
