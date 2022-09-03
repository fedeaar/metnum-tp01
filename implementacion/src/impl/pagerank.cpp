#include "../pagerank.h"


void normalize(vector<double> &v) {
    double s = {};
    for (auto & i : v) {
        s += i;
    }
    for (auto & i : v) {
        i = i / s;
    }
}


vector<double> pagerank::solve(in_file &params) {
    matriz<__ESTR__> w(params.paginas, params.paginas);
    vector<double> grado(params.paginas);
    for (auto &r: params.relaciones) {
        w.set(r.i - 1, r.j - 1, 1);
        ++grado[r.j - 1];
    }
    for (auto &r: grado) {
        r = r == 0 ? 0 : 1 / r;
    }
    matriz<__ESTR__> d = diagonal<__ESTR__>(grado);
    matriz<__ESTR__> i = identity<__ESTR__>(params.paginas);
    matriz<__ESTR__> ipwd = i - params.p_val * (w * d);
    vector<double> res = ipwd.solve(vector<double>(params.paginas, 1));
    normalize(res);
    return res;
}


vector<double> pagerank::solve_optimizado(in_file &params) {
    matriz<__ESTR__> m(params.paginas, params.paginas);
    // m = 0
    vector<double> grado(params.paginas);
    for (auto &r: params.relaciones) {
        m.set(r.i - 1, r.j - 1, -params.p_val);
        ++grado[r.j - 1];
    }
    // m = -pW
    for (auto jt = m.begin(); jt.in_range(); jt.next(false)) {
        for (auto it = m.begin(jt.row(), jt.col()); it.in_range(); it.next()) {
            double grado_i = grado[it.col()];
            double peso = grado_i == 0 ? 0 : 1 / grado_i;
            it.set(it.at() * peso);
        }
    }
    // m = -pWD
    for (size_t i = 0; i < params.paginas; ++i) {
        m.set(i, i, 1);
    }
    // m = I - pWD
    vector<double> res = m.solve(vector<double>(params.paginas, 1));
    normalize(res);

    return res;
}
