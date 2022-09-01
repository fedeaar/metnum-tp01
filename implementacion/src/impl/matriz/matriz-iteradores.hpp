#include "../../matriz.h"


//
// CONSTRUCTORES / DESTRUCTOR
//

template<class T, class R>
matriz<T, R>::const_iterator::const_iterator(const matriz<T, R> &p, size_t row, size_t col):
    _row(row), _col(col), _p(p) {}


template<class T, class R>
matriz<T, R>::const_iterator::~const_iterator() = default;




//
// OPERADORES
//

template<class T, class R>
bool matriz<T, R>::const_iterator::operator==(const const_iterator& b) {
    // apuntan al mismo lado o ambos son inválidos.
    return _row == b._row && _col == b._col || !in_range() && !b.in_range();
}


template<class T, class R>
bool matriz<T, R>::const_iterator::in_range() {
    return 0 <= _row && _row < _p.n() && 0 <= _col && _col < _p.m();
}




//
// GETTERS / SETTERS
//

template<class T, class R>
size_t matriz<T, R>::const_iterator::row() {
    return _row;
}


template<class T, class R>
size_t matriz<T, R>::const_iterator::col() {
    return _col;
}


template<class T, class R>
T matriz<T, R>::const_iterator::at() {
    return _p.at(row(), col());
}


template<class T, class R>
void matriz<T, R>::const_iterator::next(bool rowOrder, bool wrap) {
    if (rowOrder) {
        ++_col;
        if (wrap && _col >= _p.m()) {
            ++_row;
            _col = 0;
        }
    } else {
        ++_row;
        if (wrap && _row >= _p.n()) {
            ++_col;
            _row = 0;
        }
    }
}


template<class T, class R>
void matriz<T, R>::const_iterator::next_diagonal() {
    ++_row;
    ++_col;
}




//
// ITERADOR
//

template<class T, class R>
matriz<T, R>::iterator::iterator(matriz<T, R> &p, size_t row, size_t col): const_iterator(p, row, col), _p(p) {}


template<class T, class R>
void matriz<T, R>::iterator::set(T elem) {
    _p.set(const_iterator::row(), const_iterator::col(), elem);
}




//
// MATRIZ:: BEGIN / END
//

template<class T, class R> typename
matriz<T, R>::iterator matriz<T, R>::begin(size_t i, size_t j) {
    return iterator(*this, i, j);
}


template<class T, class R> typename
matriz<T, R>::const_iterator matriz<T, R>::begin(size_t i, size_t j) const {
    return const_iterator(*this, i, j);
}


template<class T, class R> typename
matriz<T, R>::iterator matriz<T, R>::end() {
    return iterator(*this, -1, -1);
}


template<class T, class R> typename
matriz<T, R>::const_iterator matriz<T, R>::end() const {
    return const_iterator(*this, -1, -1);
}
