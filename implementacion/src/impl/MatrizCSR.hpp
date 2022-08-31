#include "../MatrizCSR.h"




template<class T>
MatrizCSR<T>::MatrizCSR(size_t n, size_t m): n(n), m(m), _m(n), _last(vector<cache>(n), Matriz<T>(n, m)){
    for(int i =0 ; i < n; ++i) _last[i].to = m;
}


template<class T>
MatrizCSR<T>::MatrizCSR(const MatrizCSR<T> &b): MatrizCSR(b.n, b.m) {
    *this = b;
}


template<class T>
MatrizCSR<T>::MatrizCSR(const initializer_list<initializer_list<T>> &b): MatrizCSR(b.size(), (*b.begin()).size()) {
    *this = b;
}


template<class T>
void MatrizCSR<T>::set(size_t row, size_t col, T elem) {
    assert(0 <= row && row < n && 0 <= col && col < m);
    size_t inicioRow = _rows[row];
    size_t finRow = _rows[row+1];
    int pos = lower_bound(_m.begin() + inicioRow, _m.begin() + finRow, col) - _m.begin();
    _m.insert(pos, col)

}

template<class T>
T MatrizCSR<T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < n && 0 <= col && col < m);
    if(!_m[row].size()) return {};
    int pos = search(row, col);
    updateLast(pos);
    if(pos < _m[row].size() && _m[row][pos].col == col)
        return _m[row][pos].val;
    else 
        return {};
}

