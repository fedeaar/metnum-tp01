#include "../../matriz/matriz_llist.h"


//
// LLIST PRIVATE
//

typename llist::elem* llist::inicioRow(size_t row) const {
    return _inicioRow[row];
}


typename llist::elem* llist::finRow(size_t row) const {
    return _finRow[row];
}


typename llist::elem* llist::inicioCol(size_t col) const {
    return _inicioCol[col];
}


typename llist::elem* llist::finCol(size_t col) const {
    return _finCol[col];
}


typename llist::elem* llist::search(size_t row, size_t col, bool dir) const {
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


void llist::remove(elem* x) {
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




//
// LLIST
//

llist::llist(size_t n, size_t m): _n(n), _m(m), _last(vector<elem*>(n)),
_inicioRow(vector<elem*>(n)), _inicioCol(vector<elem*>(m)), _finRow(vector<elem*>(n)), _finCol(vector<elem*>(m)){
    for(size_t i = 0; i < n; ++i) {
        elem* finRow_i = (new elem);
        finRow_i->row = i;
        finRow_i->col = m;
        _inicioRow[i] = finRow_i;
        _finRow[i] = finRow_i;
        _last[i] = finRow_i;
    }
    for(size_t i = 0; i < m; ++i) {
        elem* finCol_i = (new elem);
        finCol_i->row = n;
        finCol_i->col = i;
        _inicioCol[i] = finCol_i;
        _finCol[i] = finCol_i;
    }
}


double llist::at(size_t row, size_t col) const {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    elem* x = search(row, col, true);
    if(x->col != col)
        return {};
    else
        return x->val;
}


void llist::set(size_t row, size_t col, double val) {
    assert(0 <= row && row < _n && 0 <= col && col < _m);
    elem* x = search(row, col, true);
    if(x->col != col){
        if(std::abs(val) <= EPSILON) return;
        elem* nCol = search(row, col, false);

        // nuevo valor en la matriz inicializado
        elem* newVal = new elem;
        newVal->col = col;
        newVal->row = row;
        newVal->nextInCol = nCol;
        newVal->nextInRow = x;
        newVal->val = val;
        newVal->prevInRow = x->prevInRow; // sabemos que por lo menos hay un elemento en cada fila
        newVal->prevInCol = nCol->prevInCol; // sabemos que por lo menos hay un elemento en cada columna

        // actualizo la fila
        if(x->prevInRow != nullptr) x->prevInRow->nextInRow = newVal;
        else _inicioRow[row] = newVal;
        x->prevInRow = newVal;

        // actualizo la columna
        if(nCol->prevInCol != nullptr) nCol->prevInCol->nextInCol = newVal;
        else _inicioCol[col] = newVal;
        nCol->prevInCol = newVal;

        _last[row] = newVal;
    } else {
        if(std::abs(val) <= EPSILON) {
            _last[row] =(x->nextInRow);
            remove(x);
        } else {
            _last[row] = x;
            x->val = val;
        }
    }
}


llist::iterator llist::begin(size_t i, size_t j) {
    return llist::iterator(*this, i, j);
}


llist::iterator llist::begin(const iterator &it) {
    return {it};
}


llist::const_iterator llist::begin(size_t i, size_t j) const {
    return llist::const_iterator(*this, i, j);
}


llist::const_iterator llist::begin(const const_iterator &it) const {
    return {it};
}




//
// CONST ITERATOR
//

llist::const_iterator::const_iterator(const llist &p, size_t row, size_t col): _p(p) {
    if (0 <= row && row < _p._n && 0 <= col && col < _p._m) {
        _actual = (p.search(row, col, true));
    } else {
        _actual = nullptr;
    }
}


llist::const_iterator::const_iterator(const const_iterator &it) = default;


bool llist::const_iterator::in_range() const {
    return _actual != nullptr && 0 <= _actual->row && _actual->row < _p._n && 0 <= _actual->col && _actual->col < _p._m;
}


size_t llist::const_iterator::col() const {
    return _actual->col;
}


size_t llist::const_iterator::row() const {
    return _actual->row;
}


double llist::const_iterator::at() const {
    assert(in_range());
    return _actual->val;
}


void llist::const_iterator::next(bool rowOrder) {
    if (rowOrder) {
        if(_actual->nextInRow != nullptr) _actual = _actual->nextInRow;
    } else {
        if(_actual->nextInCol != nullptr) _actual = _actual->nextInCol;
    }

}




//
// LLIST ITERATOR
//

llist::iterator::iterator(llist &p, size_t row, size_t col): const_iterator(p, row, col), _p(p) {}


llist::iterator::iterator(const llist::iterator &p) = default;


void llist::iterator::remove(bool rowOrder) {
    if(rowOrder) {
        (*this).next();
        if(_actual->prevInRow != nullptr) _p.remove(_actual->prevInRow);
    } else {
        (*this).next(true);
        if(_actual->prevInCol != nullptr) _p.remove(_actual->prevInCol);
    }
}


void llist::iterator::set(double val) {
    _actual->val = val;
}
