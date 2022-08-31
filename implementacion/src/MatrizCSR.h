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
 * @tparam T implementa operadores =, <, >, +, -, *, /, <<.
 */
template<class T>
class MatrizCSR : public Matriz<n, m, T> {
private:
    /**
     ESTRUCTURA
     */
    size_t _nz;
    vector<T> _m; // tamaño nz
    vector<size_t> _cols; // tamaño nz
    vector<size_t> _rows; // tamaño n+1
public:
    size_t n;
    size_t m;
    /**
     CONSTRUCTORES
     * default, por copia, por array.
     */
    MatrizCSR(size_t n, size_t m);
    MatrizCSR(const MatrizCSR& b);
    MatrizCSR(const initializer_list<initializer_list<T>>& b);

    /**
     SET
     * modifica el elemento en la posición dada.
     * @param row 0 <= i < n, fila del elemento a guardar.
     * @param col 0 <= j < m, columna del elemento a guardar.
     */
    void set(size_t row, size_t col, T elem);

    // /**
    //  REINDEX
    //  * modifica el orden de las filas o columnas.
    //  * @param i1 0 <= i < n ó m según el orden, fila o columna por la que intercambiar.
    //  * @param i2 0 <= j < n ó m según el orden, fila o columna por la que intercambiar.
    //  * @param rowOrder si true intercambia por fila, sino por columna.
    //  */
    //  void reindex(size_t i1, size_t i2, bool rowOrder=true);

    /**
     AT
     * @param row 0 <= i < n, fila del elemento a guardar.
     * @param col 0 <= j < m, columna del elemento a guardar.
     * @return una copia del elemento que está en la posición dada.
     */
    T at(size_t row, size_t col) const;
};

#include "./impl/MatrizCSR.hpp"
#endif //IMPLEMENTACION_MATRIZCSR_H
