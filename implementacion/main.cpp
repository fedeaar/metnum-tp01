#include "./src/IO.h"
#include "./src/matriz/matriz_alt.h"

#include <map>


int main(int argc,  char** argv) {

    if (argc < 3) {
        cout << "error: cantidad invalida de parametros.\n" <<
                "expected: [source] [valor_p] ?-out='./' ?-debug" << endl;
        return -1;
    }

    // file loc
    string in = argv[1];
    // file name
    string file_name;
    auto delim = in.find_last_of('/');
    if (delim != string::npos) {
        file_name = in.substr(delim + 1, in.size());
    } else {
        file_name = in;
    }
    // remover extension del nombre
    delim = file_name.find_last_of('.');
    if (delim != string::npos) {
        file_name = file_name.substr(0, delim);
    }

    // p_val
    double p_val {};
    IO::stodcast(argv[2], p_val, "error: el valor p no se pudo interpretar como double.");

    // params opcionales
    map<string, string> args;
    for (int i = 3; i < argc; ++i) {
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
        args[param] = val;
    }
    // out_dir
    string outdir = args.count("-out") ? args.at("-out") : "./";
    if (outdir[outdir.length() - 1] != '/') {
        outdir += '/';
    }
    // debug flag
    bool debug = args.count("-debug");

    // exe
    cout << "leyendo el archivo: " + in << ".\n";
    pagerank::in_file data = IO::pagerank_read_in(in, p_val);

    cout << "creando matriz I - pWD...\n";
    matriz<alt> mat = pagerank::make<alt>(data);
    if (debug) {
        string matriz_out = outdir + file_name + "_debug.out";
        cout << "-debug- guardando matriz en: " + matriz_out << " (si el path existe)." << endl;
        IO::pagerank_write_matriz(matriz_out, mat);
    }

    cout << "calculando PageRank...\n";
    vector<double> solucion = pagerank::solve(mat);
    string out = outdir + file_name + ".out";
    cout << "guardando resultado: " + out << " (si el path existe).";
    IO::pagerank_write_out(out, p_val, solucion);

    return 0;
}
