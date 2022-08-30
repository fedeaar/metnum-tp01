//
// TODO.
//

#ifndef IMPLEMENTACION_MATRIZALT_H
#define IMPLEMENTACION_MATRIZALT_H

#include "Matriz.h"
#include <vector>


/**
 * Una matriz con estructura alternativa.
 * @tparam n > 0, cantidad de filas.
 * @tparam m > 0, cantidad de columnas.
 * @tparam T implementa operadores =, <, >, +, -, *, /, <<
 */
template<size_t n, size_t m, class T>
class MatrizALT : public Matriz<n, m, T> {
private:
    /**
     ESTRUCTURA
     */
    struct elem {
        int col;
        T val;
    }

    struct cache {
        int from = 0;
        int to = m;
        int next = m;
        int pos = 0;
    }
    std::array<std::vector<elem, m>, n> _m;
    std::array<cache, n> _last;
    int search(size_t row, size_t col);
    void updateLast(size_t row, size_t pos);
public:
    /**
     CONSTRUCTORES
     * default, por copia, por array.
     */
    MatrizALT();
    MatrizALT(const MatrizALT& b);
    MatrizALT(const initializer_list<initializer_list<T>>& b);

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

};

#include "./impl/MatrizALT.hpp"
#endif //IMPLEMENTACION_MATRIZALT_H
