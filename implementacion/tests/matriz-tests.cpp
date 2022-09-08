#include "gtest-1.8.1/gtest.h"

#include "../src/matriz.h"
#include "../src/matriz/matriz_base.h"
#include "../src/matriz/matriz_alt.h"

#if ESTR == 1
    typedef base __ESTR__;
#elif ESTR == 2
    typedef alt __ESTR__;
#else
    typedef alt __ESTR__;
#endif


class MatrizTest : public testing::Test {
protected:
    matriz<__ESTR__> a {4, 4}, b {4, 4}, c {4, 4}, d {4, 4};
    void SetUp() override {
        a = {
            {1, 2, 3, 4},
            {4, 0, 0, 1},
            {1, 1, 1, 1},
            {1, 2, 3, 7}
        };
        b = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        c = {
            {1, 25, 3, 9},
            {4, 0, 7, 1},
            {1, 6, 6, 1},
            {1, 2, 0, 0}
        };
        d = {
            {0, 0, 0, 4},
            {1, 0, 0, 0},
            {0, 0, 3, 0},
            {0, 2, 0, 0}
        };
    }
};


TEST_F(MatrizTest, init) {
    array<array<int, 4>, 4> _a = {{
            {1, 2, 3, 4},
            {4, 0, 0, 1},
            {1, 1, 1, 1},
            {1, 2, 3, 7}
    }};
    array<array<int, 4>, 4> _b = {{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    }};
    array<array<int, 4>, 4> _c = {{
            {1, 25, 3, 9},
            {4, 0, 7, 1},
            {1, 6, 6, 1},
            {1, 2, 0, 0}
    }};
    array<array<int, 4>, 4> _d = {{
            {0, 0, 0, 4},
            {1, 0, 0, 0},
            {0, 0, 3, 0},
            {0, 2, 0, 0}
    }};
    for (auto it = a.begin(); it.in_range(); it.next()) {
        EXPECT_EQ(it.at(), _a[it.row()][it.col()]);
    }
    for (auto it = b.begin(); it.in_range(); it.next()) {
        EXPECT_EQ(it.at(), _b[it.row()][it.col()]);
    }
    for (auto it = c.begin(); it.in_range(); it.next()) {
        EXPECT_EQ(it.at(), _c[it.row()][it.col()]);
    }
    for (auto it = d.begin(); it.in_range(); it.next()) {
        EXPECT_EQ(it.at(), _d[it.row()][it.col()]);
    }
}


TEST_F(MatrizTest, suma) {
    matriz<__ESTR__> ab = {
        {2, 2, 3, 4},
        {4, 1, 0, 1},
        {1, 1, 2, 1},
        {1, 2, 3, 8}
    };
    matriz<__ESTR__> ac = {
        {2, 27, 6, 13},
        {8, 0, 7, 2},
        {2, 7, 7, 2},
        {2, 4, 3, 7}
    };
    matriz<__ESTR__> bd = {
        {1, 0, 0, 4},
        {1, 1, 0, 0},
        {0, 0, 4, 0},
        {0, 2, 0, 1}
    };
    matriz<__ESTR__> cb = {
        {2, 25, 3, 9},
        {4, 1, 7, 1},
        {1, 6, 7, 1},
        {1, 2, 0, 1}
    };
    EXPECT_TRUE(ab.eq(a + b));
    EXPECT_TRUE(ac.eq(a + c));
    EXPECT_TRUE(bd.eq(b + d));
    EXPECT_TRUE(cb.eq(c + b));
    EXPECT_TRUE(ab.eq(b + a));
    EXPECT_TRUE(ac.eq(c + a));
    EXPECT_TRUE(bd.eq(d + b));
    EXPECT_TRUE(cb.eq(b + c));
}


TEST_F(MatrizTest, resta) {
    matriz<__ESTR__> ab = {
        {0, 2, 3, 4},
        {4, -1, 0, 1},
        {1, 1, 0, 1},
        {1, 2, 3, 6}
    };
    matriz<__ESTR__> ac = {
        {0, -23, 0, -5},
        {0, 0, -7, 0},
        {0, -5, -5, 0},
        {0, 0, 3, 7}
    };
    matriz<__ESTR__> bd = {
        {1, 0, 0, -4},
        {-1, 1, 0, 0},
        {0, 0, -2, 0},
        {0, -2, 0, 1}
    };
    matriz<__ESTR__> cb = {
        {0, 25, 3, 9},
        {4, -1, 7, 1},
        {1, 6, 5, 1},
        {1, 2, 0, -1}
    };
    EXPECT_TRUE(ab.eq(a - b));
    EXPECT_TRUE(ac.eq(a - c));
    EXPECT_TRUE(bd.eq(b - d));
    EXPECT_TRUE(cb.eq(c - b));
    EXPECT_TRUE(ab.eq(-1 * (b - a)));
    EXPECT_TRUE(ac.eq(-1 * (c - a)));
    EXPECT_TRUE(bd.eq(-1 * (d - b)));
    EXPECT_TRUE(cb.eq(-1 * (b - c)));
}


TEST_F(MatrizTest, productoEscalar) {
    matriz<__ESTR__> a5 = {
        {5, 10, 15, 20},
        {20, 0, 0, 5},
        {5, 5, 5, 5},
        {5, 10, 15, 35}
    };
    matriz<__ESTR__> b13 = {
        {13, 0, 0, 0},
        {0, 13, 0, 0},
        {0, 0, 13, 0},
        {0, 0, 0, 13}
    };
    matriz<__ESTR__> c0 = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    matriz<__ESTR__> d1 = {
        {0, 0, 0, 4},
        {1, 0, 0, 0},
        {0, 0, 3, 0},
        {0, 2, 0, 0}
    };
    EXPECT_TRUE(a5.eq(a * 5));
    EXPECT_TRUE(b13.eq(b * 13));
    EXPECT_TRUE(c0.eq(c * 0));
    EXPECT_TRUE(d1.eq(d * 1));
    EXPECT_TRUE(a5.eq(5 * a));
    EXPECT_TRUE(b13.eq(13 * b));
    EXPECT_TRUE(c0.eq(0 * c));
    EXPECT_TRUE(d1.eq(1 * d));
};


TEST_F(MatrizTest, producto) {
    matriz<__ESTR__> aa = {
        {16, 13, 18, 37},
        {5, 10, 15, 23},
        {7, 5, 7, 13},
        {19, 19, 27, 58}
    };
    matriz<__ESTR__> ac = {
        {16, 51, 35, 14},
        {5, 102, 12, 36},
        {7, 33, 16, 11},
        {19, 57, 35, 14}
    };
    matriz<__ESTR__> ca = {
        {113, 23, 33, 95},
        {12, 17, 22, 30},
        {32, 10, 12, 23},
        {9, 2, 3, 6}
    };
    matriz<__ESTR__> cd = {
        {25, 18, 9, 4},
        {0, 2, 21, 16},
        {6, 2, 18, 4},
        {2, 0, 0, 4}
    };
    matriz<__ESTR__> abcd = {
        {51, 28, 105, 64},
        {102, 72, 36, 20},
        {33, 22, 48, 28},
        {57, 28, 105, 76}
    };
    EXPECT_TRUE(a.eq(a * b));
    EXPECT_TRUE(a.eq(b * a));
    EXPECT_TRUE(aa.eq(a * a));
    EXPECT_TRUE(ac.eq(a * c));
    EXPECT_TRUE(ca.eq(c * a));
    EXPECT_TRUE(cd.eq(c * d));
    EXPECT_TRUE(abcd.eq(a * b * c * d));
}


TEST_F(MatrizTest, print) {
    ostringstream stream;
    stream << a;
    string a_os = stream.str();
    EXPECT_EQ(a_os, "1, 2, 3, 4\n4, 0, 0, 1\n1, 1, 1, 1\n1, 2, 3, 7\n");

    stream = ostringstream();
    stream << b;
    string b_os = stream.str();
    EXPECT_EQ(b_os, "1, 0, 0, 0\n0, 1, 0, 0\n0, 0, 1, 0\n0, 0, 0, 1\n");
}


TEST_F(MatrizTest, gauss_elim){
    matriz<__ESTR__> input1 = {
        {1, 0, 0, 3},
        {0, 1, 0, 6},
        {0, 0, 1, 12}
    };
    matriz<__ESTR__> output1 = {
        {1, 0, 0, 3},
        {0, 1, 0, 6},
        {0, 0, 1, 12}
    };
    matriz<__ESTR__> input2 = {
        {1, 0, 0, 3},
        {2, 1, 0, 6},
        {1, 0, 1, 12}
    };
    matriz<__ESTR__> output2 = {
        {1, 0, 0, 3},
        {0, 1, 0, 0},
        {0, 0, 1, 9}
    };
    matriz<__ESTR__> input3 = {
        {1, 2, 3, 4, 2},
        {1, 4, 9, 16, 10},
        {1, 8, 27, 64, 44},
        {1, 16, 81, 256, 190}
    };
    matriz<__ESTR__> output3 = {
        {1, 2, 3, 4, 2},
        {0, 2, 6, 12, 8},
        {0, 0, 6, 24, 18},
        {0, 0, 0, 24, 24}
    };
    EXPECT_TRUE(output1.eq(input1.gauss_elim()));
    EXPECT_TRUE(output2.eq(input2.gauss_elim()));
    EXPECT_TRUE(output3.eq(input3.gauss_elim()));
}
