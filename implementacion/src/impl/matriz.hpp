//
// CONSTRUCTORES
//


template<class R>
matriz<R>::matriz(size_t n, size_t m): _rep(n, m), _n(n), _m(m) {}


template<class R>
template<class S>
matriz<R>::matriz(const matriz<S> &b) {
    *this = b;
}


template<class R>
matriz<R>::matriz(const initializer_list<initializer_list<double>> &b): _n(b.size()), _m((*b.begin()).size()), _rep(_n, _m) {
    *this = b;
}




//
// INTERFAZ
//

template<class R>
size_t matriz<R>::n() const {
    return _n;
}


template<class R>
size_t matriz<R>::m() const {
    return _m;
}


template<class R>
double matriz<R>::at(size_t row, size_t col) const {
    return _rep.at(row, col);
}


template<class R>
void matriz<R>::set(size_t row, size_t col, double elem) {
    _rep.set(row, col, elem);
}




//
// OPERADORES
//

template<class R>
template<class S>
matriz<R> &matriz<R>::operator=(const matriz<S> &b) {
    assert(n() == b.n() && m() == b.m());
    if (this != &b) {
        clear();
        // set
        for (auto it = b.begin(); it.in_range(); it.next()) {
            set(it.row(), it.col(), it.at());
        }
    }
    return *this;
}


template<class R>
matriz<R> &matriz<R>::operator=(const initializer_list<initializer_list<double>> &b) {
    assert(n() == b.size());
    // clear
    clear();
    size_t i = 0;
    for (auto it = b.begin(); it != b.end(); ++it, ++i) {
        auto inner = *it;
        assert(m() >= inner.size());
        size_t j = 0;
        for (auto jt = inner.begin(); jt != inner.end(); ++jt, ++j) {
            set(i, j, *jt);
        }
    }
    return *this;
}


template<class R>
template<class S>
matriz<R> matriz<R>::operator+(const matriz<S> &b) const {
    assert(n() == b.n() && m() == b.m());
    matriz<R> res {*this};
    for (auto jt = b.begin(); jt.in_range(); jt.next(false)) {
        for (auto it = b.begin(jt.row(), jt.col()); it.in_range(); it.next()) {
            res.set(it.row(), it.col(), at(it.row(), it.col()) + it.at());
        }
    }
    return res;
}


template<class R>
template<class S>
matriz<R> matriz<R>::operator-(const matriz<S> &b) const {
    assert(n() == b.n() && m() == b.m());
    matriz<R> res {*this};
    for (auto jt = b.begin(); jt.in_range(); jt.next(false)) {
        for (auto it = b.begin(jt.row(), jt.col()); it.in_range(); it.next()) {
            res.set(it.row(), it.col(), at(it.row(), it.col()) - it.at());
        }
    }
    return res;
}


template<class R>
matriz<R> matriz<R>::operator*(double b) const {
    matriz<R> res {*this};
    for (auto jt = res.begin(); jt.in_range(); jt.next(false)) {
        for (auto it = res.begin(jt.row(), jt.col()); it.in_range(); it.next()) {
            it.set(it.at() * b);
        }
    }
    return res;
}
template<class R>
matriz<R> operator*(double b, const matriz<R> &a) {
    return a * b;
}


template<class R>
template<class S>
matriz<R> matriz<R>::operator*(const matriz<S> &b) const {
    assert(m() == b.n());
    matriz<R> res {n(), b.m()};
    for (size_t i = 0; i < n(); ++i) {
        for (size_t j = 0; j < b.m(); ++j) {
            double sum = 0;
            for (auto kt = begin(i, 0); kt.in_range(); kt.next()) {
                sum += kt.at() * b.at(kt.col(), j);
            }
            if (sum >= EPSILON) {
                res.set(i, j, sum);
            }
        }
    }
    return res;
}


template<class R>
template<class S>
bool matriz<R>::eq(const matriz<S> &b, double epsilon) const {
    bool res = true;
    for (auto it = begin(); it.in_range() && res; it.next()) {
        res = std::abs(it.at() - b.at(it.row(), it.col())) < epsilon;
    }
    return res;
}




//
// GAUSS
//

template<class R>
matriz<R> matriz<R>::gauss_elim() const {
    /** pre: A_ii != 0 para i: 0 ... N. hasta el final de la eliminación */
    matriz res {*this};
    for (size_t i = 0; i < n() - 1; ++i) {
        for (auto jt = res.begin(i + 1, i); jt.in_range(); jt.next(false)) {
            if (jt.col() != i) {
                continue;
            } else {
                double mij = jt.at() / res.at(i, i);
                for (auto kt = res.begin(i, i); kt.in_range(); kt.next()) {
                    double newVal = res.at(jt.row(), kt.col()) - mij * kt.at();
                    res.set(jt.row(), kt.col(), newVal);
                }
            }
        }
    }
    return res;
}


template<class R>
matriz<R> matriz<R>::gauss_elim(vector<double> &b) const {
    matriz res {*this};
    res._rep.gauss_elim(b);
    return res;
    /** pre: A_ii != 0 para i: 0 ... N. hasta el final de la eliminación y b.size() == N. *//*
    matriz res {*this};
    for (size_t i = 0; i < n() - 1; ++i) {
        for (auto jt = res.begin(i + 1, i); jt.in_range(); jt.next(false)) {
            if (jt.col() != i) {
                continue;
            } else {
                double mij = jt.at() / res.at(i, i);
                for (auto kt = res.begin(i, i); kt.in_range(); kt.next()) {
                    double newVal = res.at(jt.row(), kt.col()) - mij * kt.at();
                    res.set(jt.row(), kt.col(), newVal);
                }
                b[jt.row()] = b[jt.row()] - mij * b[i];
            }
        }
    }
    return res;*/
}


template<class R>
vector<double> matriz<R>::solve(const vector<double> &b) const {
    /** pre: pre: A_ii != 0 para i: 0 ... N despues de triangular y N == M y b.size() == N. */
    assert(b.size() == n());
    vector<double> b_tri {b};
    matriz<R> m_tri = gauss_elim(b_tri);
    vector<double> res (n());
    for (long i = n() - 1; i >= 0; --i) {
        double parcial = 0;
        for (auto it = m_tri.begin(i, i + 1); it.in_range(); it.next()) {
            parcial = parcial + it.at() * res[it.col()];
        }
        res[i] = (b_tri[i] - parcial) / m_tri.at(i, i);
    }
    return res;
}




//
// ITERADORES
//

template<class R> typename
R::iterator matriz<R>::begin(size_t i, size_t j) {
    return _rep.begin(i, j);
}


template<class R> typename
R::const_iterator matriz<R>::begin(size_t i, size_t j) const {
    return _rep.begin(i, j);
}




//
// STREAM
//

template<class R>
ostream &matriz<R>::print(ostream &os) const {
    for (size_t i = 0; i < n(); ++i) {
        for (size_t j = 0; j < m(); ++j) {
            os << at(i, j) << (j == m() - 1 ? "\n" : ", ");
        }
    }
    return os;
}
template<class R>
ostream &operator<<(ostream &os, const matriz<R> &mat) {
    return mat.print(os);
}


template<class R>
void matriz<R>::clear() {
    for (auto jt = begin(); jt.in_range(); jt.next(false)) {
        for (auto it = begin(jt.row(), jt.col()); it.in_range(); it.next()) {
            it.set(0);
        }
    }
}




//
// OTRAS FUNCIONES
//

template<class R>
matriz<R> diagonal(const vector<double> &v) {
    size_t n = v.size();
    matriz<R> res {n, n};
    for (size_t i = 0; i < v.size(); ++i) {
        res.set(i, i, v[i]);
    }
    return res;
}

template<class R>
matriz<R> identity(size_t n) {
    return diagonal<R>(vector<double>(n, 1));
}
