#include "../IO.h"


//
// IO
//

size_t IO::stolcast(const string &val, const string &msg) {
    size_t res;
    try {
        res = std::stoll(val);
    } catch(std::invalid_argument &ia) {
        throw std::invalid_argument(msg);
    }
    return res;
}


double IO::stodcast(const string &val, const string &msg) {
    double res;
    try {
        res = std::stod(val);
    } catch(std::invalid_argument &ia) {
        throw std::invalid_argument(msg);
    }
    return res;
}


string IO::filename(const string &path) {
    string name;
    // encontrar nombre
    auto delim = path.find_last_of('/');
    if (delim != string::npos) {
        name = path.substr(delim + 1, path.size());
    } else {
        name = path;
    }
    // remover extension
    delim = name.find_last_of('.');
    if (delim != string::npos) {
        name = name.substr(0, delim);
    }
    return name;
}


map<string, string> IO::oparams(int argc,  char** argv) {
    map<string, string> params;
    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] != '-') {
            continue;
        }
        string arg = argv[i];
        string param;
        string val;
        auto delim = arg.find('=');
        if (delim != string::npos) {
            param = arg.substr(0, delim);
            val = arg.substr(delim + 1, arg.size());
        } else {
            param = arg;
            val = "true";
        }
        params[param] = val;
    }
    return params;
}




//
// PAGERANK
//

pagerank::in_file IO::pagerank_read_in(const string &in, double p_val) {
    ifstream file {in};
    if (!file.is_open()) {
        throw std::invalid_argument("no se pudo leer el archivo: " + in + ".");
    }
    // cantidad de paginas
    string _paginas {};
    std::getline(file, _paginas);
    size_t paginas = stolcast(_paginas, "error de formato: linea 1.");
    // cantidad de links
    string _links {};
    std::getline(file, _links);
    size_t links = stolcast(_links, "error de formato: linea 2.");
    // init store
    pagerank::in_file params(paginas, links, p_val);
    // in coords
    string _i, _j;
    size_t i, j, k = 2;
    while (file >> _j >> _i) {
        string msg = "error de formato: linea " + std::to_string(k) + ".";
        i = stolcast(_i, msg);
        j = stolcast(_j, msg);
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
    double p_val = stodcast(_p_val, "error de formato: linea 1.");
    // init store
    pagerank::out_file params(p_val);
    // in xi
    string _xi;
    double xi;
    size_t k = 1;
    while (std::getline(file, _xi)) {
        string msg = "error de formato: linea " + std::to_string(k) + ".";
        xi = stodcast(_xi, msg);
        params.solucion.push_back(xi);
    }
    return params;
}


void IO::pagerank_write_out(const string &out,  double p_val, const vector<double> &res, int precision) {
    ofstream file {out};
    file << p_val << '\n';
    for (auto &xi : res) {
        file << std::setprecision(precision) << std::fixed << xi << '\n';
    }
    file.close();
}


void IO::pagerank_write_time(const string &out, const chrono::microseconds &time) {
    ofstream file {out};
    file << "format: microseconds\n" << time.count() << '\n';
    file.close();
}
