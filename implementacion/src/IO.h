#ifndef IMPLEMENTACION_IO_H
#define IMPLEMENTACION_IO_H

#include "Matriz.h"
#include "PageRank.h"
#include <fstream>


namespace IO {
    const string error_1 = "no se pudo abrir el archivo de entrada";
    const string error_2 = "informacion invalida en el archivo de entrada";
    const string error_3 = "informacion invalida en los parametros de entrada";

    void throwexcept(int error, const string &msg="");

    void stolcast(const string &val, size_t &res, const string &msg);

    void stodcast(const string &val, double &res, const string &msg);

    void pagerank(const string &in, const string &out, double p_val);

    // void matrizf(string in, string out, string funct);
}


#endif //IMPLEMENTACION_IO_H
