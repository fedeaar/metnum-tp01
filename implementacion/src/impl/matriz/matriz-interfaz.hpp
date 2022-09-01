#include "../../matriz.h"


//
// INTERFAZ
//

template<class T, class R>
const size_t &matriz<T, R>::n() const {
    return _rep.n();
}


template<class T, class R>
const size_t &matriz<T, R>::m() const {
    return _rep.m();
}


template<class T, class R>
T matriz<T, R>::at(size_t row, size_t col) const {
    return _rep.at(row, col);
}


template<class T, class R>
void matriz<T, R>::set(size_t row, size_t col, T elem) {
    _rep.set(row, col, elem);
}


template<class T, class R>
void matriz<T, R>::swap(size_t i1, size_t i2, bool rowOrder) {
    _rep.swap(i1, i2, rowOrder);
}
