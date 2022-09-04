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

template<class T, class R>
matriz<T, R> matriz<T, R>::gauss_elim(vector<T> &b) const {
    /** pre: A_ii != 0 para i: 0 ... N y b.size() == N. */
    assert(b.size() == n());
    matriz res {*this};
    auto A = &(res._rep._mat);
    for (size_t i = 0; i < n()- 1; i++) {
        T mii = (*A)[i][0].val;
        for (size_t j = i + 1; j < n(); j++) {
            typename alt<T>::elem* col_i = &((*A)[j][0]);
            if(col_i->col != i) continue;
            T mij = col_i->val / mii;
            size_t pos = 1;
            vector<typename alt<T>::elem> newRow = {};
            for (size_t k = 1; k < (*A)[i].size(); k++) {
                while(pos < (*A)[j].size() && (*A)[j][pos].col < (*A)[i][k].col) {
                    if(abs((*A)[j][pos].val) > 1e-4) newRow.push_back((*A)[j][pos]);
                    pos++;
                }

                // m[j][pos].col >= m[k].col
                typename alt<T>::elem x;
                if(pos < (*A)[j].size() && (*A)[j][pos].col == (*A)[i][k].col) {
                    x.val = (*A)[j][pos].val;
                    pos++;
                }
                x.val -= mij * (*A)[i][k].val;
                x.col = (*A)[i][k].col;
                if(abs(x.val) > 1e-4) newRow.push_back(x);
            }

            for(size_t k = pos; k < (*A)[j].size(); ++k) {
                if(abs((*A)[j][k].val) > 1e-4) newRow.push_back((*A)[j][k]);
            }

            (*A)[j] = newRow;

            b[j] = b[j] - mij * b[i];
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
