#pragma once
#include <map>
#include <limits>

template<class T, T ZERO_VAL>
class Matrix
{
private:
    struct Cell;
    using column_t = std::map<uint64_t, Cell>;
    using column_ptr_t = column_t*;

    struct Cell
    {
        uint64_t x_;
        uint64_t y_;
        T value_;
        column_ptr_t p_column_;

        Cell(uint64_t x, uint64_t y):x_(x), y_(y), value_(ZERO_VAL){};

        Cell& operator=(const T& value)
        {
            value_ = value;
            if(value_ == ZERO_VAL)
            {
                auto p_column = p_column_;
                p_column->erase(y_);
                if(p_column->empty())
                    p_column->p_matrix_->erase(x_);
            }
        }
    };
    struct Column;
    using matrix_t = std::map<uint64_t, Column>;
    using matrix_ptr_t = matrix_t*;
    
    struct Column
    {
        const uint64_t x_;
        matrix_ptr_t p_matrix_;
        column_t column_;
        Cell& operator[](const uint64_t y)
        {
            return *(column_.emplace({y, Cell(x_,y)}).first);
        }
        Column(uint64_t x, matrix_ptr_t p_matrix):x_(x),p_matrix_(p_matrix){};
    };

    matrix_t matrix_; 
public:
    Matrix(/* args */){};
    ~Matrix(){};
    Column& operator[](uint64_t x)
    {
        return matrix_.insert(std::make_pair(x, Column(x, &matrix_)).first.second;
    }
};

