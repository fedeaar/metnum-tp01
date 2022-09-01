#include "../IO.h"


void IO::stolcast(const string &val, size_t &res, const string &msg) {
    try {
        res = std::stoll(val);
    } catch(std::invalid_argument &ia) {
        throw std::invalid_argument(msg);
    }
}


void IO::stodcast(const string &val, double &res, const string &msg) {
    try {
        res = std::stod(val);
    } catch(std::invalid_argument &ia) {
        throw std::invalid_argument(msg);
    }
}


pagerank::in_file IO::pagerank_read_in(const string &in, double p_val) {
    ifstream file {in};
    if (!file.is_open()) {
        throw std::invalid_argument("no se pudo leer el archivo: " + in + ".");
    }
    // cantidad de paginas
    string _paginas {};
    std::getline(file, _paginas);
    size_t paginas {};
    stolcast(_paginas, paginas, "error de formato: linea 1.");
    // cantidad de links
    string _links {};
    std::getline(file, _links);
    size_t links {};
    stolcast(_links, links, "error de formato: linea 2.");
    // init store
    pagerank::in_file params(paginas, links, p_val);
    // in coords
    string _i, _j;
    size_t i, j, k = 2;
    while (file >> _j >> _i) {
        string msg = "error de formato: linea " + std::to_string(k) + ".";
        stolcast(_i, i, msg);
        stolcast(_j, j, msg);
        params.relaciones.emplace_back(pagerank::coords{i, j});
    }
    return params;
}


pagerank::out_file IO::pagerank_read_out(const string &in) {
    ifstream file {in};
    if (!file.is_open()) {
        throw std::invalid_argument("no se pudo leer el archivo: " + in + ".");
    }
    // valor p
    string _p_val {};
    std::getline(file, _p_val);
    double p_val {};
    stodcast(_p_val, p_val, "error de formato: linea 1.");
    // init store
    pagerank::out_file params(p_val);
    // in xi
    string _xi;
    double xi;
    size_t k = 1;
    while (std::getline(file, _xi)) {
        string msg = "error de formato: linea " + std::to_string(k) + ".";
        stodcast(_xi, xi, msg);
        params.solucion.push_back(xi);
    }
    return params;
}


void IO::pagerank_write_out(const string &out,  double p_val, const vector<double> &res) {
    ofstream file {out};
    file << p_val << '\n';
    for (auto &xi : res) {
        file << xi << '\n';
    }
    file.close();
}
