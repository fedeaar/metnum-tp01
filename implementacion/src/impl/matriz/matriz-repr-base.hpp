#include "../../matriz-repr.h"


template<class T>
base<T>::base(size_t n, size_t m): _n(n), _m(m), _mat(n, vector<T>(m)), _row(n), _col(m) {
    std::iota(_row.begin(), _row.end(), 0);
    std::iota(_col.begin(), _col.end(), 0);
}


template<class T>
const size_t &base<T>::n() const {
    return _n;
}


template<class T>
const size_t &base<T>::m() const {
    return _m;
}


template<class T>
T base<T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    return _mat[_row[row]][_col[col]];
}


template<class T>
void base<T>::set(size_t row, size_t col, T elem) {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    _mat[_row[row]][_col[col]] = elem;
}


template<class T>
void base<T>::swap(size_t i1, size_t i2, bool rowOrder) {
    assert(0 <= i1 && i1 < (rowOrder ? _n : _m) && 0 <= i2 && i2 < (rowOrder ? _n : _m));
    if (rowOrder) {
        _row[i1] = i2;
        _row[i2] = i1;
    } else {
        _col[i1] = i2;
        _col[i2] = i1;
    }
}
