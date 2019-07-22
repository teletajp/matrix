#include <iostream>
#include "version.h"
#include "matrix.h"
int main(int argc, char const *argv[])
{
    Matrix<int, -1> matrix; // бесконечная матрица int заполнена значениями -1
    //assert(matrix.size() == 0); // все ячейки свободны
    //auto a = matrix[0][0];
    //assert(a == -1);
    //assert(matrix.size() == 0);
    matrix[100][100] = 314;
    //assert(matrix[100][100] == 314);
    //assert(matrix.size() == 1);
    return 0;
}
