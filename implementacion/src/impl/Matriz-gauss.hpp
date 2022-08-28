#include "../Matriz.h"


//
// GAUSS
//

template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::gauss_swap(size_t i1, size_t i2, bool rowOrder) const {
    Matriz res {*this};
    res.reindex(i1, i2, rowOrder);
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::gauss_mult(size_t i, const T &val, bool rowOrder) const {
    Matriz res {*this};
    for (iterator it = (rowOrder ? res.begin(i, 0) : res.begin(0, i)); it.in_range(); it.next(rowOrder, false)) {
        it.set(it.at() * val);
    }
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::gauss_sum(size_t i1, size_t i2, const T &val, bool rowOrder) const {
    Matriz res {*this};
    iterator it1 = (rowOrder ? res.begin(i1, 0) : res.begin(0, i1)),
             it2 = (rowOrder ? res.begin(i2, 0) : res.begin(0, i2));
    while (it1.in_range()) {
        it1.set(it1.at() + it2.at() * val);
        it1.next(rowOrder, false);
        it2.next(rowOrder, false);
    }
    return res;
}


template<size_t n, size_t m, class T>
Matriz<n, m, T> Matriz<n, m, T>::gauss_elim() const {
    // TODO
    return Matriz();
}
