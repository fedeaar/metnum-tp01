#include "../Matriz.h"


//
// CONSTRUCTORES / DESTRUCTOR
//

template<class T>
Matriz<T>::Matriz() {}

template<class T>
Matriz<T>::Matriz(size_t n, size_t m): n(n), m(m), _mat(n, vector<T>(m)), _row(n), _col(m) {
    std::iota(_row.begin(), _row.end(), 0);
    std::iota(_col.begin(), _col.end(), 0);
}


template<class T>
Matriz<T>::Matriz(const Matriz<T> &b): Matriz(b.n, b.m) {
    *this = b;
}


template<class T>
Matriz<T>::Matriz(const initializer_list<initializer_list<T>> &b): Matriz(b.size(), (*b.begin()).size()) {
    *this = b;
}


template<class T>
Matriz<T>::~Matriz() = default;




//
// OPERADORES
//

template<class T>
Matriz<T> &Matriz<T>::operator=(const Matriz &b) {
    assert(shape() == b.shape());
    if (this != &b) {
        for (const_iterator it = b.begin(); it.in_range(); it.next()) {
            set(it.row(), it.col(), it.at());
        }
    }
    return *this;
}
template<class T>
Matriz<T> &Matriz<T>::operator=(const initializer_list<initializer_list<T>> &b) {
    assert(n == b.size());
    size_t i = 0;
    for (auto it = b.begin(); it != b.end(); ++it, ++i) {
        auto in = *it;
        assert(m >= in.size());
        size_t j = 0;
        for (auto jt = in.begin(); jt != in.end(); ++jt, ++j) {
            set(i, j, *jt);
        }
    }
    return *this;
}


template<class T>
Matriz<T> Matriz<T>::operator+(const Matriz &b) const {
    assert(shape() == b.shape());
    Matriz res {n, m};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
         res.set(it.row(), it.col(), it.at() + b.at(it.row(), it.col()));
    }
    return res;
}


template<class T>
Matriz<T> Matriz<T>::operator-(const Matriz &b) const {
    assert(shape() == b.shape());
    Matriz res {n, m};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        res.set(it.row(), it.col(), it.at() - b.at(it.row(), it.col()));
    }
    return res;
}


template<class T>
Matriz<T> Matriz<T>::operator*(const T &b) const {
    Matriz res {n, m};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        res.set(it.row(), it.col(), it.at() * b);
    }
    return res;
}
template<class T>
Matriz<T> operator*(const T &b, const Matriz<T> &a) {
    return a * b;
}


template<class T>
Matriz<T> Matriz<T>::operator*(const Matriz<T> &b) const {
    assert(m == b.n);
    Matriz<T> res {n, b.m};
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


template<class T>
bool Matriz<T>::eq(const Matriz &b, double epsilon) const {
    bool res = true;
    for (const_iterator it = begin(), jt = b.begin(); it.in_range() && res; it.next(), jt.next()) {
        res = std::abs(it.at() - jt.at()) < epsilon;
    }
    return res;
}




//
// GETTERS / SETTERS
//

template<class T>
void Matriz<T>::set(size_t row, size_t col, T elem) {
    assert(0 <= row && row < n && 0 <= col && col < m);
    _mat[_row[row]][_col[col]] = elem;
}


template<class T>
T Matriz<T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < n && 0 <= col && col < m);
    return _mat[_row[row]][_col[col]];
}


template<class T>
pair<size_t, size_t> Matriz<T>::shape() const {
    return {n, m};
}


template<class T>
void Matriz<T>::reindex(size_t i1, size_t i2, bool rowOrder) {
    assert(0 <= i1 && i1 < n && 0 <= i2 && i2 < m);
    if (rowOrder) {
        _row[i1] = i2;
        _row[i2] = i1;
    } else {
        _col[i1] = i2;
        _col[i2] = i1;
    }
}




//
// STREAM
//

template<class T>
ostream &Matriz<T>::print(ostream &os) const {
    os << '\n';
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        os << it.at() << (it.col() == (m - 1) ? "\n" : ", ");
    }
    return os;
}


template<class T>
ostream &operator<<(ostream &os, const Matriz<T> &mat) {
    return mat.print(os);
}




//
// OTRAS FUNCIONES
//

template<class T>
Matriz<T> identity(size_t n) {
    Matriz<T> res {n, n};
    for (auto it = res.begin(); it.in_range(); it.next_diagonal()) {
        it.set(1);
    }
    return res;
}


template<class T>
Matriz<T> diagonal(const vector<T> &v) {
    size_t n = v.size();
    Matriz<T> res {n, n};
    for (auto it = res.begin(); it.in_range(); it.next_diagonal()) {
        it.set(v[it.row()]);
    }
    return res;
}
