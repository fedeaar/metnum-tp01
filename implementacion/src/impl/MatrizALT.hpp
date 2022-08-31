#include "../MatrizALT.h"




template<class T>
MatrizALT<T>::MatrizALT(size_t n, size_t m): n(n), m(m), _m(n), _last(vector<cache>(n), Matriz<T>(n, m)){
    for(int i =0 ; i < n; ++i) _last[i].to = m;
}


template<class T>
MatrizALT<T>::MatrizALT(const MatrizALT<T> &b): MatrizALT(b.n, b.m) {
    *this = b;
}


template<class T>
MatrizALT<T>::MatrizALT(const initializer_list<initializer_list<T>> &b): MatrizALT(b.size(), (*b.begin()).size()) {
    *this = b;
}


template<class T>
void MatrizALT<T>::set(size_t row, size_t col, T elem) {
    assert(0 <= row && row < n && 0 <= col && col < m);
    int pos = search(row, col);
    T tmp {};
    if(pos < _m[row].size() && _m[row][pos].col == col) 
        _m[row][pos].val = elem;
    else if(elem != tmp) //agregar epsilon a la comparacion
        _m[row].insert(pos, elem);

    updateLast(row, pos); 
}

template<class T>
T MatrizALT<T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < n && 0 <= col && col < m);
    if(!_m[row].size()) return {};
    int pos = search(row, col);
    updateLast(pos);
    if(pos < _m[row].size() && _m[row][pos].col == col)
        return _m[row][pos].val;
    else 
        return {};
}

template<class T>
int MatrizALT<T>::search(size_t row, size_t col) {
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

template<class T>
void MatrizALT<T>::updateLast(size_t row, size_t pos) {
    assert(0 <= row && row < n && 0 <= pos && pos <= _m[row].size());
    if(pos == _m[row].size()) {
        if(pos) {
            _last[row].from = _m[row].back().col + 1;
            _last[row].to = m;
            _last[row].next = m;
            _last[row].pos = pos;
        }
    } else {
        _last[row].from = _m[row][max((size_t) 0, pos-1)].col;
        _last[row].to = _m[row][pos].col;
        _last[row].next = pos + 1 < _m[row].size() ? _m[row][pos+1].col : m;
        _last[row].pos = pos;
    }
}