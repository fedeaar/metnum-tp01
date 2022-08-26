#include "gtest-1.8.1/gtest.h"
#include "../src/Matriz.h"


class MatrizTest : public testing::Test {
protected:
    Matriz<4, 4, int> a, b, c, d;

    void SetUp() override {
        int _a[4][4] = {{1, 2, 3, 4},
                        {4, 0, 0, 1},
                        {1, 1, 1, 1},
                        {1, 2, 3, 7}};

        int _b[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};

        int _c[4][4] = {{1, 25, 3, 9},
                        {4, 0, 7, 1},
                        {1, 6, 6, 1},
                        {1, 2, 0, 0}};

        int _d[4][4] = {{0, 0, 0, 4},
                        {1, 0, 0, 0},
                        {0, 0, 3, 0},
                        {0, 2, 0, 0}};

        a = Matriz<4, 4, int>(_a);
        b = Matriz<4, 4, int>(_b);
        c = Matriz<4, 4, int>(_c);
        d = Matriz<4, 4, int>(_d);
    }
};

TEST_F(MatrizTest, init) {
    std::cout << 1;
    std::cout << a;
    EXPECT_TRUE(true);
}


