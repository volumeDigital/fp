#pragma once
#include <cstdint>
#include <cmath>
#include <utility>

namespace fp {

// TODO constexpr noexcept
template <int P>
class fp32
{

public:
    static fp32 min() {
        return make_fp32(INT32_MIN);
    }
    static fp32 max() {
        return make_fp32(INT32_MAX);
    }
    static fp32 epsilon() {
        return make_fp32(1);
    }

    fp32(const fp32& value)
        : m_data(value.m_data) {}
    fp32(int value)
        : m_data(value << P) {}
    fp32(float value)
        : m_data(value * (1<<P)) {}
    fp32(double value)
        : m_data(value * (1<<P)) {}

    fp32& operator=(const fp32& value) {
        m_data = value.m_data;
        return *this;
    }
    fp32& operator=(int value) {
        m_data = value << P;
        return *this;
    }
    fp32& operator=(float value) {
        m_data = value * (1<<P);
        return *this;
    }
    fp32& operator=(double value) {
        m_data = value * (1<<P);
        return *this;
    }

    int as_int() const {
        return m_data >> P;
    }

    float as_float() const {
        return ((float)m_data) / (1<<P);
    }

    double as_double() const {
        return ((double)m_data) / (1<<P);
    }

    typedef std::pair<int32_t,uint32_t> num_denom_t;
    num_denom_t as_num_denom() const {
        return num_denom_t(m_data,1<<P);
    }

    // unary ops
    fp32 operator+() {
        return *this;
    }
    fp32 operator-() {
        return make_fp32(-m_data);
    }

    // binary ops
    fp32 operator+(const fp32& arg) const {
        return make_fp32(m_data + arg.m_data);
    }
    fp32 operator-(const fp32& arg) const {
        return make_fp32(m_data - arg.m_data);
    }
    fp32 operator*(const fp32& arg) const {
        return make_fp32(((int64_t)m_data * arg.m_data) >> P);
    }
    fp32 operator/(const fp32& arg) const {
        return make_fp32((((int64_t)m_data)<<P) / arg.m_data);
    }
    fp32 operator%(const fp32& arg) const {
        return make_fp32(m_data % arg.m_data);
    }

    // pre-increment
    fp32& operator++() {
        m_data += 1<<P;
        return *this;
    }
    fp32& operator--() {
        m_data -= 1<<P;
        return *this;
    }
    // post-increment
    fp32 operator++(int) {
        fp32 result(*this);
        ++(*this);
        return result;
    }
    fp32 operator--(int) {
        fp32 result(*this);
        --(*this);
        return result;
    }

    // assignment ops
    fp32& operator+=(const fp32& arg) {
        *this = *this + arg;
        return *this;
    }
    fp32& operator-=(const fp32& arg) {
        *this = *this - arg;
        return *this;
    }
    fp32& operator*=(const fp32& arg) {
        *this = *this * arg;
        return *this;
    }
    fp32& operator/=(const fp32& arg) {
        *this = *this / arg;
        return *this;
    }
    // Fused Multiply and Add is a type of assignment operator.
    fp32& fma(const fp32& arg0, const fp32& arg1) {
        *this += arg0 * arg1;
        return *this;
    }

    // Comparison ops
    bool operator==(const fp32& rhs) const {
        return m_data == rhs.m_data;
    }
    bool operator!=(const fp32& rhs) const {
        return m_data != rhs.m_data;
    }
    bool operator<=(const fp32& rhs) const {
        return m_data <= rhs.m_data;
    }
    bool operator<(const fp32& rhs) const {
        return m_data < rhs.m_data;
    }
    bool operator>=(const fp32& rhs) const {
        return m_data >= rhs.m_data;
    }
    bool operator>(const fp32& rhs) const {
        return m_data > rhs.m_data;
    }

    fp32 sqrt() const {
        fp32 result(std::sqrt(as_double()));
        return result;
    }

private:
    fp32() {}
    static fp32 make_fp32(int32_t data) {
        fp32 result;
        result.m_data = data;
        return result;
    }
private:
    int32_t m_data;
};


// Non-member comparison operators
template<typename T, int N>
bool operator==(T lhs, const fp32<N>& rhs) {
    return fp32<N>(lhs) == rhs;
}
template<typename T, int N>
bool operator!=(T lhs, const fp32<N>& rhs) {
    return fp32<N>(lhs) != rhs;
}
template<typename T, int N>
bool operator<(T lhs, const fp32<N>& rhs) {
    return fp32<N>(lhs) < rhs;
}
template<typename T, int N>
bool operator<=(T lhs, const fp32<N>& rhs) {
    return fp32<N>(lhs) <= rhs;
}
template<typename T, int N>
bool operator>(T lhs, const fp32<N>& rhs) {
    return fp32<N>(lhs) > rhs;
}
template<typename T, int N>
bool operator>=(T lhs, const fp32<N>& rhs) {
    return fp32<N>(lhs) >= rhs;
}

// Non-member arithmetic operators
template<typename T, int P>
fp32<P> operator+(T lhs, const fp32<P>& rhs) {
    return fp32<P>(lhs) + rhs;
}
template<typename T, int P>
fp32<P> operator-(T lhs, const fp32<P>& rhs) {
    return fp32<P>(lhs) - rhs;
}
template<typename T, int P>
fp32<P> operator*(T lhs, const fp32<P>& rhs) {
    return fp32<P>(lhs) * rhs;
}
template<typename T, int P>
fp32<P> operator/(T lhs, const fp32<P>& rhs) {
    return fp32<P>(lhs) / rhs;
}
template<typename T, int P>
fp32<P> operator%(T lhs, const fp32<P>& rhs) {
    return fp32<P>(lhs) % rhs;
}

template<int P>
fp32<P> sqrt(const fp32<P>& arg) {
    return arg.sqrt();
}

} // namespace fp

