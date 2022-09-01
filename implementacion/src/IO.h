#ifndef IMPLEMENTACION_IO_H
#define IMPLEMENTACION_IO_H

#include "matriz.h"
#include "pagerank.h"
#include <fstream>


namespace IO {
    void stolcast(const string &val, size_t &res, const string &msg);

    void stodcast(const string &val, double &res, const string &msg);

    pagerank::in_file pagerank_read_in(const string &in, double p_val);

    pagerank::out_file pagerank_read_out(const string &in);

    void pagerank_write_out(const string &out, double p_val, const vector<double> &res);

    // void matrizf(string in, string out, string funct);
}


#endif //IMPLEMENTACION_IO_H
