/* Snippet Header */

#include <bits/stdc++.h>
using i64 = long long;
#define MOD 998244353

/* Snippet BEGIN */

template <typename T> constexpr T power(T a, i64 b)
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

template <typename M> class MInt
{
  public:
    constexpr MInt() : x{0} {}
    constexpr MInt(i64 v)
    {
        if (v < 0)
            v = v % MOD + MOD;
        if (v >= MOD)
            v %= MOD;
        x = v;
    }

    typedef M ModType;
    static inline constexpr i64 P() { return M::P(); }

    constexpr i64 val() const { return x; }
    constexpr MInt operator-() const
    {
        MInt res;
        res.x = P() - x;
        return res;
    }
    constexpr MInt inv() const
    {
        MInt ret = power(*this, P() - 2);
#ifdef DBG
        assert(ret * *this == 1);
#endif
        return ret;
    }
    constexpr MInt &operator*=(MInt rhs) &
    {
        if (P() <= INT_MAX) {
            x = x * rhs.x % int(P());
        } else {
            x = mul(x, rhs.x, P());
        }
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) &
    {
        x = x + rhs.x;
        if (x >= P()) {
            x -= P();
        }
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) &
    {
        x = x - rhs.x;
        if (x < 0) {
            x += P();
        }
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
    friend std::ostream &operator<<(std::ostream &os, MInt x)
    {
        return os << x.val();
    }
  private:
    i64 x;
};

// TODO
struct barrett_reduction
{
    unsigned mod;
    uint64_t div;

    barrett_reduction(unsigned m) : mod(m), div(-1LLU / m) {}

    unsigned operator()(uint64_t a) const
    {
#ifdef __SIZEOF_INT128__
        uint64_t q = uint64_t(__uint128_t(div) * a >> 64);
        uint64_t r = a - q * mod;
        return unsigned(r < mod ? r : r - mod);
#endif
        return unsigned(a % mod);
    }
};

class StaticMod
{
  public:
    constexpr static i64 P() { return MOD; }
};

class DynamicMod
{
  public:
    static i64 P() { return p; }
    static void set(i64 x) { p = x; }

  private:
    // https://stackoverflow.com/questions/9110487/undefined-reference-to-a-static-member
    inline static i64 p;
};

using Z = MInt<StaticMod>;
using Zp = MInt<DynamicMod>;

template <typename F> struct Comb
{
    int n;
    std::vector<F> _fac;
    std::vector<F> _invfac;
    std::vector<F> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() { init(n); }

    void init(int m)
    {
        m = std::min<i64>(m, F::P() - 1);
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

    F fac(int m)
    {
        if (m > n)
            init(2 * m);
        return _fac[m];
    }
    F invfac(int m)
    {
        if (m > n)
            init(2 * m);
        return _invfac[m];
    }
    F inv(int m)
    {
        if (m > n)
            init(2 * m);
        return _inv[m];
    }
    F binom(int n, int m)
    {
        if (n < m || m < 0)
            return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
};

void modint_example()
{
    Comb<Z> comb;

    assert(comb.binom(3, 2) == 3);

    Z x = 5;
    assert(1 == x / 5);
    assert(1 == x * comb.inv(5));

    printf("%lld\n", (x / 2).val());
}

/* Snippet END */
