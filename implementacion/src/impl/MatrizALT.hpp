#include "../MatrizALT.h"

template<size_t n, size_t m, class T>
void MatrizALT<n, m, T>::set(size_t row, size_t col, T elem) {
    assert(0 <= row && row < n && 0 <= col && col < m);
    _m[_row[row]][_col[col]] = elem;
}

template<size_t n, size_t m, class T>
T Matriz<n, m, T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < n && 0 <= col && col < m);
    int pos = search(row, col);
    _last[row] = make_pair(col, i); // puede ponerse en el search tambien para que actualice siempre que se busca
    if(pos < _m[row].size() && _m[row][pos].col == col) 
        return _m[row][pos].val;
    else 
        return {};
}

template<size_t n, size_t m, class T>
int MatrizALT<n, m, T>::search(size_t row, size_t col) {
    assert(0 <= row && row < n && 0 <= col && col < m);
    if(_last[row].first <= col && col <=_m[row][_last[row].second].col) {
        return _last[row].second;
    }
    size_t i = 0, j = _m[row].size();
    while(i < j) {
        size_t k = (i+j)/2;
        if(_m[row][k].col < col) i = k + 1;
        else j = k;
    }
    return i;
}