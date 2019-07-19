#pragma once
#include <map>
#include <limits>

template<class T, T empty_value>
class InfinityArray
{
private:
    const T empty_value_ = empty_value;
    using ValArray = std::map<std::size_t, T>;
    ValArray values_;
public:
    InfinityArray(/* args */);
    ~InfinityArray();
    T& operator[](std::size_t idx)
    {
        auto it = values_.find(idx);
        if(it != values_.end()) return it->second;
        return values_[indx] = empty_value_;
    }
    T operator[](std::size_t idx)
    {
        auto it = values_.find(idx);
        if(it != values_.end()) return it->second;
        return empty_value_;
    }
};

template<class T, T empty_value>
class matrix
{
public:
    using std::tuple<std::size_t, std::size_t, T> cell_t;
    using std::map<std::size_t, cell_t> row_t;
    struct row
    {
        row_t cells_;
        cell_t& operator[](std::size_t col_idx)
    }
private:
    
    
    using std::map<std::size_t, row_t> table_t;

    std::size_t size_;
    table_t table_;
public:
    matrix(/* args */) = default;
    ~matrix() = default;
    T& operator[](std::size_t col_idx)
    {
        return *(table_.emplace({col_idx, row_t()}).first);
    };

};

