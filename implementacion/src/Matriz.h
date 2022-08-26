//
// Estructura para matrices ralas y vectores
// Un vector es una matriz Nx1 ó 1xN
//

#ifndef IMPLEMENTACION_MATRIZ_H
#define IMPLEMENTACION_MATRIZ_H

#include <cstdlib>
#include <array>
#include <numeric>
#include <cassert>


/**
 * Una matriz.
 * @tparam n > 0, cantidad de filas.
 * @tparam m > 0, cantidad de columnas.
 * @tparam T implementa operadores =, ==, +, -, *.
 */
template<std::size_t n, std::size_t m, class T>
class Matriz {
private:
    std::array<std::array<T, m>, n> _m;
    std::array<std::size_t, n> _row;
    std::array<std::size_t, m> _col;

    class iterator {
    protected:
        std::size_t _i, _j;

    public:
        explicit iterator(std::size_t i=0, std::size_t j=0);
        ~iterator();

        bool operator==(const iterator &b);

        std::size_t i();
        std::size_t j();
        void next(bool rowOrder=true, bool wrap=true);
        bool inRange();
    };
    class row_iterator: iterator {
        void next();
    };
    class col_iterator: iterator {
        void next();
    };

public:
    Matriz();
    Matriz(const Matriz& b);
    Matriz(T (&a)[n][m]);
    ~Matriz();

    Matriz &operator=(const Matriz &b);
    Matriz operator+(const Matriz &b);
    Matriz operator-(const Matriz &b);
    Matriz operator*(const T &b);
    Matriz swap(std::size_t i, std::size_t j, bool rowOrder=true);

    template<std::size_t l>
    Matriz<n, l, T> operator*(const Matriz<m, l, T> &b);

    T &at(std::size_t i, std::size_t j);
    const T &at(std::size_t i, std::size_t j) const;
    T &at(iterator it);
    const T &at(iterator it) const;

    iterator begin(std::size_t i=0, std::size_t j=0);
    iterator end();

    std::ostream& print(std::ostream& os) const;
};

template<std::size_t n, std::size_t m, class T>
std::ostream &operator<<(std::ostream &os, const Matriz<n, m, T>& _m);

#include "./impl/Matriz.hpp"
#endif //IMPLEMENTACION_MATRIZ_H
