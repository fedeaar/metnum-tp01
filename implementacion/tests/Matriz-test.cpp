#include "gtest-1.8.1/gtest.h"
#include "../src/Matriz.h"


class MatrizTest : public testing::Test {
protected:
    Matriz<4, 4, int> a, b, c, d;
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
    Matriz<4, 4, int> ab = {
        {2, 2, 3, 4},
        {4, 1, 0, 1},
        {1, 1, 2, 1},
        {1, 2, 3, 8}
    };
    Matriz<4, 4, int> ac = {
        {2, 27, 6, 13},
        {8, 0, 7, 2},
        {2, 7, 7, 2},
        {2, 4, 3, 7}
    };
    Matriz<4, 4, int> bd = {
        {1, 0, 0, 4},
        {1, 1, 0, 0},
        {0, 0, 4, 0},
        {0, 2, 0, 1}
    };
    Matriz<4, 4, int> cb = {
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
    Matriz<4, 4, int> ab = {
        {0, 2, 3, 4},
        {4, -1, 0, 1},
        {1, 1, 0, 1},
        {1, 2, 3, 6}
    };
    Matriz<4, 4, int> ac = {
        {0, -23, 0, -5},
        {0, 0, -7, 0},
        {0, -5, -5, 0},
        {0, 0, 3, 7}
    };
    Matriz<4, 4, int> bd = {
        {1, 0, 0, -4},
        {-1, 1, 0, 0},
        {0, 0, -2, 0},
        {0, -2, 0, 1}
    };
    Matriz<4, 4, int> cb = {
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
    Matriz<4, 4, int> a5 = {
        {5, 10, 15, 20},
        {20, 0, 0, 5},
        {5, 5, 5, 5},
        {5, 10, 15, 35}
    };
    Matriz<4, 4, int> b13 = {
        {13, 0, 0, 0},
        {0, 13, 0, 0},
        {0, 0, 13, 0},
        {0, 0, 0, 13}
    };
    Matriz<4, 4, int> c0 = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    Matriz<4, 4, int> d1 = {
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
    Matriz<4, 4, int> aa = {
        {16, 13, 18, 37},
        {5, 10, 15, 23},
        {7, 5, 7, 13},
        {19, 19, 27, 58}
    };
    Matriz<4, 4, int> ac = {
        {16, 51, 35, 14},
        {5, 102, 12, 36},
        {7, 33, 16, 11},
        {19, 57, 35, 14}
    };
    Matriz<4, 4, int> ca = {
        {113, 23, 33, 95},
        {12, 17, 22, 30},
        {32, 10, 12, 23},
        {9, 2, 3, 6}
    };
    Matriz<4, 4, int> cd = {
        {25, 18, 9, 4},
        {0, 2, 21, 16},
        {6, 2, 18, 4},
        {2, 0, 0, 4}
    };
    Matriz<4, 4, int> abcd = {
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


TEST_F(MatrizTest, gauss_swap) {
    Matriz<4, 4, int> a0_2 = {
        {1, 1, 1, 1},
        {4, 0, 0, 1},
        {1, 2, 3, 4},
        {1, 2, 3, 7}
    };
    Matriz<4, 4, int> a0_2y1_0 = {
        {4, 0, 0, 1},
        {1, 1, 1, 1},
        {1, 2, 3, 4},
        {1, 2, 3, 7}
    };
    Matriz<4, 4, int> a0_2y1_0y1_2 = {
        {4, 0, 0, 1},
        {1, 2, 3, 4},
        {1, 1, 1, 1},
        {1, 2, 3, 7}
    };
    Matriz<4, 4, int> a0_2y1_0y1_2y1_0 = {
        {1, 2, 3, 4},
        {4, 0, 0, 1},
        {1, 1, 1, 1},
        {1, 2, 3, 7}
    };
    Matriz<4, 4, int> a0_2c = {
        {3, 2, 1, 4},
        {0, 0, 4, 1},
        {1, 1, 1, 1},
        {3, 2, 1, 7}
    };
    EXPECT_TRUE(a0_2.eq(a.gauss_swap(0, 2)));
    EXPECT_TRUE(a0_2y1_0.eq(a.gauss_swap(0, 2).gauss_swap(1, 0)));
    EXPECT_TRUE(a0_2y1_0y1_2.eq(a.gauss_swap(0, 2).gauss_swap(1, 0).gauss_swap(1, 2)));
    EXPECT_TRUE(a0_2y1_0y1_2y1_0.eq(a.gauss_swap(0, 2).gauss_swap(1, 0).gauss_swap(1, 2).gauss_swap(1, 0)));
    EXPECT_TRUE(a0_2c.eq(a.gauss_swap(0, 2, false)));
    EXPECT_TRUE(a.eq(a.gauss_swap(0, 2, false).gauss_swap(2, 0, false)));
}


TEST_F(MatrizTest, gauss_multiplo) {
    Matriz<4, 4, int> af0p5 = {
        {5, 10, 15, 20},
        {4, 0, 0, 1},
        {1, 1, 1, 1},
        {1, 2, 3, 7}
    };
    Matriz<4, 4, int> af2p0 = {
        {1, 2, 3, 4},
        {4, 0, 0, 1},
        {0, 0, 0, 0},
        {1, 2, 3, 7}
    };
    Matriz<4, 4, int> ac1p5 = {
        {1, 10, 3, 4},
        {4, 0, 0, 1},
        {1, 5, 1, 1},
        {1, 10, 3, 7}
    };
    Matriz<4, 4, int> ac3p0 = {
        {1, 2, 3, 0},
        {4, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 2, 3, 0}
    };
    EXPECT_TRUE(af0p5.eq(a.gauss_mult(0, 5)));
    EXPECT_TRUE(af2p0.eq(a.gauss_mult(2, 0)));
    EXPECT_TRUE(ac1p5.eq(a.gauss_mult(1, 5, false)));
    EXPECT_TRUE(ac3p0.eq(a.gauss_mult(3, 0, false)));
}



TEST_F(MatrizTest, gauss_suma) {
    Matriz<4, 4, int> af1 = {
        {1, 2, 3, 4},
        {0, -8, -12, -15},
        {1, 1, 1, 1},
        {1, 2, 3, 7}
    };
    Matriz<4, 4, int> af2 = {
        {1, 2, 3, 4},
        {0, -8, -12, -15},
        {0, -1, -2, -3},
        {1, 2, 3, 7}
    };
    Matriz<4, 4, int> af3 = {
        {1, 2, 3, 4},
        {0, -8, -12, -15},
        {0, -1, -2, -3},
        {0, 0, 0, 3}
    };
    Matriz<4, 4, int> ac1 = {
        {1, 0, 3, 4},
        {4, -8, 0, 1},
        {1, -1, 1, 1},
        {1, 0, 3, 7}
    };
    Matriz<4, 4, int> ac2 = {
        {1, 0, 0, 4},
        {4, -8, -12, 1},
        {1, -1, -2, 1},
        {1, 0, 0, 7}
    };
    Matriz<4, 4, int> ac3 = {
        {1, 0, 0, 0},
        {4, -8, -12, -15},
        {1, -1, -2, -3},
        {1, 0, 0, 3}
    };
    EXPECT_TRUE(af1.eq(a.gauss_sum(1, 0, -4)));
    EXPECT_TRUE(af2.eq(af1.gauss_sum(2, 0, -1)));
    EXPECT_TRUE(af3.eq(af2.gauss_sum(3, 0, -1)));
    EXPECT_TRUE(ac1.eq(a.gauss_sum(1, 0, -2, false)));
    EXPECT_TRUE(ac2.eq(ac1.gauss_sum(2, 0, -3, false)));
    EXPECT_TRUE(ac3.eq(ac2.gauss_sum(3, 0, -4, false)));
}


TEST_F(MatrizTest, print) {
    std::ostringstream stream;
    stream << a;
    std::string a_os = stream.str();
    EXPECT_EQ(a_os, "\n1, 2, 3, 4\n4, 0, 0, 1\n1, 1, 1, 1\n1, 2, 3, 7\n");

    stream = std::ostringstream();
    stream << b;
    std::string b_os = stream.str();
    EXPECT_EQ(b_os, "\n1, 0, 0, 0\n0, 1, 0, 0\n0, 0, 1, 0\n0, 0, 0, 1\n");
}