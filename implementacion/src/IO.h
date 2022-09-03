#ifndef IMPLEMENTACION_IO_H
#define IMPLEMENTACION_IO_H

#include "pagerank.h"
#include <fstream>


namespace IO {
    void stolcast(const string &val, size_t &res, const string &msg);

    void stodcast(const string &val, double &res, const string &msg);

    pagerank::in_file pagerank_read_in(const string &in, double p_val);

    pagerank::out_file pagerank_read_out(const string &in);

    void pagerank_write_out(const string &out, double p_val, const vector<double> &res);

    template<class R> void pagerank_write_matriz(const string &out, const matriz<R>& mat);
}


#include "./impl/IO.hpp"
#endif //IMPLEMENTACION_IO_H
