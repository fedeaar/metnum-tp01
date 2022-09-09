//
// IO
//

template<class R>
void IO::pagerank_write_matriz(const string &out, const matriz<R> &mat, int precision) {
    ofstream file {out};
    file << std::setprecision(precision) << std::fixed << mat;
    file.close();
}
