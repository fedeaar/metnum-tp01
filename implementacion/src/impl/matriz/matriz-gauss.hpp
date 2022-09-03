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
        T mii = res._rep._mat[i].front().val;
        for (size_t j = i + 1; j < n(); j++) {
            auto col_i = res._rep._mat[j].begin();
            if (col_i->col != i) continue;
            T mij = col_i->val / mii;
            auto iti = res._rep._mat[i].begin();
            auto itj = col_i;
            auto final = res._rep._mat[j].end();
            ++iti, --final;
            itj = res._rep._mat[j].erase(itj);
            while (iti != res._rep._mat[i].end()) {
                if(j == 747 && i == 601 && iti->col > 670) {
                    int a = 5;
                }
                while(itj != final && itj->col < iti->col) ++itj;
                T val = - mij * iti->val;
                if(itj->col == iti->col) val += itj->val;
                res._rep.set(itj, j, iti->col, val);
                ++iti;
            }
            b[j] = b[j] - mij * b[i];

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
//            T tmp = res.at(j, i);
//            if (tmp == 0) {
//                continue;
//            } else {
//                T mij = tmp / res.at(i, i);
//                auto kt = res._rep.begin(i, i);
//                while (kt.in_range()) {
//                    T newVal = res.at(j, kt.col()) - mij * kt.at();
//                    res.set(j, kt.col(), newVal);
//                    kt.next(false);
//                }
//                b[j] = b[j] - mij * b[i];
//            }
//        }
//    }
//    return res;
//}



//template<class T, class R>
//matriz<T, R> matriz<T, R>::gauss_elim(vector<T> &b) const {
//    assert(b.size() == n());
//    matriz res {*this};
//    for(size_t i = 0; i < n()-1; ++i) {
//        auto mii = res._rep.inicioRow(i); // parado en la diagonal
//        auto col_i = mii; // recorre la columna i
//        col_i = col_i->nextInCol;
//
//        while(col_i->row < res._rep.n()) {
//            auto row_i = mii;
//            row_i = row_i->nextInRow;
//            T k = col_i->val/mii->val;
//            while(row_i->col < res._rep.m()) {
//                T newVal = res.at(col_i->row, row_i->col) - k * row_i->val;
//                res.set(col_i->row, row_i->col, newVal);
//                row_i = row_i->nextInRow;
//            }
//            b[col_i->row] = b[col_i->row] - k * b[i];
//
//            col_i = col_i->nextInCol;
//            res._rep.remove(col_i->prevInCol);
//        }
//    }
//    return res;
//}

// template<class T, class R>
// matriz<T, R> matriz<T, R>::gauss_elim(vector<T> &b) const {
//     assert(b.size() == n());
//     matriz res {*this};
//     auto mii = res._rep.begin();; // parado en la diagonal
//     for(size_t i = 0; i < n(); ++i) {
//         auto col_i = res._rep.begin(mii); // recorre la columna i
//         col_i.nextInCol();
//         while(col_i.in_range()) {
//             auto row_i = res._rep.begin(mii);
//             row_i.next();
//             auto row_j = res._rep.begin(col_i);
//             row_j.next();
//             T k = col_i.at()/mii.at();
//             while(row_j.in_range() && row_i.in_range()) {
//                 if(row_i.col() == row_j.col())
//                     row_j.set(row_j.at() - k * row_i.at());
//                 else if(row_i.col() > row_j.col())
//                     row_j.next();
//                 else
//                     row_i.next();
//             }
//
//             b[col_i.row()] = b[col_i.row()] - k * b[i];
//             col_i.remove(false);
//         }
//
//         mii.next();
//         mii.nextInCol();
//     }
//     return res;
// }

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
