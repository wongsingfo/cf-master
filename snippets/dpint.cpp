/* Snippet Header */

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

/* Snippet BEGIN */

template <typename T, T Invalid = std::numeric_limits<T>::min()> struct DpInt
{
    T x;
    constexpr DpInt() : x{Invalid} {}
    constexpr DpInt(T x) : x{x} {}

    constexpr i64 val() const
    {
        assert(!invalid());
        return x;
    }

    constexpr bool invalid() const { return x == Invalid; }

    constexpr DpInt &operator*=(DpInt rhs) &
    {
        if (invalid() || rhs.invalid())
            x = Invalid;
        else
            x *= rhs.x;
        return *this;
    }
    constexpr DpInt &operator+=(DpInt rhs) &
    {
        if (invalid() || rhs.invalid())
            x = Invalid;
        else
            x += rhs.x;
        return *this;
    }
    constexpr DpInt &operator-=(DpInt rhs) &
    {
        if (invalid() || rhs.invalid())
            x = Invalid;
        else
            x -= rhs.x;
        return *this;
    }
    constexpr DpInt &operator/=(DpInt rhs) &
    {
        if (invalid() || rhs.invalid())
            x = Invalid;
        else {
            assert(x % rhs.x == 0);
            x /= rhs.x;
        }
        return *this;
    }
    constexpr void max(DpInt rhs) &
    {
        if (rhs.invalid())
            return;
        if (invalid()) {
            x = rhs.x;
            return;
        }
        x = std::max(x, rhs.x);
    }
    constexpr void min(DpInt rhs) &
    {
        if (rhs.invalid())
            return;
        if (invalid()) {
            x = rhs.x;
            return;
        }
        x = std::min(x, rhs.x);
    }
    friend constexpr DpInt operator*(DpInt lhs, DpInt rhs)
    {
        DpInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr DpInt operator+(DpInt lhs, DpInt rhs)
    {
        DpInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr DpInt operator-(DpInt lhs, DpInt rhs)
    {
        DpInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr DpInt operator/(DpInt lhs, DpInt rhs)
    {
        DpInt res = lhs;
        res /= rhs;
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, DpInt x)
    {
        if (x.invalid()) {
            return os << "X";
        }
        return os << x.val();
    }
};

using DInt = DpInt<int>;
using LInt = DpInt<i64>;

/* Snippet END */
