/* Snippet Header */

#include <bits/stdc++.h>
using i64 = long long;
#define MOD 998244353

/* Snippet BEGIN */

template <class T> constexpr T power(T a, i64 b)
{
    T res{1};
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p)
{
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template <i64 P> struct MInt
{
    i64 x;
    constexpr MInt() : x{0} {}
    constexpr MInt(i64 x) : x{norm(x % P)} {}

    constexpr i64 norm(i64 x) const
    {
        if (x < 0) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    constexpr i64 val() const { return x; }
    constexpr MInt operator-() const
    {
        MInt res;
        res.x = norm(P - x);
        return res;
    }
    constexpr MInt inv() const { return power(*this, P - 2); }
    constexpr MInt &operator*=(MInt rhs) &
    {
        if constexpr (P < (1ULL << 31)) {
            x = x * rhs.x % int(P);
        } else {
            x = mul(x, rhs.x, P);
        }
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & { return *this *= rhs.inv(); }
    friend constexpr MInt operator*(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs)
    {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs)
    {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs)
    {
        return lhs.val() < rhs.val();
    }
};

constexpr int P = MOD;
using Z = MInt<P>;

struct Comb
{
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() { init(n); }

    void init(int m)
    {
        m = std::min<i64>(m, P - 1);
        if (m <= n)
            return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m)
    {
        if (m > n)
            init(2 * m);
        return _fac[m];
    }
    Z invfac(int m)
    {
        if (m > n)
            init(2 * m);
        return _invfac[m];
    }
    Z inv(int m)
    {
        if (m > n)
            init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m)
    {
        if (n < m || m < 0)
            return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

void modint_example()
{
    int n = 6;
    Comb comb(n);

    assert(comb.binom(3, 2) == 3);

    Z x = 5;
    assert(1 == x / 5);
    assert(1 == x * comb.inv(5));

    printf("%lld\n", (x / 2).val());
}

/* Snippet END */
