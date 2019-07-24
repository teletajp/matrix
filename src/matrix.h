#pragma once
#include <map>
#include <limits>

template<class T, T ZERO_VAL>
class Matrix
{
private:
    struct Cell;
    struct Column;
    using column_t = std::map<uint64_t, Cell>;
    using matrix_t = std::map<uint64_t, Column>;

    struct Cell
    {
        uint64_t x_;
        uint64_t y_;
        T value_;
        uint64_t *matrix_size_;
        Cell(uint64_t x, uint64_t y, uint64_t *matrix_size):x_(x), y_(y), value_(ZERO_VAL), matrix_size_(matrix_size){};

        Cell& operator=(const T& value)
        {
            if (value_ == ZERO_VAL && value != ZERO_VAL)
                if(matrix_size_)(*matrix_size_)++;
            else if(value_ != ZERO_VAL && value == ZERO_VAL)
                    if (matrix_size_)(*matrix_size_)--;
            value_ = value;
            return *this;
        }
        template<class U>
        operator std::tuple<U&, U&, T&>()
        {
            return std::tie((U&)x_, (U&)y_, value_);
        }
        template<class U>
        operator U()
        {
            return static_cast<U>(value_);
        }
        bool operator== (const T& value) const { return value_ == value; };
    };

    struct Column
    {
        Cell zero_cell;
        const uint64_t x_;
        column_t column_;
        uint64_t *matrix_size_;
        Cell& operator[](uint64_t y)
        {
            return column_.insert(std::make_pair(y, Cell(x_,y, matrix_size_))).first->second;
        }

        Column(uint64_t x, uint64_t *matrix_size):zero_cell(0, 0, nullptr), x_(x), matrix_size_(matrix_size){};
        typename column_t::iterator begin() { return column_.begin(); }
        typename column_t::iterator end() { return column_.end(); }
    };

    matrix_t matrix_; 
    uint64_t size_;
public:
    Matrix():size_(0){};
    ~Matrix(){};
    Column& operator[](uint64_t x)
    {
        return matrix_.insert(std::make_pair(x, Column(x, &size_))).first->second;
    };

    uint64_t size() { return size_; };

    class matrix_iterator
    {
        typename matrix_t::iterator mit_;
        typename matrix_t::iterator end_;
        typename column_t::iterator cit_;
    public:
        matrix_iterator() = default;
        matrix_iterator(typename matrix_t::iterator mit, typename matrix_t::iterator end):mit_(mit), end_(end)
        {
            cit_ = mit_ == end_ ? column_t().end() : mit_->second.begin();
        };
        matrix_iterator(const matrix_iterator &rhs) :mit_(rhs.mit_), cit_(rhs.cit_){};
        const matrix_iterator& operator=(const matrix_iterator& rhs) { mit_ = rhs.mit_; end_ = rhs.end_; cit_ = rhs.cit_; return *this; }

        std::tuple<int&, int&,T&> operator*() { return (std::tuple<int&, int&, T&>)cit_->second;}
        Cell* operator->() { return cit_->second; }
        const bool operator!=(const matrix_iterator& rhs)const 
        { 
            if(mit_ != end_)
                return !(mit_ == rhs.mit_ && cit_ == rhs.cit_);
            return mit_ != rhs.mit_;
        }
        matrix_iterator& operator++()
        {
            do
            {
                cit_++;
                if (cit_ == mit_->second.end())
                {
                    mit_++;
                    if (mit_ != end_)
                        cit_ = mit_->second.begin();
                    else
                        break;
                }
            }
            while (cit_->second.value_ == ZERO_VAL);
            return *this;
        };
    };

    using iterator = matrix_iterator;
    iterator begin()
    {
        return iterator(matrix_.begin(), matrix_.end());
    }
    iterator end() { return iterator(matrix_.end(), matrix_.end()); }

};

