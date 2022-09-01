#include "../../matriz-repr.h"


template<class T>
alt<T>::alt(size_t n, size_t m): _n(n), _m(m), _mat(n), _last(vector<cache>(n)) {
    for(size_t i =0 ; i < n; ++i) _last[i].to = m;
}


template<class T>
const size_t &alt<T>::n() const {
    return _n;
}


template<class T>
const size_t &alt<T>::m() const {
    return _m;
}


template<class T>
T alt<T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    if(!_mat[row].size()) return {};
    size_t pos = search(row, col);
    updateLast(row, pos);
    if(pos < _mat[row].size() && _mat[row][pos].col == col)
        return _mat[row][pos].val;
    else
        return {};
}


template<class T>
void alt<T>::set(size_t row, size_t col, T val) {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    size_t pos = search(row, col);
    elem newVal;
    if(pos < _mat[row].size() && _mat[row][pos].col == col)
        _mat[row][pos].val = val;
    else if(val != newVal.val) { //agregar epsilon a la comparacion
        newVal.col = col;
        newVal.val = val;
        _mat[row].insert(_mat[row].begin() + pos, newVal);
    }
    updateLast(row, pos);
}


template<class T>
void alt<T>::swap(size_t i1, size_t i2, bool rowOrder) {}


template<class T>
size_t alt<T>::search(size_t row, size_t col) const {
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


template<class T>
void alt<T>::updateLast(size_t row, size_t pos) const {
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




//
// IT RAPIDO
//

template<class T>
alt<T>::iterador_rapido::iterador_rapido(const alt<T> &p, size_t row, size_t col): _row(row), _p(p) {
    if (0 <= _row && _row < _p.n() && 0 <= col && col < _p.m()) {
        _pos = (p.search(row, col));
    } else {
        _pos = -1;
    }
}


template<class T>
T alt<T>::iterador_rapido::at() {
    assert(in_range());
    return _p._mat[_row][_pos].val;
}


template<class T>
size_t alt<T>::iterador_rapido::col() {
    return _p._mat[_row][_pos].col;
}


template<class T>
size_t alt<T>::iterador_rapido::row() {
    return _row;
}


template<class T>
void alt<T>::iterador_rapido::next(bool wrap) {
    ++_pos;
    if (wrap && _pos >= _p._mat.size()) {
        ++_row;
        _pos = 0;
    }
}


template<class T>
bool alt<T>::iterador_rapido::in_range() {
    return 0 <= _row && _row < _p._mat.size() && 0 <= _pos && _pos < _p._mat[_row].size();
}


template<class T> typename
alt<T>::iterador_rapido alt<T>::begin(size_t i, size_t j) const {
    return iterador_rapido(*this, i, j);
}
