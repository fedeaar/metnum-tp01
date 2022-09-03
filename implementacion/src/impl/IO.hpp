//
// IO
//

template<class R>
void IO::pagerank_write_matriz(const string &out, const matriz<R> &mat) {
    ofstream file {out};
    file << mat;
    file.close();
}
