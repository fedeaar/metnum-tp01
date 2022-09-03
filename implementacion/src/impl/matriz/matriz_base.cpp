#include "../../matriz_base.h"


//
// BASE
//

base::base(size_t n, size_t m): _n(n), _m(m), _mat(n, vector<double>(m)) {}


double base::at(size_t row, size_t col) const {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    return _mat[row][col];
}


void base::set(size_t row, size_t col, double elem) {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    _mat[row][col] = elem;
}


base::iterator base::begin(size_t i, size_t j) {
    return base::iterator(*this, i, j);
}


base::const_iterator base::begin(size_t i, size_t j) const {
    return base::const_iterator(*this, i, j);
}




//
// CONST_ITERATOR
//

base::const_iterator::const_iterator(const base &p, size_t row, size_t col): _row(row), _col(col), _p(p) {}


bool base::const_iterator::in_range() const {
    return 0 <= _row && _row < _p._n && 0 <= _col && _col < _p._m;
}


size_t base::const_iterator::row() const {
    return _row;
}


size_t base::const_iterator::col() const {
    return _col;
}


double base::const_iterator::at() const {
    return _p.at(row(), col());
}


void base::const_iterator::next(bool rowOrder) {
    if (rowOrder) {
        ++_col;
    } else {
        ++_row;
    }
}




//
// ITERATOR
//

base::iterator::iterator(base &p, size_t row, size_t col): const_iterator(p, row, col), _p(p) {}


void base::iterator::set(double elem) {
    _p.set(row(), col(), elem);
}
