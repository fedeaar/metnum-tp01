using namespace std;
#include "../Matriz.h"

//
// Iterador
//

template<size_t n, size_t m, class T>
Matriz<n, m, T>::iterator::iterator(size_t i, size_t j): _i(i), _j(j) {}


template<size_t n, size_t m, class T>
Matriz<n, m, T>::iterator::~iterator() = default;


template<size_t n, size_t m, class T>
bool Matriz<n, m, T>::iterator::operator==(const iterator& b) {
    // apuntan al mismo lado o ambos son inválidos.
    return _i == b._i && _j == b._j || !inRange() && !b.inRange();
}


template<size_t n, size_t m, class T>
size_t Matriz<n, m, T>::iterator::i() {
    return _i;
}


template<size_t n, size_t m, class T>
size_t Matriz<n, m, T>::iterator::j() {
    return _j;
}


template<size_t n, size_t m, class T>
void Matriz<n, m, T>::iterator::next(bool rowOrder, bool wrap) {
    if (rowOrder) {
        ++_j;
        if (wrap && _j >= m) {
            ++_i;
            _j = 0;
        }
    } else {
        ++_i;
        if (wrap && _i >= n) {
            ++_j;
            _i = 0;
        }
    }
}


template<size_t n, size_t m, class T>
bool Matriz<n, m, T>::iterator::inRange() {
    return 0 <= _i && _i < n && 0 <= _j && _j < m;
}


template<size_t n, size_t m, class T>
void Matriz<n, m, T>::row_iterator::next() {
    ++iterator::_j;
}


template<size_t n, size_t m, class T>
void Matriz<n, m, T>::col_iterator::next() {
    ++iterator::_i;
}




//
// Matriz
//

template<size_t n, size_t m, class T>
Matriz<n, m, T>::Matriz(): _m(), _row(), _col() {
    iota(_row.begin(), _row.end(), 0);
    iota(_col.begin(), _col.end(), 0);
}


template<size_t n, size_t m, class T>
Matriz<n, m, T>::Matriz(const Matriz<n, m, T> &b) {
    this = b;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T>::Matriz(T (&a)[n][m]): Matriz() {
    for (iterator it = begin(); it.inRange(); it.next()) {
        at(it) = a[it.i()][it.j()];
    }
}


template<size_t n, size_t m, class T>
Matriz<n, m, T>::~Matriz() = default;


template<size_t n, size_t m, class T>
Matriz<n, m, T> &Matriz<n, m, T>::operator=(const Matriz& b) {
    if (this != &b) {
        for (iterator it = begin(); it.inRange(); it.next()) {
            at(it) = b.at(it);
        }
    }
    return *this;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::operator+(const Matriz& b) {
    Matriz res(n, m);
    for (iterator it = begin(); it.isValid(); it.next()) {
         res.at(it) = at(it) + b.at(it);
    }
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::operator-(const Matriz& b) {
    Matriz res(n, m);
    for (iterator it = begin(); it.inRange(); it.next()) {
        res.at(it) = at(it) - b.at(it);
    }
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::operator*(const T& b) {
    Matriz res(n, m);
    for (iterator it = begin(); it.inRange(); it.next()) {
        res.at(it) = at(it) * b;
    }
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::swap(size_t i, size_t j, bool rowOrder) {
    Matriz res(this);
    if (rowOrder) {
        res._row[i] = j;
        res._row[j] = i;
    } else {
        res._col[i] = j;
        res._col[j] = i;
    }
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::sum(size_t dest, size_t orig, const T &b, bool rowOrder){
    Matriz res();
    res = this;
    // Revisar ---
    if (rowOrder){
        res._row[dest] = dest + b*orig; // b*orig no funciona porque no tiene sentido xd pero se entiende la idea
    } else {
        res._col[dest] = dest + b*orig;
    }
    return res;
}


template<size_t n, size_t m, class T>
template<size_t l>
Matriz<n, l, T> Matriz<n, m, T>::operator*(const Matriz<m, l, T>& b) {
    Matriz res(n, l);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < l; ++j) {
            T val {};
            for (size_t k = 0; k < m; ++k) {
                val = val + at(i, k) * b.at(k, j);
            }
            res.at(i, j) = val;
        }
    }
    return res;
}


template<size_t n, size_t m, class T>
T &Matriz<n, m, T>::at(size_t i, size_t j) {
    assert(0 <= i && i < n && 0 <= j && j < m);
    return _m[_row[i]][_col[j]];
}


template<size_t n, size_t m, class T>
const T &Matriz<n, m, T>::at(size_t i, size_t j) const {
    assert(0 <= i && i < n && 0 <= j && j < m);
    return _m[_row[i]][_col[j]];
}


template<size_t n, size_t m, class T>
T &Matriz<n, m, T>::at(Matriz::iterator it) {
    assert(it.inRange());
    return _m[_row[it.i()]][_col[it.j()]];
}


template<size_t n, size_t m, class T>
const T &Matriz<n, m, T>::at(Matriz::iterator it) const {
    assert(it.inRange());
    return _m[_row[it.i()]][_col[it.j()]];
}



template<size_t n, size_t m, class T>
typename Matriz<n, m, T>::iterator Matriz<n, m, T>::begin(size_t i, size_t j) {
    return iterator(i, j);
}


template<size_t n, size_t m, class T>
typename Matriz<n, m, T>::iterator Matriz<n, m, T>::end() {
    return iterator(-1, -1);
}


template<size_t n, size_t m, class T>
ostream &Matriz<n, m, T>::print(ostream &os) const {
    os << '\n';
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            os << at(i, j) << ", ";
        }
        os << '\n';
    }
    os << endl;
    return os;
}


template<size_t n, size_t m, class T>
ostream &operator<<(ostream &os, const Matriz<n, m, T>& _m) {
    return _m.print(os);
}







