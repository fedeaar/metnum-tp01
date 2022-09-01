#include "../../matriz.h"


//
// CONSTRUCTORES / DESTRUCTOR
//

template<class T, class R>
matriz<T, R>::matriz(size_t n, size_t m): _rep(n, m) {}


template<class T, class R>
template<class S>
matriz<T, R>::matriz(const matriz<T, S> &b): matriz(b.n(), b.m()) {
    *this = b;
}


template<class T, class R>
matriz<T, R>::matriz(const initializer_list<initializer_list<T>> &b): _rep(b.size(), (*b.begin()).size()) {
    assert(b.size() > 0);
    *this = b;
}




//
// ASSIGN
//

template<class T, class R>
template<class S>
matriz<T, R> &matriz<T, R>::operator=(const matriz<T, S> &b) {
    assert(n() == b.n() && m() == b.m());
    if (this != &b) {
        for (const_iterator it = b.begin(); it.in_range(); it.next()) {
            set(it.row(), it.col(), it.at());
        }
    }
    return *this;
}


template<class T, class R>
matriz<T, R> &matriz<T, R>::operator=(const initializer_list<initializer_list<T>> &b) {
    assert(n() == b.size());
    size_t i = 0;
    for (auto it = b.begin(); it != b.end(); ++it, ++i) {
        auto in = *it;
        assert(m() >= in.size());
        size_t j = 0;
        for (auto jt = in.begin(); jt != in.end(); ++jt, ++j) {
            set(i, j, *jt);
        }
    }
    return *this;
}


template<class T, class R>
matriz<T, R>::~matriz() = default;




//
// STREAM
//

template<class T, class R>
ostream &matriz<T, R>::print(ostream &os) const {
    os << '\n';
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        os << it.at() << (it.col() == (m() - 1) ? "\n" : ", ");
    }
    return os;
}
template<class T, class R>
ostream &operator<<(ostream &os, const matriz<T, R> &mat) {
    return mat.print(os);
}




//
// OTRAS FUNCIONES
//

template<class T, class R>
matriz<T, R> identity(size_t n) {
    matriz<T, R> res {n, n};
    for (auto it = res.begin(); it.in_range(); it.next_diagonal()) {
        it.set(1);
    }
    return res;
}


template<class T, class R>
matriz<T, R> diagonal(const vector<T> &v) {
    size_t n = v.size();
    matriz<T, R> res {n, n};
    for (auto it = res.begin(); it.in_range(); it.next_diagonal()) {
        it.set(v[it.row()]);
    }
    return res;
}
