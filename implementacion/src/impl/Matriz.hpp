#include "../Matriz.h"


//
// CONSTRUCTORES / DESTRUCTOR
//

template<size_t n, size_t m, class T>
Matriz<n, m, T>::Matriz(): _m(), _row(), _col() {
    std::iota(_row.begin(), _row.end(), 0);
    std::iota(_col.begin(), _col.end(), 0);
}


template<size_t n, size_t m, class T>
Matriz<n, m, T>::Matriz(const Matriz<n, m, T> &b): Matriz() {
    *this = b;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T>::Matriz(const initializer_list<initializer_list<T>> &b): Matriz() {
    *this = b;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T>::~Matriz() = default;




//
// OPERADORES
//

template<size_t n, size_t m, class T>
Matriz<n, m, T> &Matriz<n, m, T>::operator=(const Matriz &b) {
    if (this != &b) {
        for (iterator it = begin(); it.in_range(); it.next()) {
            it.set(b.at(it.row(), it.col()));
        }
    }
    return *this;
}
template<size_t n, size_t m, class T>
Matriz<n, m, T> &Matriz<n, m, T>::operator=(const initializer_list<initializer_list<T>> &b) {
    assert(b.size() == n);
    size_t i = 0;
    for (auto it = b.begin(); it != b.end(); ++it, ++i) {
        auto in = *it;
        assert(in.size() == m);
        size_t j = 0;
        for (auto jt = in.begin(); jt != in.end(); ++jt, ++j) {
            set(i, j, *jt);
        }
    }
    return *this;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::operator+(const Matriz& b) const {
    Matriz res {};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
         res.set(it.row(), it.col(), it.at() + b.at(it.row(), it.col()));
    }
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::operator-(const Matriz& b) const {
    Matriz res {};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        res.set(it.row(), it.col(), it.at() - b.at(it.row(), it.col()));
    }
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::operator*(const T& b) const {
    Matriz res {};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        res.set(it.row(), it.col(), it.at() * b);
    }
    return res;
}
template<size_t n, size_t m, class T>
Matriz<n, m, T> operator*(const T &b, const Matriz<n, m, T> &a) {
    return a * b;
}


template<size_t n, size_t m, class T>
template<size_t l>
Matriz<n, l, T> Matriz<n, m, T>::operator*(const Matriz<m, l, T>& b) const {
    Matriz<n, l, T> res {};
    for (iterator rt = res.begin(); rt.in_range(); rt.next()) {
        T sum {};
        const_iterator it = begin(rt.row(), 0),
                       jt = b.begin(0, rt.col());
        while (it.in_range()) {
            sum = sum + it.at() * jt.at();
            jt.next(false, false);
            it.next(true, false);
        }
        rt.set(sum);
    }
    return res;
}


template<size_t n, size_t m, class T>
bool Matriz<n, m, T>::eq(const Matriz &b, double epsilon) const {
    bool res = true;
    for (const_iterator it = begin(), jt = b.begin(); it.in_range() && res; it.next(), jt.next()) {
        res = std::abs(it.at() - jt.at()) < epsilon;
    }
    return res;
}




//
// GETTERS / SETTERS
//

template<size_t n, size_t m, class T>
void Matriz<n, m, T>::set(size_t row, size_t col, T elem) {
    assert(0 <= row && row < n && 0 <= col && col < m);
    _m[_row[row]][_col[col]] = elem;
}


template<size_t n, size_t m, class T>
void Matriz<n, m, T>::reindex(size_t i1, size_t i2, bool rowOrder) {
    assert(0 <= i1 && i1 < n && 0 <= i2 && i2 < m);
    if (rowOrder) {
        _row[i1] = i2;
        _row[i2] = i1;
    } else {
        _col[i1] = i2;
        _col[i2] = i1;
    }
}


template<size_t n, size_t m, class T>
T Matriz<n, m, T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < n && 0 <= col && col < m);
    return _m[_row[row]][_col[col]];
}



//
// STREAM
//

template<size_t n, size_t m, class T>
ostream &Matriz<n, m, T>::print(ostream &os) const {
    os << '\n';
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        os << it.at() << (it.col() == (m - 1) ? "\n" : ", ");
    }
    return os;
}
template<size_t n, size_t m, class T>
ostream &operator<<(ostream &os, const Matriz<n, m, T>& _m) {
    return _m.print(os);
}
