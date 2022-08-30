#include "./src/IO.h"

int main(int argc,  char** argv) {
    if (argc < 3 || argc > 5) {
        cout << "error: cantidad invalida de parametros.\n" <<
                "expected: [source] [valor_p] [dest=./resultado.txt]" << endl;
        return -1;
    }
    string in = argv[1];
    string out = argc == 5 ? argv[4] : "./resultado.txt";
    double p_val {};
    IO::stodcast(argv[2], p_val, "error: el valor p no se pudo interpretar como double.");
    IO::pagerank(in, out, p_val);
    return 0;
}
