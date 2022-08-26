// Estructura para matrices ralas y vectores
// Un vector es una matriz Nx1 ó 1xN

using namespace std;
#ifndef IMPLEMENTACION_MATRIZ_H
#define IMPLEMENTACION_MATRIZ_H


// ================================= INCLUDES =================================
#include <cstdlib>
#include <array>
#include <numeric>
#include <cassert>



/** ===============================================
 * Una matriz.
 * @tparam n > 0, cantidad de filas.
 * @tparam m > 0, cantidad de columnas.
 * @tparam T implementa operadores =, ==, +, -, *.
 =============================================== */


template<size_t n, size_t m, class T>
class Matriz {
// ================================== PRIVATE ==================================
private:

    // -------------------- VARIABLES --------------------
    array<array<T, m>, n> _m;           // Matriz
    array<size_t, n> _row;              // Filas
    array<size_t, m> _col;              // Columnas

    // -------------------- ITERATOR --------------------
    class iterator {
    protected:
        size_t _i, _j;

    public:
        explicit iterator(size_t i=0, size_t j=0);
        ~iterator();

        bool operator==(const iterator &b);

        size_t i();
        size_t j();
        void next(bool rowOrder=true, bool wrap=true);
        bool inRange();
    };

    class row_iterator: iterator {
        void next();
    };

    class col_iterator: iterator {
        void next();
    };

// ================================== PUBLIC ==================================
public:
    Matriz();
    Matriz(const Matriz& b);
    Matriz(T (&a)[n][m]);
    ~Matriz();

    // ------------------------ OPERACIONES BÁSICAS ------------------------
    Matriz &operator=(const Matriz &b);                                     // Asignación
    Matriz operator+(const Matriz &b);                                      // Suma lugar a lugar
    Matriz operator-(const Matriz &b);                                      // Resta lugar a lugar
    Matriz operator*(const T &b);                                           // Producto escalar, lugar a lugar

    // ------------------- OPERACIONES DE FILAS/COLUMNAS -------------------
    Matriz swap(size_t i, size_t j, bool rowOrder=true);                    // Intercambio de filas/columnas
    Matriz sum(size_t dest, size_t orig, const T &b, bool rowOrder=true);   // Suma fila/columna origen multiplicada por un escalar b en fila/columna destino

    template<size_t l>
    Matriz<n, l, T> operator*(const Matriz<m, l, T> &b);                    // Producto matricial, fila por columna

    T &at(size_t i, size_t j);
    const T &at(size_t i, size_t j) const;
    T &at(iterator it);
    const T &at(iterator it) const;

    iterator begin(size_t i=0, size_t j=0);
    iterator end();

    ostream& print(ostream& os) const;
};

template<size_t n, size_t m, class T>
ostream &operator<<(ostream &os, const Matriz<n, m, T>& _m);

#include "./impl/Matriz.hpp"
#endif //IMPLEMENTACION_MATRIZ_H
