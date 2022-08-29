#include "../MatrizALT.h"

template<size_t n, size_t m, class T>
void MatrizALT<n, m, T>::set(size_t row, size_t col, T elem) {
    assert(0 <= row && row < n && 0 <= col && col < m);
    int pos = search(row, col);
    if(pos < _m[row].size() && _m[row][pos].col == col) 
        _m[row][pos].val = elem;
    else if(elem != {}) //agregar epsilon a la comparacion
        _m[row].insert(pos, elem);

    updateLast(row, pos); 
}

template<size_t n, size_t m, class T>
T Matriz<n, m, T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < n && 0 <= col && col < m);
    if(!_m[row].size()) return {};
    int pos = search(row, col);
    updateLast(pos);
    if(pos < _m[row].size() && _m[row][pos].col == col)
        return _m[row][pos].val;
    else 
        return {};
}

template<size_t n, size_t m, class T>
int MatrizALT<n, m, T>::search(size_t row, size_t col) {
    assert(0 <= row && row < n && 0 <= col && col < m);
    if(_last[row].from <= col && col <= _last[row].to)   return _last[row].pos;
    if(_last[row].to+1 <= col && col <= _last[row].next) return _last[row].pos + 1;
    size_t i = 0, j = _m[row].size();
    while(i < j) {
        size_t k = (i+j)/2;
        if(_m[row][k].col == col) return k;
        if(_m[row][k].col <  col) i = k + 1;
        else j = k;
    }
    return i;
}

template<size_t n, size_t m, class T>
void MatrizALT<n, m, T>::updateLast(size_t row, size_t pos) {
    assert(0 <= row && row < n && 0 <= pos && pos <= _m[row].size());
    if(pos == _m[row].size()) {
        if(pos) {
            _last[row].from = _m[row].back().col + 1;
            _last[row].to = m;
            _last[row].next = m;
            _last[row].pos = pos;
        }
    } else {
        _last[row].from = _m[row][max(0, pos-1)].col;
        _last[row].to = _m[row][pos].col;
        _last[row].next = pos + 1 < _m[row].size() ? _m[row][pos+1].col : m;
        _last[row].pos = pos;
    }
}