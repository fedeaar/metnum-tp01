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


void IO::pagerank(const string &in, const string &out, double p_val) {
    ifstream file {in};
    if (!file.is_open()) {
        throw std::invalid_argument(error_1 + ": " + in + ".");
    }
    // cantidad de paginas
    string _paginas {};
    std::getline(file, _paginas);
    size_t paginas {};
    stolcast(_paginas, paginas, error_2 + ": " + "linea 1.");

    // cantidad de links
    string _links {};
    std::getline(file, _links);
    size_t links {};
    stolcast(_links, links, error_2 + ": " + "linea 2.");

    // init store
    PageRank::params parametros(paginas, links, p_val);

    // in coords
    string _i, _j;
    size_t i, j, k = 2;
    while (file >> _j >> _i) {
        string msg = error_2 + ": " + "linea " + std::to_string(k) + ".";
        stolcast(_i, i, msg);
        stolcast(_j, j, msg);
        parametros.relaciones.emplace_back(i, j);
    }

    // solve
    vector<double> res = PageRank::solve(parametros);
}


