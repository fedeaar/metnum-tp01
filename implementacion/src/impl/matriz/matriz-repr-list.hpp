#include "../../matriz-repr.h"


template<class T>
list<T>::list(size_t n, size_t m): _n(n), _m(m), _last(vector<elem*>(n)), 
_inicioRow(vector<elem*>(n)), _inicioCol(vector<elem*>(m)), _finRow(vector<elem*>(n)), _finCol(vector<elem*>(m)){
    for(size_t i = 0; i < n; ++i) {
        elem finRow_i;
        finRow_i.row = i;
        finRow_i.col = n;
        _inicioRow[i] = &finRow_i;
        _finRow[i] = &finRow_i;
        _last[i] = &finRow_i;
    }
    for(size_t i = 0; i < m; ++i) {
        elem finCol_i;
        finCol_i.col = i;
        finCol_i.col = m;
        _inicioCol[i] = &finCol_i;
        _finCol[i] = &finCol_i;
    }
}


template<class T>
const typename list<T>::elem* list<T>::inicioRow(size_t row) const {
    return _inicioRow[row];
}

template<class T>
const typename list<T>::elem* list<T>::finRow(size_t row) const {
    return _finRow[row];
}

template<class T>
const typename list<T>::elem* list<T>::inicioCol(size_t col) const {
    return _inicioCol[col];
}

template<class T>
const typename list<T>::elem* list<T>::finCol(size_t col) const {
    return _finCol[col];
}

template<class T>
const size_t &list<T>::n() const {
    return _n;
}


template<class T>
const size_t &list<T>::m() const {
    return _m;
}


template<class T>
T list<T>::at(size_t row, size_t col) const {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    elem* x = search(row, col);
    if(x->col != col) 
        return {};
    else 
        return x->val;
}


template<class T>
void list<T>::set(size_t row, size_t col, T val) {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    elem* x = search(row, col);
    if(x->col != col){
        if(compCero(val)) return;
        elem* nCol = search(row, col, false);

        // nuevo valor en la matriz inicializado
        elem newVal;
        newVal.col = col;
        newVal.row = row;
        newVal.nextInCol = nCol;
        newVal.nextInRow = x; 
        newVal.prevInRow = x->prevInRow; // sabemos que por lo menos hay un elemento en cada fila
        newVal.prevInCol = nCol->prevInCol; // sabemos que por lo menos hay un elemento en cada columna

        // actualizo la fila
        x->prevInRow = &newVal;
        if(x->prevInRow != nullptr) x->prevInRow->nextInRow = &newVal;
        else _inicioRow[row] = &newVal;

        // actualizo la columna
        nCol->prev = &newVal;
        if(nCol->prevInCol != nullptr) nCol->prevInCol->nextInCol = &newVal;
        else _inicioCol[col] = &newVal;
        
        _last[row] = &newVal;
    } else {
        if(compCero(val)) {
            _last[row] =(x->nextInRow);
            remove(x);
        }
        else {
            _last[row] = x;
            x->val = val;
        }
    }
}


template<class T>
void list<T>::remove(elem* x) {
    // actualizo la fila
    x->nextInRow->prevInRow = x->prevInRow;
    if(x->prevInRow != nullptr) x->prevInRow->nextInRow = x->nextInRow;
    else _inicioRow[x->row] = x->nextInRow;

    // actualizo la columna
    x->nextInCol->prevInCol = x->prevInCol;
    if(x->prevInCol != nullptr) x->prevInCol->nextInCol = x->nextInCol;
    else _inicioCol[x->col] = x->nextInCol;

    delete x;
}

template<class T>
void list<T>::swap(size_t i1, size_t i2, bool rowOrder) {}


template<class T>
typename list<T>::elem* list<T>::search(size_t row, size_t col, bool dir = true) const { 
    // dir == true es busqueda de row, dir == false es busqueda de col
    // sabemos que hay por lo menos un elemento en cada fila y en cada columna
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    if(_last[row]->col == col) 
        return _last[row];
    if(dir && _last[row]->col < col && col <= _last[row]->nextInRow->col)  
        return _last[row]->nextInRow;
    if(!dir && row && _last[row-1]->col == col) 
        return _last[row-1]->nextInCol;

    elem* actual = dir ? _inicioRow[row] : _inicioCol[col];
    if(dir) 
        while(actual->col < col) 
            actual = actual->nextInRow;
    else
        while(actual->row < row) 
            actual = actual->nextInCol;
        
    return actual;
}


//
// IT RAPIDO
//

template<class T>
list<T>::iterador_rapido::iterador_rapido(const list<T> &p, size_t row, size_t col): _p(p) {
    if (0 <= row && row < _p._n && 0 <= col && col < _p._m) {
        _actual = (p.search(row, col));
    } else {
        _actual = nullptr;
    }
}


template<class T>
T list<T>::iterador_rapido::at() {
    assert(in_range());
    return _actual.val;
}


template<class T>
size_t list<T>::iterador_rapido::col() {
    return _actual->col;
}


template<class T>
size_t list<T>::iterador_rapido::row() {
    return _actual->row;
}


template<class T>
void list<T>::iterador_rapido::next(bool wrap) {
    _actual = _actual->nextInRow;
    if (wrap && _actual->col == _p._m) {
        if(_actual->row == _p._n-1) _actual = nullptr;
        else _actual = _p._inicioRow[_actual->row + 1];
    }
}

template<class T>
void list<T>::iterador_rapido::next(bool wrap) {
    _actual = _actual->nextInRow;
    if (wrap && _actual->col == _p._m) {
        if(_actual->row == _p._n-1) _actual = nullptr;
        else _actual = _p._inicioRow[_actual->row + 1];
    }
}


template<class T>
bool list<T>::iterador_rapido::in_range() {
    return 0 <= _actual->row && _actual->row < _p._n && 0 <= _actual->col && _actual->col < _p._m;
}


template<class T> typename
list<T>::iterador_rapido list<T>::begin(size_t i, size_t j) const {
    return iterador_rapido(*this, i, j);
}
