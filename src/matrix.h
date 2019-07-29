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
        matrix_t* p_matrix_;
        uint64_t* p_matix_size_;
        Cell(uint64_t x, uint64_t y, matrix_t* p_matrix, uint64_t* p_matix_size): x_(x), y_(y), value_(ZERO_VAL), p_matrix_(p_matrix), p_matix_size_(p_matix_size){};
        Cell& operator=(const Cell& cell) = default;

        Cell& operator=(const T& value)
        {
            if (value_ == ZERO_VAL && value != ZERO_VAL)
            {//fake_value
                Column &col = p_matrix_->emplace(x_, Column(x_, p_matrix_, p_matix_size_)).first->second;
                Cell& cell = col.column_.emplace(y_, Cell(x_, y_, p_matrix_, p_matix_size_)).first->second;
                cell = *this;
                cell.value_ = value;
                (*p_matix_size_)++;
                return cell;
            }
            
            if (value_ != ZERO_VAL)
            {
                if (value == ZERO_VAL)
                {
                    Cell temp = *this;
                    column_t *p_column = &temp.p_matrix_->at(temp.x_).column_;
                    p_column->erase(temp.y_);
                    if (p_column->empty())
                        temp.p_matrix_->erase(temp.x_);
                    (*temp.p_matix_size_)--;
                    temp.value_ = ZERO_VAL;
                    return temp;
                }
                else
                {
                    value_ = value;
                }
            }
            return *this;
        }
        template<class U>
        operator std::tuple<U&, U&, T&>()
        {
            return std::tie((U&)x_, (U&)y_, value_);
        }

        operator T() const
        {
            return value_;
        }
        bool operator== (const T& value) const { return value_ == value; };
    };

    struct Column
    {
        uint64_t x_;
        matrix_t* p_matrix_;
        column_t column_;
        uint64_t* p_matix_size_;
        Cell fake_cell;
        Cell& operator[](uint64_t y)
        {
            auto find_it = column_.find(y);
            if (find_it == column_.end())
            {
                fake_cell.x_ = x_;
                fake_cell.y_ = y;
                return fake_cell;
            }
            return find_it->second;
        }

        Column(uint64_t x, matrix_t* p_matrix, uint64_t* p_matix_size): x_(x), p_matrix_(p_matrix), p_matix_size_(p_matix_size), fake_cell(x_,0,p_matrix_, p_matix_size_){};
        typename column_t::iterator begin() { return column_.begin(); }
        typename column_t::iterator end() { return column_.end(); }
    };

    matrix_t matrix_; 
    uint64_t size_;
    Column fake_column_;
public:
    Matrix() : matrix_(), size_(0), fake_column_(0, &matrix_, &size_) {};
    ~Matrix(){};
    Column& operator[](uint64_t x)
    {
        auto find_it = matrix_.find(x);
        if (find_it == matrix_.end())
        {
            fake_column_.x_ = x;
            return fake_column_;
        }
        return find_it->second;
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
            if (mit_ != end_)
            {
                cit_++;
                if (cit_ == mit_->second.end())
                {
                    mit_++;
                    if (mit_ != end_)
                        cit_ = mit_->second.begin();
                }
            }
            return *this;
        }
    };

    using iterator = matrix_iterator;
    iterator begin()
    {
        return iterator(matrix_.begin(), matrix_.end());
    }
    iterator end() { return iterator(matrix_.end(), matrix_.end()); }

};
