//
// TODO.
//

#ifndef IMPLEMENTACION_MATRIZCSR_H
#define IMPLEMENTACION_MATRIZCSR_H

#include "Matriz.h"
#include <vector>


/**
 * Una matriz con estructura CSR.
 * @tparam n > 0, cantidad de filas.
 * @tparam m > 0, cantidad de columnas.
 * @tparam T implementa operadores =, <, >, +, -, *. <<.
 */
template<std::size_t n, std::size_t m, class T>
class MatrizCSR : protected Matriz<n, m, T> {
private:
    /**
     ESTRUCTURA
     */
    std::vector<T> _m;
    std::vector<std::size_t> _jm;
    std::vector<std::size_t> _im;

public:
    /**
     CONSTRUCTORES
     * default, por copia, por array.
     */
    MatrizCSR();
    MatrizCSR(const MatrizCSR& b);
    MatrizCSR(const initializer_list<initializer_list<T>>& b);

    /**
     SET
     * modifica el elemento en la posición dada.
     * @param row 0 <= i < n, fila del elemento a guardar.
     * @param col 0 <= j < m, columna del elemento a guardar.
     */
    void set(std::size_t row, std::size_t col, T elem);

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
    T at(std::size_t row, std::size_t col) const;
};

#include "./impl/MatrizCSR.hpp"
#endif //IMPLEMENTACION_MATRIZCSR_H
