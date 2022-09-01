#include "../../matriz.h"
#include <chrono>
using namespace std::chrono;
//
// GAUSS
//

template<class T, class R>
matriz<T, R> matriz<T, R>::gauss_swap(size_t i1, size_t i2, bool rowOrder) const {
    matriz res {*this};
    res.swap(i1, i2, rowOrder);
    return res;
}


template<class T, class R>
matriz<T, R> matriz<T, R>::gauss_mult(size_t i, const T &val, bool rowOrder) const {
    matriz res {*this};
    for (iterator it = (rowOrder ? res.begin(i, 0) : res.begin(0, i)); it.in_range(); it.next(rowOrder, false)) {
        it.set(it.at() * val);
    }
    return res;
}


template<class T, class R>
matriz<T, R> matriz<T, R>::gauss_sum(size_t i1, size_t i2, const T &val, bool rowOrder) const {
    matriz res {*this};
    iterator it1 = (rowOrder ? res.begin(i1, 0) : res.begin(0, i1)),
             it2 = (rowOrder ? res.begin(i2, 0) : res.begin(0, i2));
    while (it1.in_range()) {
        it1.set(it1.at() + it2.at() * val);
        it1.next(rowOrder, false);
        it2.next(rowOrder, false);
    }
    return res;
}


template<class T, class R>
matriz<T, R> matriz<T, R>::gauss_elim() const {
    /** pre: A_ii != 0 para i: 0 ... N. */
    matriz res {*this};
    for (int i = 0; i < n() - 1; i++) {
        for (int j = i + 1; j < n(); j++) {
            T mij = res.at(j, i) / res.at(i, i);
            for (int k = i; k < m(); k++) {
                T newVal = res.at(j, k) - mij * res.at(i, k);
                res.set(j, k, newVal);
            }
        }
    }
    return res;
}
//template<class T, class R>
//matriz<T, R> matriz<T, R>::gauss_elim(vector<T> &b) const {
//    /** pre: A_ii != 0 para i: 0 ... N y b.size() == N. */
//    assert(b.size() == n());
//    matriz res {*this};
//    for (size_t i = 0; i < n() - 1; i++) {
//        for (size_t j = i + 1; j < n(); j++) {
//            T mij = res.at(j, i) / res.at(i, i);
//            for (size_t k = i; k < m(); k++) {
//                T newVal = res.at(j, k) - mij * res.at(i, k);
//                res.set(j, k, newVal);
//            }
//            b[j] = b[j] - mij * b[i];
//        }
//    }
//    return res;
//}
template<class T, class R>
matriz<T, R> matriz<T, R>::gauss_elim(vector<T> &b) const {
    /** pre: A_ii != 0 para i: 0 ... N y b.size() == N. */
    assert(b.size() == n());
    matriz res {*this};
    for (size_t i = 0; i < n() - 1; i++) {
        for (size_t j = i + 1; j < n(); j++) {
            T tmp = res.at(j, i);
            if (tmp == 0) {
                continue;
            } else {
                T mij = tmp / res.at(i, i);
                auto kt = res._rep.begin(i, i);
                while (kt.in_range()) {
                    T newVal = res.at(j, kt.col()) - mij * kt.at();
                    res.set(j, kt.col(), newVal);
                    kt.next(false);
                }
                b[j] = b[j] - mij * b[i];
            }
        }
    }
    return res;
}


template<class T, class R>
vector<T> matriz<T, R>::solve(const vector<T> &b) {
    /** pre: pre: A_ii != 0 para i: 0 ... N despues de triangular y N == M y b.size() == N. */
    assert(b.size() == n());

    auto start = high_resolution_clock::now();
    vector<T> b_tri = b;
    matriz<T, R> m_tri = gauss_elim(b_tri);
    auto stop = high_resolution_clock::now();
    cout << "tiempo triangular: " << duration_cast<milliseconds>(stop-start).count() << " ms." << endl;

    start = high_resolution_clock::now();
    vector<T> res(n());
    for (long i = n() - 1; i >= 0; --i) {
        T parcial {};
        for (auto it = m_tri._rep.begin(i, i + 1); it.in_range(); it.next(false)) {
            parcial = parcial + it.at() * res[it.col()];
        }
        res[i] = (b_tri[i] - parcial) / m_tri.at(i, i);
    }
    stop = high_resolution_clock::now();
    cout << "tiempo resolvero: " << duration_cast<milliseconds>(stop-start).count() << " ms." << endl;
    return res;
}
