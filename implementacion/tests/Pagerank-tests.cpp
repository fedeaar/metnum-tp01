#include <chrono>

#include "gtest-1.8.1/gtest.h"
#include "../src/IO.h"

using namespace std::chrono;

class PageRankTest : public testing::Test {
protected:
    string basedir;
    double epsilon;
    void SetUp() override {
        basedir = "../tests/files/";
        epsilon = 1e-4;
    }

    bool base_test(const string &in, const string &out);
};

bool PageRankTest::base_test(const string &in, const string &out) {

    cout << "testing: " << in << endl;
    auto start = high_resolution_clock::now();
    pagerank::out_file expected = IO::pagerank_read_out(basedir + out);
    auto stop = high_resolution_clock::now();
    cout << "tiempo read out file: " << duration_cast<milliseconds>(stop-start).count() << " ms." << endl;

    start = high_resolution_clock::now();
    pagerank::in_file data = IO::pagerank_read_in(basedir + in, expected.p_val);
    stop = high_resolution_clock::now();
    cout << "tiempo read in file: " << duration_cast<milliseconds>(stop-start).count() << " ms." << endl;

    start = high_resolution_clock::now();
    vector<double> solucion = pagerank::solve_optimizado(data);
    stop = high_resolution_clock::now();
    cout << "tiempo total calcular solucion: " << duration_cast<milliseconds>(stop-start).count() << " ms." << endl;

    bool res = (solucion.size() == expected.solucion.size());
    for (size_t i = 0; i < solucion.size() && res; ++i) {
        res = std::abs(solucion[i] - expected.solucion[i]) < epsilon;
    }
    return res;
}

TEST_F(PageRankTest, test_aleatorio) {
    bool res = base_test("test_aleatorio.txt", "test_aleatorio_desordenado.txt.out");
    EXPECT_TRUE(res);
}

TEST_F(PageRankTest, test_aleatorio_desordenado) {
    bool res = base_test("test_aleatorio_desordenado.txt", "test_aleatorio_desordenado.txt.out");
    EXPECT_TRUE(res);
}

TEST_F(PageRankTest, test_trivial) {
    bool res = base_test("test_trivial.txt", "test_trivial.txt.out");
    EXPECT_TRUE(res);
}

TEST_F(PageRankTest, test_completo) {
    bool res = base_test("test_completo.txt", "test_completo.txt.out");
    EXPECT_TRUE(res);
}

TEST_F(PageRankTest, test_sin_links) {
    bool res = base_test("test_sin_links.txt", "test_sin_links.txt.out");
    EXPECT_TRUE(res);
}

TEST_F(PageRankTest, test_15_segundos) {
    bool res = base_test("test_15_segundos.txt", "test_15_segundos.txt.out");
    EXPECT_TRUE(res);
}

TEST_F(PageRankTest, test_30_segundos) {
    bool res = base_test("test_30_segundos.txt", "test_30_segundos.txt.out");
    EXPECT_TRUE(res);
}


