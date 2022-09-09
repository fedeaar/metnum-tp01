//
// PAGERANK
//

template<class R>
matriz<R> pagerank::make(const in_file &params) {
    matriz<R> m = identity<R>(params.paginas);
    // m = I
    vector<double> grado(params.paginas);
    for (auto &r: params.relaciones) {
        ++grado[r.j - 1];
    }
    for (auto &r: params.relaciones) {
        if (r.i != r.j) {
            m.set(r.i - 1, r.j - 1, -params.p_val / grado[r.j - 1]);
        }
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
