#include "./src/IO.h"
#include "./src/matriz/matriz_alt.h"

#include <map>


int main(int argc,  char** argv) {

    if (argc < 3) {
        cout << "error: cantidad invalida de parametros.\n" <<
                "expected: [source] [valor_p] ?-out='./' ?-debug" << endl;
        return -1;
    }

    // params fijos
    string in = argv[1];
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
    string outdir = args.count("-out") ? args.at("-out") : "./";
    if (outdir[outdir.length() - 1] != '/') {
        outdir += '/';
    }
    bool debug = args.count("-debug");

    // exe
    cout << "leyendo el archivo: " + in << ".\n";
    pagerank::in_file data = IO::pagerank_read_in(in, p_val);

    cout << "creando matriz I - pWD...\n";
    matriz<alt> mat = pagerank::make<alt>(data);
    if (debug) {
        string matriz_out = outdir + "matriz.txt";
        cout << "--DEBUG-- guardando matriz en: " + matriz_out << " (si es una direccion valida)." << endl;
        IO::pagerank_write_matriz(matriz_out, mat);
    }

    cout << "calculando PageRank...\n";
    vector<double> solucion = pagerank::solve(mat);
    string out = outdir + "resultado.txt";
    cout << "guardando resultado: " + out << " (si es una direccion valida)." << endl;
    IO::pagerank_write_out(out, p_val, solucion);

    return 0;
}
