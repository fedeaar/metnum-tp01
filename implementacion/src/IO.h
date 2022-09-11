#ifndef IMPLEMENTACION_IO_H
#define IMPLEMENTACION_IO_H

#include "pagerank.h"
#include <chrono>
#include <iomanip>
#include <fstream>
#include <map>


namespace IO {

    /** UTILS */

    const int PRECISION = 15;

    size_t stolcast(const string &val, const string &msg);

    double stodcast(const string &val, const string &msg);

    map<string, string> oparams(int argc,  char** argv);

    string filename(const string& path);


    /** PAGERANK IO */

    pagerank::in_file pagerank_read_in(const string &in, double p_val);

    pagerank::out_file pagerank_read_out(const string &in);

    void pagerank_write_out(const string &out, double p_val, const vector<double> &res, int precision=PRECISION);

    void pagerank_write_time(const string &out, const chrono::microseconds &time);

    template<class R> void pagerank_write_matriz(const string &out, const matriz<R>& mat, int precision=PRECISION);
}


#include "./impl/IO.hpp"
#endif //IMPLEMENTACION_IO_H
