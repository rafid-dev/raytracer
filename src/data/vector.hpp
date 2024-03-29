#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <numeric>

namespace data {

    template <typename TYPE, size_t SIZE>
    class Vector : public std::array<TYPE, SIZE> {
    private:
        // Templated arithmetic operation for vector-vector operations
        template <typename Function>
        auto arithmetic_operation(const Vector<TYPE, SIZE>& other, Function op) const {
            Vector<TYPE, SIZE> result;
            std::transform(this->begin(), this->end(), other.begin(), result.begin(), op);
            return result;
        }

        // Templated arithmetic operation for vector-scalar operations
        template <typename Function>
        auto arithmetic_operation(const TYPE val, Function op) const {
            Vector<TYPE, SIZE> result;
            result.fill(val);
            std::transform(this->begin(), this->end(), result.begin(), result.begin(), op);
            return result;
        }

    public:
        Vector() : std::array<TYPE, SIZE>() {
            static_assert(SIZE > 0);
        };

        template <typename... Args>
        Vector(Args... args) {
            static_assert(SIZE > 0);
            static_assert(sizeof...(Args) == SIZE, "Number of arguments must match vector size.");

            auto it_this = this->begin();
            for (auto arg : {static_cast<TYPE>(args)...}) {
                *it_this++ = arg;
            }
        }

        auto operator()(size_t index) const {
            return (*this)[index];
        }

        auto operator()(size_t index) {
            return (*this)[index];
        }

        void operator=(const Vector<TYPE, SIZE>& other) {
            std::copy(other.begin(), other.end(), this->begin());
        }

        /*/////////////////////////////////////////////
            const vector-vector arithmetic overloads
        *//////////////////////////////////////////////

        auto operator+(const Vector<TYPE, SIZE>& other) const {
            return arithmetic_operation(other, std::plus<TYPE>());
        }
        auto operator-(const Vector<TYPE, SIZE>& other) const {
            return arithmetic_operation(other, std::minus<TYPE>());
        }

        auto operator*(const Vector<TYPE, SIZE>& other) const {
            return arithmetic_operation(other, std::multiplies<TYPE>());
        }

        auto operator/(const Vector<TYPE, SIZE>& other) const {
            return arithmetic_operation(other, std::divides<TYPE>());
        }

        /*//////////////////////////////////////////////
            const vector-scalar arithmetic overloads
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

        /*//////////////////////////////////////////////
            vector-vector arithmetic assignment overloads
        *//////////////////////////////////////////////
        auto& operator+=(const Vector<TYPE, SIZE>& other) {
            *this = *this + other;
            
            return *this;
        }

        auto& operator-=(const Vector<TYPE, SIZE>& other) {
            *this = *this - other;
            
            return *this;
        }

        auto& operator*=(const Vector<TYPE, SIZE>& other) {
            *this = *this * other;
            
            return *this;
        }

        auto& operator/=(const Vector<TYPE, SIZE>& other) {
            *this = *this / other;
            
            return *this;
        }

        /*//////////////////////////////////////////////
            vector-scalar arithmetic assignment overloads
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
            vector-vector comparison overloads
        *//////////////////////////////////////////////

        bool operator==(const Vector<TYPE, SIZE>& other) const {
            return std::equal(this->begin(), this->end(), other.begin());
        }

        bool operator!=(const Vector<TYPE, SIZE>& other) const {
            return !(*this == other);
        }

        /*//////////////////////////////////////////////
            vector-scalar comparison overloads
        *//////////////////////////////////////////////

        bool operator==(const TYPE val) const {
            return std::all_of(this->begin(), this->end(), [val](TYPE x) { return x == val; });
        }

        bool operator!=(const TYPE val) const {
            return !(*this == val);
        }

        // Unary negation
        Vector<TYPE, SIZE> operator-() const {
            return *this * -1;
        }

        /*//////////////////////////////////////////////
                    vector operations
        *//////////////////////////////////////////////
        
        TYPE sum() const {
            return std::accumulate(this->begin(), this->end(), 0);
        }

        TYPE dot(const Vector<TYPE, SIZE>& other) const {
            return std::inner_product(this->begin(), this->end(), other.begin(), 0);
        }

        TYPE length() const {
            return std::sqrt(dot(*this));
        }

        auto normalised() const {
            return *this / this->length();
        }

        auto& normalise() {
            *this /= this->length();

            return *this;
        }

        /*/////////////////////////
            stdout overloads
        */////////////////////////
        friend inline std::ostream& operator<<(std::ostream& os, const Vector<TYPE, SIZE>& vec) {
            os << "(";
            for (size_t i = 0; i < SIZE; i++) {
                os << vec[i];
                if (i != SIZE - 1) {
                    os << ", ";
                }
            }
            os << ")";
            return os;
        }
    };

    using Vector3f = Vector<float, 3>;
} // namespace data