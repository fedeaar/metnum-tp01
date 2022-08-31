#include "../Matriz.h"


//
// CONSTRUCTORES / DESTRUCTOR
//

template<class T>
Matriz<T>::const_iterator::const_iterator(const Matriz<T> &p, size_t row, size_t col):
    _row(row), _col(col), _p(p) {}


template<class T>
Matriz<T>::const_iterator::~const_iterator() = default;




//
// OPERADORES
//

template<class T>
bool Matriz<T>::const_iterator::operator==(const const_iterator& b) {
    // apuntan al mismo lado o ambos son inválidos.
    return _row == b._row && _col == b._col || !in_range() && !b.in_range();
}


template<class T>
bool Matriz<T>::const_iterator::in_range() {
    return 0 <= _row && _row < _p.shape().first && 0 <= _col && _col < _p.shape().second;
}




//
// GETTERS / SETTERS
//

template<class T>
size_t Matriz<T>::const_iterator::row() {
    return _row;
}


template<class T>
size_t Matriz<T>::const_iterator::col() {
    return _col;
}


template<class T>
T Matriz<T>::const_iterator::at() {
    return _p.at(row(), col());
}


template<class T>
void Matriz<T>::const_iterator::next(bool rowOrder, bool wrap) {
    if (rowOrder) {
        ++_col;
        if (wrap && _col >= _p.shape().second) {
            ++_row;
            _col = 0;
        }
    } else {
        ++_row;
        if (wrap && _row >= _p.shape().first) {
            ++_col;
            _row = 0;
        }
    }
}


template<class T>
void Matriz<T>::const_iterator::next_diagonal() {
    ++_row;
    ++_col;
}




//
// ITERADOR
//

template<class T>
Matriz<T>::iterator::iterator(Matriz<T> &p, size_t row, size_t col): const_iterator(p, row, col), _p(p) {}


template<class T>
void Matriz<T>::iterator::set(T elem) {
    _p.set(const_iterator::row(), const_iterator::col(), elem);
}




//
// MATRIZ:: BEGIN / END
//

template<class T> typename
Matriz<T>::iterator Matriz<T>::begin(size_t i, size_t j) {
    return iterator(*this, i, j);
}


template<class T> typename
Matriz<T>::const_iterator Matriz<T>::begin(size_t i, size_t j) const {
    return const_iterator(*this, i, j);
}


template<class T> typename
Matriz<T>::iterator Matriz<T>::end() {
    return iterator(*this, -1, -1);
}


template<class T> typename
Matriz<T>::const_iterator Matriz<T>::end() const {
    return const_iterator(*this, -1, -1);
}
