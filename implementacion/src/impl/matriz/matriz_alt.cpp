#include "../../matriz/matriz_alt.h"


//
// ALT PRIVATE
//

size_t alt::search(size_t row, size_t col) const {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    if(_last[row].from <= col && col <= _last[row].to)   return _last[row].pos;
    if(_last[row].to+1 <= col && col <= _last[row].next) return _last[row].pos + 1;
    size_t i = 0, j = _mat[row].size();
    while(i < j) {
        size_t k = (i+j)/2;
        if(_mat[row][k].col == col) return k;
        if(_mat[row][k].col <  col) i = k + 1;
        else j = k;
    }
    return i;
}


void alt::updateLast(size_t row, size_t pos) const {
    assert(0 <= row && row < _n && 0 <= pos && pos <= _mat[row].size());
    if(pos == _mat[row].size()) {
        if(pos) {
            _last[row].from = _mat[row].back().col + 1;
            _last[row].to = _m;
            _last[row].next = _m;
            _last[row].pos = pos;
        }
    } else {
        _last[row].from = _mat[row][max((size_t) 0, pos-1)].col+1;
        _last[row].to = _mat[row][pos].col;
        _last[row].next = pos + 1 < _mat[row].size() ? _mat[row][pos+1].col : _m;
        _last[row].pos = pos;
    }
}


bool alt::count(size_t row, size_t col) const {
    return col == search(row, col);
}




//
// ALT
//

alt::alt(size_t n, size_t m): _n(n), _m(m), _mat(n), _last(vector<cache>(n)) {
   for(size_t i =0 ; i < n; ++i) _last[i].to = m;
}


double alt::at(size_t row, size_t col) const {
   assert(0 <= row && row < _n && 0 <= col && col < _m);
   if(!_mat[row].size()) return {};
   size_t pos = search(row, col);
   updateLast(row, pos);
   if(pos < _mat[row].size() && _mat[row][pos].col == col)
       return _mat[row][pos].val;
   else
       return {};
}


void alt::set(size_t row, size_t col, double val) {
   assert(0 <= row && row < _n && 0 <= col && col < _m);
   size_t pos = search(row, col);
   if(pos < _mat[row].size() && _mat[row][pos].col == col)
       _mat[row][pos].val = val;
   else if(std::abs(val) >= EPSILON) {
       elem newVal {col, val};
       _mat[row].insert(_mat[row].begin() + pos, newVal);
   }
   updateLast(row, pos);
}


alt::iterator alt::begin(size_t i, size_t j) {
    return alt::iterator(*this, i, j);
}


alt::const_iterator alt::begin(size_t i, size_t j) const {
    return alt::const_iterator(*this, i, j);
}




//
// CONST_ITERATOR
//

alt::const_iterator::const_iterator(const alt &p, size_t row, size_t col): _row(row), _col_pedida(col), _p(p) {
   if (0 <= row && row < _p._n && 0 <= col && col < _p._m) {
       _pos = (p.search(row, col));
   } else {
       _pos = -1;
   }
}


bool alt::const_iterator::in_range() const {
    return 0 <= _row && _row < _p._n && 0 <= _pos && _pos < _p._mat[_row].size();
}


double alt::const_iterator::at() const {
   assert(in_range());
   return _p._mat[_row][_pos].val;
}


size_t alt::const_iterator::col() const {
   return _p._mat[_row][_pos].col;
}


size_t alt::const_iterator::row() const {
   return _row;
}


void alt::const_iterator::next(bool rowOrder) {
    if (rowOrder) {
        ++_pos;
    } else {
        do {
            ++_row;
        } while (_row < _p._n && _p._mat[_row].empty());
        if (_row < _p._n) {
            _pos = _p.search(_row, _col_pedida);
        }
    }
}




//
// ITERATOR
//

alt::iterator::iterator(alt &p, size_t row, size_t col): const_iterator(p, row, col), _p(p) {}


void alt::iterator::set(double elem) {
    _p.set(row(), col(), elem);
}
