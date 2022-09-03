#include "../../matriz-repr.h"


template<class T>
vlist<T>::vlist(size_t n, size_t m): _n(n), _m(m), _mat(vector<list<elem>>(n)) {}



template<class T>
const size_t &vlist<T>::n() const {
    return _n;
}


template<class T>
const size_t &vlist<T>::m() const {
    return _m;
}


template<class T>
T vlist<T>::at(size_t row, size_t col) const {
    auto it = _mat[row].begin();
    while(it != _mat[row].end() && it->col < col) ++it;
    if(it->col == col) return it->val;
    else return {};
}


template<class T>
void vlist<T>::set(size_t row, size_t col, T val) {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    auto it = _mat[row].begin();
    while(it != _mat[row].end() && it->col < col) ++it;
    set(it, row, col, val);
}
template<class T>
void vlist<T>::set(typename list<elem>::iterator it, size_t row, size_t col, T val) {
    assert(0 <= col && col < _m);
    if(compCero(val)){
        if (it->col == col) _mat[row].erase(it);
    } else if (it->col == col){
        it->val = val;
    }else {
        elem* newVal = (new elem);
        newVal->val = val;
        newVal->col = col;
        _mat[row].insert(it, *newVal);
    }
}

template<class T>
void vlist<T>::swap(size_t i1, size_t i2, bool rowOrder) {}



//
// IT RAPIDO
//


template<class T>
vlist<T>::iterador_rapido::iterador_rapido(const vlist<T> &p, size_t row, size_t col): _p(p), _row(row), _col(col){}


template<class T>
T vlist<T>::iterador_rapido::at() {
    assert(in_range());
    return _p.at(_row, _col);
}


template<class T>
size_t vlist<T>::iterador_rapido::col() {
    return _col;
}


template<class T>
size_t vlist<T>::iterador_rapido::row() {
    return _row;
}


template<class T>
void vlist<T>::iterador_rapido::next(bool wrap) {
    ++_col;
   if (wrap && _col >= _p._m) {
       ++_row;
       _col = 0;
   }
}


template<class T>
bool vlist<T>::iterador_rapido::in_range() {
    return 0 <= _row && _row < _p._n && 0 <= _col && _col < _p._m;
}


template<class T> typename vlist<T>::iterador_rapido vlist<T>::begin(size_t i, size_t j) const {
    return iterador_rapido(*this, i, j);
}
