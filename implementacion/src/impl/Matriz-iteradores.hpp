#include "../Matriz.h"


//
// CONSTRUCTORES / DESTRUCTOR
//

template<size_t n, size_t m, class T>
Matriz<n, m, T>::const_iterator::const_iterator(const Matriz<n, m, T> &p, size_t row, size_t col):
    _row(row), _col(col), _p(p) {}


template<size_t n, size_t m, class T>
Matriz<n, m, T>::const_iterator::~const_iterator() = default;




//
// OPERADORES
//

template<size_t n, size_t m, class T>
bool Matriz<n, m, T>::const_iterator::operator==(const const_iterator& b) {
    // apuntan al mismo lado o ambos son inválidos.
    return _row == b._row && _col == b._col || !in_range() && !b.in_range();
}


template<size_t n, size_t m, class T>
bool Matriz<n, m, T>::const_iterator::in_range() {
    return 0 <= _row && _row < n && 0 <= _col && _col < m;
}




//
// GETTERS / SETTERS
//

template<size_t n, size_t m, class T>
size_t Matriz<n, m, T>::const_iterator::row() {
    return _row;
}


template<size_t n, size_t m, class T>
size_t Matriz<n, m, T>::const_iterator::col() {
    return _col;
}


template<size_t n, size_t m, class T>
T Matriz<n, m, T>::const_iterator::at() {
    return _p.at(row(), col());
}


template<size_t n, size_t m, class T>
void Matriz<n, m, T>::const_iterator::next(bool rowOrder, bool wrap) {
    if (rowOrder) {
        ++_col;
        if (wrap && _col >= m) {
            ++_row;
            _col = 0;
        }
    } else {
        ++_row;
        if (wrap && _row >= n) {
            ++_col;
            _row = 0;
        }
    }
}



//
// ITERADOR
//

template<size_t n, size_t m, class T>
Matriz<n, m, T>::iterator::iterator(Matriz<n, m, T> &p, size_t row, size_t col): const_iterator(p, row, col), _p(p) {}


template<size_t n, size_t m, class T>
void Matriz<n, m, T>::iterator::set(T elem) {
    _p.set(const_iterator::row(), const_iterator::col(), elem);
}




//
// MATRIZ:: BEGIN / END
//

template<size_t n, size_t m, class T> typename
Matriz<n, m, T>::iterator Matriz<n, m, T>::begin(size_t i, size_t j) {
    return iterator(*this, i, j);
}


template<size_t n, size_t m, class T> typename
Matriz<n, m, T>::const_iterator Matriz<n, m, T>::begin(size_t i, size_t j) const {
    return const_iterator(*this, i, j);
}


template<size_t n, size_t m, class T> typename
Matriz<n, m, T>::iterator Matriz<n, m, T>::end() {
    return iterator(*this, -1, -1);
}


template<size_t n, size_t m, class T> typename
Matriz<n, m, T>::const_iterator Matriz<n, m, T>::end() const {
    return const_iterator(*this, -1, -1);
}
