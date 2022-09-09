#include "./src/IO.h"
#include "./src/matriz/matriz_alt.h"
#include "./src/matriz/matriz_base.h"


#if ESTR == 1
    typedef base __ESTR__;
#elif ESTR == 2
    typedef alt __ESTR__;
#else
    typedef alt __ESTR__;
#endif


int main(int argc,  char** argv) {

    if (argc < 3 || argc > 8) {
        cout << "error: cantidad invalida de parametros.\n" <<
                "expected: [source] [valor_p]\n"  <<
                "optional: -out=./\n" <<
                "          -save_as=[source]\n" <<
                "          -presicion=15\n" <<
                "          -save_m\n" <<
                "          -time_it" << endl;
        return -1;
    }

    // in path
    string in_path = argv[1];
    string file_name = IO::filename(in_path);
    double p_val = IO::stodcast(argv[2], "error: el valor p no se pudo interpretar como double.");

    // params opcionales
    map <string, string> params = IO::oparams(argc, argv);
    string out_path = params.count("-out") ? params.at("-out") : "./";
    if (out_path[out_path.length() - 1] != '/') {
        out_path += '/';
    }
    string out_name = params.count("-save_as") ? params.at("-save_as") : file_name;

    // cout << "leyendo el archivo: " + in_path << ".\n";
    pagerank::in_file data = IO::pagerank_read_in(in_path, p_val);

    // cout << "calculando PageRank...\n";
    auto inicio = chrono::high_resolution_clock::now();
    matriz<__ESTR__> mat = pagerank::make<__ESTR__>(data);
    vector<double> solucion = pagerank::solve<__ESTR__>(mat);
    auto fin = chrono::high_resolution_clock::now();

    string out = out_path + out_name + ".out";
    // cout << "guardando resultado en: " + out << " (si el path existe).\n";
    IO::pagerank_write_out(out, p_val, solucion);

    if (params.count("-time_it")) {
        auto time = chrono::duration_cast<chrono::microseconds>(fin - inicio);
        string time_out = out_path + out_name + ".time";
        // cout << "guardando tiempo de ejecucion en: " + time_out << " (si el path existe).\n";
        IO::pagerank_write_time(time_out, time);
    }
    if (params.count("-save_m")) {
        string matriz_out = out_path + out_name + ".matriz";
        // cout << "guardando matriz en: " + matriz_out << " (si el path existe).\n";
        IO::pagerank_write_matriz(matriz_out, mat);
    }

    return 0;
}
