// #include "../../matriz-repr.h"


// template<class T>
// llist<T>::llist(size_t n, size_t m): _n(n), _m(m), _last(vector<elem*>(n)), 
// _inicioRow(vector<elem*>(n)), _inicioCol(vector<elem*>(m)), _finRow(vector<elem*>(n)), _finCol(vector<elem*>(m)){
//     for(size_t i = 0; i < n; ++i) {
//         elem* finRow_i = (new elem);
//         finRow_i->row = i;
//         finRow_i->col = m;
//         _inicioRow[i] = finRow_i;
//         _finRow[i] = finRow_i;
//         _last[i] = finRow_i;
//     }
//     for(size_t i = 0; i < m; ++i) {
//         elem* finCol_i = (new elem);
//         finCol_i->row = n;
//         finCol_i->col = i;
//         _inicioCol[i] = finCol_i;
//         _finCol[i] = finCol_i;
//     }

// }


// template<class T>
// typename llist<T>::elem* llist<T>::inicioRow(size_t row) {
//     return _inicioRow[row];
// }

// template<class T>
// typename llist<T>::elem* llist<T>::finRow(size_t row) {
//     return _finRow[row];
// }

// template<class T>
// typename llist<T>::elem* llist<T>::inicioCol(size_t col) {
//     return _inicioCol[col];
// }

// template<class T>
// typename llist<T>::elem* llist<T>::finCol(size_t col) {
//     return _finCol[col];
// }

// template<class T>
// const size_t &llist<T>::n() const {
//     return _n;
// }


// template<class T>
// const size_t &llist<T>::m() const {
//     return _m;
// }


// template<class T>
// T llist<T>::at(size_t row, size_t col) const {
//     assert(0 <= row && row < _n && 0 <= col && col < _m);
//     elem* x = search(row, col, true);
//     if(x->col != col) 
//         return {};
//     else 
//         return x->val;
// }


// template<class T>
// void llist<T>::set(size_t row, size_t col, T val) {
//     assert(0 <= row && row < _n && 0 <= col && col < _m);
//     elem* x = search(row, col, true);
//     if(x->col != col){
//         if(compCero(val)) return;
//         elem* nCol = search(row, col, false);

//         // nuevo valor en la matriz inicializado
//         elem* newVal = new elem;
//         newVal->col = col;
//         newVal->row = row;
//         newVal->nextInCol = nCol;
//         newVal->nextInRow = x; 
//         newVal->val = val;
//         newVal->prevInRow = x->prevInRow; // sabemos que por lo menos hay un elemento en cada fila
//         newVal->prevInCol = nCol->prevInCol; // sabemos que por lo menos hay un elemento en cada columna

//         // actualizo la fila
//         if(x->prevInRow != nullptr) x->prevInRow->nextInRow = newVal;
//         else _inicioRow[row] = newVal;
//         x->prevInRow = newVal;

//         // actualizo la columna
//         if(nCol->prevInCol != nullptr) nCol->prevInCol->nextInCol = newVal;
//         else _inicioCol[col] = newVal;
//         nCol->prevInCol = newVal;
        
//         _last[row] = newVal;
//     } else {
//         if(compCero(val)) {
//             _last[row] =(x->nextInRow);
//             remove(x);
//         }
//         else {
//             _last[row] = x;
//             x->val = val;
//         }
//     }
// }

// template<class T>
// void llist<T>::remove(elem* x) {
//     // actualizo la fila
//     x->nextInRow->prevInRow = x->prevInRow;
//     if(x->prevInRow != nullptr) x->prevInRow->nextInRow = x->nextInRow;
//     else _inicioRow[x->row] = x->nextInRow;

//     // actualizo la columna
//     x->nextInCol->prevInCol = x->prevInCol;
//     if(x->prevInCol != nullptr) x->prevInCol->nextInCol = x->nextInCol;
//     else _inicioCol[x->col] = x->nextInCol;

//     delete x;
// }

// template<class T>
// void llist<T>::swap(size_t i1, size_t i2, bool rowOrder) {}


// template<class T>
// typename llist<T>::elem* llist<T>::search(size_t row, size_t col, bool dir) const {
//     // dir == true es busqueda de row, dir == false es busqueda de col
//     // sabemos que hay por lo menos un elemento en cada fila y en cada columna
//     assert(0 <= row && row < _n && 0 <= col && col < _m);
//     if(_last[row]->col == col) 
//         return _last[row];
//     if(dir && _last[row]->col < col && col <= _last[row]->nextInRow->col)  
//         return _last[row]->nextInRow;
//     if(!dir && row && _last[row-1]->col == col) 
//         return _last[row-1]->nextInCol;

//     elem* actual = dir ? _inicioRow[row] : _inicioCol[col];
//     if(dir) 
//         while(actual->col < col) 
//             actual = actual->nextInRow;
//     else
//         while(actual->row < row) 
//             actual = actual->nextInCol;
        
//     return actual;
// }


// //
// // IT RAPIDO
// //


// template<class T>
// llist<T>::iterador_rapido::iterador_rapido(const llist<T> &p, size_t row, size_t col): _p(p) {
//     if (0 <= row && row < _p._n && 0 <= col && col < _p._m) {
//         _actual = (p.search(row, col, true));
//     } else {
//         _actual = nullptr;
//     }

// }
// template<class T>
// llist<T>::iterador_rapido::iterador_rapido(const iterador_rapido &it):_p(it._p), _actual(it._actual){}


// template<class T>
// T llist<T>::iterador_rapido::at() {
//     assert(in_range());
//     return _actual->val;
// }


// template<class T>
// size_t llist<T>::iterador_rapido::col() {
//     return _actual->col;
// }


// template<class T>
// size_t llist<T>::iterador_rapido::row() {
//     return _actual->row;
// }


// template<class T>
// void llist<T>::iterador_rapido::next(bool wrap) {
//     if(_actual->nextInRow != nullptr) _actual = _actual->nextInRow;
//     if (wrap && _actual->col == _p._m) {
//         if(_actual->row == _p._n-1) _actual = nullptr;
//         else _actual = _p._inicioRow[_actual->row + 1];
//     }
// }
// template<class T>
// void llist<T>::iterador_rapido::nextInCol() {
//     if(_actual->nextInCol != nullptr) _actual = _actual->nextInRow;
// }

// template<class T>
// void llist<T>::iterador_rapido::remove(bool dir) {
//     if(dir) {
//         (*this).next(false);
//         if(_actual->prevInRow != nullptr) _p.remove(_actual->prevInRow);
//     } else {
//         (*this).nextInCol();
//         if(_actual->prevInCol != nullptr) _p.remove(_actual->prevInCol);
//     }
// }

// template<class T>
// void llist<T>::iterador_rapido::set(T val) {
//     _actual->val = val;
// }


// template<class T>
// bool llist<T>::iterador_rapido::in_range() {
//     return _actual != nullptr && 0 <= _actual->row && _actual->row < _p._n && 0 <= _actual->col && _actual->col < _p._m;
// }


// template<class T> typename
// llist<T>::iterador_rapido llist<T>::begin(size_t i, size_t j) const {
//     return iterador_rapido(*this, i, j);
// }

// template<class T> typename
// llist<T>::iterador_rapido llist<T>::begin(const iterador_rapido& it) const {
//     return iterador_rapido(it);
// }