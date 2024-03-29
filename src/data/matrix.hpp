#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <numeric>


namespace data {
    template <typename TYPE, size_t ROWS, size_t COLS>
    class Matrix : public std::array<TYPE, ROWS * COLS> {
    private:
        template <typename Function>
        auto arithmetic_operation(const Matrix<TYPE, ROWS, COLS>& other, Function op) const {
            Matrix<TYPE, ROWS, COLS> result;
            std::transform(this->begin(), this->end(), other.begin(), result.begin(), op);
            return result;
        }

        template <typename Function>
        auto arithmetic_operation(const TYPE val, Function op) const {
            Matrix<TYPE, ROWS, COLS> result;
            result.fill(val);
            std::transform(this->begin(), this->end(), result.begin(), result.begin(), op);
            return result;
        }

        static auto index(size_t i, size_t j) {
            return i * COLS + j;
        }

    public:
        static constexpr size_t SIZE = ROWS * COLS;

        Matrix() : std::array<TYPE, SIZE>() {
            static_assert(SIZE > 0);
        };

        template <typename... Args>
        Matrix(Args... args) {
            static_assert(SIZE > 0);
            static_assert(sizeof...(Args) == SIZE, "Number of arguments must match matrix size.");

            auto it_this = this->begin();
            for (auto arg : {static_cast<TYPE>(args)...}) {
                *it_this++ = arg;
            }
        }

        auto operator()(size_t i, size_t j) const {
            return (*this)[index(i, j)];
        }

        auto& operator()(size_t i, size_t j) {
            return (*this)[index(i, j)];
        }

        void operator=(const Matrix<TYPE, ROWS, COLS>& other) {
            std::copy(other.begin(), other.end(), this->begin());
        }

        /*/////////////////////////////////////////////
            const matrix-matrix arithmetic overloads
        *//////////////////////////////////////////////

        auto operator+(const Matrix<TYPE, ROWS, COLS>& other) const {
            return arithmetic_operation(other, std::plus<TYPE>());
        }
        auto operator-(const Matrix<TYPE, ROWS, COLS>& other) const {
            return arithmetic_operation(other, std::minus<TYPE>());
        }

        auto operator*(const Matrix<TYPE, ROWS, COLS>& other) const {
            return arithmetic_operation(other, std::multiplies<TYPE>());
        }

        auto operator/(const Matrix<TYPE, ROWS, COLS>& other) const {
            return arithmetic_operation(other, std::divides<TYPE>());
        }

        /*//////////////////////////////////////////////
            const matrix-scalar arithmetic overloads
        *//////////////////////////////////////////////
        auto operator+(const TYPE val) const {
            return arithmetic_operation(val, std::plus<TYPE>());
        }

        auto operator-(const TYPE val) const {
            return arithmetic_operation(val, std::minus<TYPE>());
        }

        auto operator*(const TYPE val) const {
            return arithmetic_operation(val, std::multiplies<TYPE>());
        }

        auto operator/(const TYPE val) const {
            return arithmetic_operation(val, std::divides<TYPE>());
        }

        /*/////////////////////////////////////////////
            matrix-matrix arithmetic assignment overloads
        *//////////////////////////////////////////////
        auto& operator+=(const Matrix<TYPE, ROWS, COLS>& other) {
            *this = *this + other;
            return *this;
        }

        auto& operator-=(const Matrix<TYPE, ROWS, COLS>& other) {
            *this = *this - other;
            return *this;
        }

        auto& operator*=(const Matrix<TYPE, ROWS, COLS>& other) {
            *this = *this * other;
            return *this;
        }

        auto& operator/=(const Matrix<TYPE, ROWS, COLS>& other) {
            *this = *this / other;
            return *this;
        }

        /*//////////////////////////////////////////////
            matrix-scalar arithmetic assignment overloads
        *//////////////////////////////////////////////

        auto& operator+=(const TYPE val) {
            *this = *this + val;
            return *this;
        }

        auto& operator-=(const TYPE val) {
            *this = *this - val;
            return *this;
        }

        auto& operator*=(const TYPE val) {
            *this = *this * val;
            return *this;
        }

        auto& operator/=(const TYPE val) {
            *this = *this / val;
            return *this;
        }

        /*//////////////////////////////////////////////
                    matrix operations
        *//////////////////////////////////////////////

        auto transposed() const {
            Matrix<TYPE, COLS, ROWS> result;

            for (size_t i = 0; i < ROWS; ++i) {
                for (size_t j = 0; j < COLS; ++j) {
                    result(j, i) = (*this)(i, j);
                }
            }

            return result;
        }

        auto& transpose() {
            *this = transposed();
            return *this;
        }

        /*/////////////////////////
            stdout overloads
        */////////////////////////
        friend inline std::ostream& operator<<(std::ostream& os, const Matrix<TYPE, ROWS, COLS>& mat) {
            constexpr int fieldWidth = 8; // Set the field width for setw
            constexpr int precision  = 4; // Set the precision for setprecision
            os << "[";
            for (size_t i = 0; i < ROWS; ++i) {
                for (size_t j = 0; j < COLS; ++j) {
                    if (mat(i, j) == 0) {
                        os << "\033[1;31m"; // ANSI escape code for red text
                    } else {
                        os << "\033[1;32m"; // ANSI escape code for green text
                    }
                    os << std::setw(fieldWidth) << std::setprecision(precision) << std::fixed << mat(i, j);
                    os << "\033[0m"; // Reset color
                    if (j != COLS - 1) {
                        os << ", ";
                    }
                }
                if (i != ROWS - 1) {
                    os << ",\n ";
                }
            }
            os << "]";
            return os;
        }

        /*//////////////////////////////////////////////
                    static functions
        *//////////////////////////////////////////////

        static constexpr auto identity() {
            static_assert(ROWS == COLS);

            Matrix<TYPE, ROWS, COLS> result;

            for (size_t i = 0; i < ROWS; ++i) {
                result(i, i) = 1;
            }

            return result;
        }
    };

    using Matrix3f = Matrix<float, 3, 3>;
    using Matrix3i = Matrix<int, 3, 3>;

    template <size_t N>
    using MatrixNf = Matrix<float, N, N>;

    template <size_t N>
    using MatrixNi = Matrix<int, N, N>;
} // namespace data
