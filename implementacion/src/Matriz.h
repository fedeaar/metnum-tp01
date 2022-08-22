//
// Estructura para matrices ralas y vectores
// Un vector es una matriz Nx1 ó 1xN
//

#ifndef IMPLEMENTACION_MATRIZ_H
#define IMPLEMENTACION_MATRIZ_H

#include <cstdlib>

template<std::size_t n, std::size_t m, class T>
class Matriz {
    Matriz();
    ~Matriz();
    Matriz operator+(const Matriz& b);
    Matriz operator-(const Matriz& b);
    Matriz operator*(const Matriz& b);

    template<typename numerico>
    Matriz operator*(const numerico& b);

    T* at(std::size_t i, std::size_t j);
};

#endif //IMPLEMENTACION_MATRIZ_H
