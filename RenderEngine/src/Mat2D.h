#pragma once
#include <iostream>
#include <vector>

namespace jd
{
    /// <summary>
    /// Interface of 2D matrix
    /// </summary>
    template<typename Node>
    class Mat2D
    {
    public:
        Mat2D();
        Mat2D(const Mat2D& mat2D);
        Mat2D(size_t num_rows, size_t num_columns);
        Mat2D(Mat2D&& mat2D);
        Mat2D& operator=(const Mat2D& mat2D);

        void Reset(size_t num_rows, size_t num_columns); // Make simple .assign();
        void Resize(size_t num_rows, size_t num_columns); // Make simple .resize();
        Node& At(size_t row, size_t column);
        Node At(size_t row, size_t column) const;
        size_t GetNumRows() const;
        size_t GetNumColumns() const;
        Mat2D clone() const;

    private:
        size_t num_rows_;
        size_t num_columns_;

        std::vector<std::vector<Node>> elements_;
    };

    /// <summary>
    /// Realisation of 2D Matrix
    /// </summary>
    /// <typeparam name="Node"></typeparam>

    template<typename Node>
    Mat2D<Node>::Mat2D() : num_rows_(0), num_columns_(0) {}

    template<typename Node>
    Mat2D<Node>::Mat2D(size_t num_rows, size_t num_columns){
        Reset(num_rows, num_columns);
    }

    template<typename Node>
    Mat2D<Node>::Mat2D(Mat2D<Node>&& mat2D)
    {
        num_columns_ = mat2D.num_columns_;
        num_rows_ = mat2D.num_rows_;

        elements_ = std::move(mat2D.elements_);
        mat2D.num_columns_ = 0;
        mat2D.num_rows_ = 0;
    }

    template<typename Node>
    Mat2D<Node>::Mat2D(const Mat2D<Node>& mat2D){
        *this = mat2D;
    }

    template<typename Node>
    Mat2D<Node>& Mat2D<Node>::operator=(const Mat2D<Node>& mat2D)
    {
        Reset(mat2D.num_rows_, mat2D.num_columns_);

        for (size_t i = 0; i < num_rows_; i++) {
            for (size_t j = 0; j < num_columns_; j++) {
                elements_[i][j] = mat2D.At(i, j);
            }
        }

        return *this;
    }

    template<typename Node>
    void Mat2D<Node>::Reset(size_t num_rows, size_t num_columns)
    {
        if (num_rows == 0 || num_columns == 0) {
            num_rows = num_columns = 0;
        }
        else if (num_rows == num_rows_ && num_columns == num_columns_) {
            return;
        }

        num_rows_ = num_rows;
        num_columns_ = num_columns;
        elements_.assign(num_rows, std::vector<Node>(num_columns, Node{}));
    }

    template<typename Node>
    void Mat2D<Node>::Resize(size_t num_rows, size_t num_columns)
    {
        if (num_rows == 0 || num_columns == 0) {
            num_rows = num_columns = 0;
        }

        if (num_rows > num_rows_) {
            elements_.push_back(std::vector<Node>(num_columns - 1, Node{}));
        }

        while (num_rows < num_rows_)
        {
            elements_.pop_back();
            num_rows_--;
        }

        for (auto& vec : elements_) {
            vec.resize(num_columns, Node{});
        }

        num_rows_ = num_rows;
        num_columns_ = num_columns;
    }

    template<typename Node>
    Node& Mat2D<Node>::At(size_t row, size_t column) {
        return elements_.at(row).at(column);
    }

    template<typename Node>
    Node Mat2D<Node>::At(size_t row, size_t column) const {
        return elements_.at(row).at(column);
    }

    template<typename Node>
    size_t Mat2D<Node>::GetNumRows() const {
        return num_rows_;
    }

    template<typename Node>
    size_t Mat2D<Node>::GetNumColumns() const {
        return num_columns_;
    }

    template<typename Node>
    Mat2D<Node> Mat2D<Node>::clone() const
    {
        Mat2D<Node> result(num_rows_, num_columns_);

        for (size_t i = 0; i < num_rows_; i++) {
            for (size_t j = 0; j < num_columns_; j++) {
                result.At(i, j) = elements_.at(i).at(j);
            }
        }

        return result;
    }

    template<typename Node>
    bool operator==(const Mat2D<Node>& one, const Mat2D<Node>& two)
    {
        if (one.GetNumRows() != two.GetNumRows())
            return false;


        if (one.GetNumColumns() != two.GetNumColumns())
            return false;


        for (size_t i = 0; i < one.GetNumRows(); i++)
        {
            for (size_t j = 0; j < one.GetNumColumns(); j++)
            {
                if (one.At(i, j) != two.At(i, j))
                    return false;
            }
        }

        return true;
    }

}