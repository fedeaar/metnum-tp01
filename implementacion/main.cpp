#include "./src/IO.h"

int main(int argc,  char** argv) {
    if (argc < 3 || argc > 4) {
        cout << "error: cantidad invalida de parametros.\n" <<
                "expected: [source] [valor_p] [dest=./resultado.txt]" << endl;
        return -1;
    }
    string in = argv[1];
    string out = argc == 4 ? argv[3] : "./resultado.txt";

    double p_val {};
    IO::stodcast(argv[2], p_val, "error: el valor p no se pudo interpretar como double.");

    cout << "leyendo el archivo: " + in << ".\n";
    PageRank::in_file data = IO::pagerank_read_in(in, p_val);

    cout << "calcuando pagerank...\n";
    vector<double> solucion = PageRank::solve_optimizado(data);

    cout << "guardando resultado en: " + out << " (si existe el directorio)." << endl;
    IO::pagerank_write_out(out, p_val, solucion);

    return 0;
}
