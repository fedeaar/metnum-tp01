#include "../../matriz.h"


//
// OPERADORES
//

template<class T, class R>
template<class S>
matriz<T, R> matriz<T, R>::operator+(const matriz<T, S> &b) const {
    assert(n() == b.n() && m() == b.m());
    matriz res {n(), m()};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        res.set(it.row(), it.col(), it.at() + b.at(it.row(), it.col()));
    }
    return res;
}


template<class T, class R>
template<class S>
matriz<T, R> matriz<T, R>::operator-(const matriz<T, S> &b) const {
    assert(n() == b.n() && m() == b.m());
    matriz res {n(), m()};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        res.set(it.row(), it.col(), it.at() - b.at(it.row(), it.col()));
    }
    return res;
}


template<class T, class R>
matriz<T, R> matriz<T, R>::operator*(const T &b) const {
    matriz res {n(), m()};
    for (const_iterator it = begin(); it.in_range(); it.next()) {
        res.set(it.row(), it.col(), it.at() * b);
    }
    return res;
}
template<class T, class R>
matriz<T, R> operator*(const T &b, const matriz<T, R> &a) {
    return a * b;
}


template<class T, class R>
template<class S>
matriz<T, R> matriz<T, R>::operator*(const matriz<T, S> &b) const {
    assert(m() == b.n());
    matriz<T, R> res {n(), b.m()};
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


template<class T, class R>
template<class S>
bool matriz<T, R>::eq(const matriz<T, S> &b, double epsilon) const {
    bool res = true;
    const_iterator it = begin();
    typename matriz<T, S>::const_iterator jt = b.begin();
    while (it.in_range() && res) {
        res = std::abs(it.at() - jt.at()) < epsilon;
        it.next();
        jt.next();
    }
    return res;
}
