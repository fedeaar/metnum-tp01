//#ifndef IMPLEMENTACION_MATRIZ_VLIST_H
//#define IMPLEMENTACION_MATRIZ_VLIST_H
//
//#include <vector>
//#include <list>
//#include <cassert>
//#include "matriz.h"
//
//using namespace std;
//
//
//template<class T>
//class vlist {
//protected:
//    size_t _n, _m;
//public:
//    struct elem {
//        T val {};
//        size_t col = -1;
//    };
//    vector<list<elem>> _mat;
//    vlist(size_t n, size_t m);
//
//    const size_t &n() const;
//    const size_t &m() const;
//    T at(size_t row, size_t col) const;
//    void set(size_t row, size_t col, T val);
//    void set(typename list<elem>::iterator it, size_t row, size_t col, T val);
//    void swap(size_t i1, size_t i2, bool rowOrder);
//
//    class iterador_rapido {
//    protected:
//        size_t _row;
//        size_t _col;
//        const vlist<T> &_p;
//
//    public:
//        iterador_rapido(const vlist<T> &p, size_t row, size_t col);
//        T at();
//        void next(bool wrap=true);
//        bool in_range();
//        size_t col();
//        size_t row();
//    };
//
//    iterador_rapido begin(size_t i=0, size_t j = 0) const;
//    iterador_rapido begin(const iterador_rapido& it) const;
//};
//
//template<class T>
//bool compCero(T a) {
//    return abs((double) a) < 1e-4;
//}


//#endif //IMPLEMENTACION_MATRIZ_VLIST_H
