//
// PAGERANK
//

template<class R>
matriz<R> pagerank::make(const in_file &params) {
    matriz<R> m(params.paginas, params.paginas);
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
    return m;
}


template<class R>
vector<double> pagerank::solve(const matriz<R> &mat) {
    vector<double> res = mat.solve(vector<double>(mat.n(), 1));
    // normalizar
    double s = {};
    for (auto & i : res) {
        s += i;
    }
    for (auto & i : res) {
        i = i / s;
    }
    return res;
}
