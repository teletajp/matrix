#include <iostream>
#include <assert.h>
#include "version.h"
#include "matrix.h"

void test()
{
    Matrix<int, -1> matrix; // бесконечная матрица int заполнена значениями -1
    for (auto c : matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);
    for (auto c : matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    //test();
    Matrix<int, 0> matrix;
    for (int i = 0; i < 10; i++)
    {
        matrix[i][i] = i;
        matrix[9 - i][i] = 9 - i;
    }

    for (int x = 1; x <= 8; x++)
    {
        for (int y = 1; y <= 8; y++)
            std::cout << matrix[x][y] << ' ';
        std::cout << std::endl;
    }

    std::cout << matrix.size() << std::endl;

    for (auto c : matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
    return 0;
}
