// Created at: Wed Jul 31 15:33:30 CST 2024
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

const int MOD = 998244353;

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

dbg_export(Z, val());

/* Snippet END */

int n, x, m;

Z solve()
{
    vector<int> fib = {0, 1, 1};
    for (int i = 3; i <= x; i++) {
        fib.push_back(fib[i - 1] + fib[i - 2]);
    }
    int upper = fib[x] * n;
    dbg(fib[x], upper);
    while (fib.back() <= upper) {
        int last = fib.back();
        int last2 = fib[fib.size() - 2];
        int v = last + last2;
        fib.push_back(v);
    }
    fib.pop_back();
    dbg(fib);

    vector<vector<Z>> dp((size_t)n + 1, vector<Z>(upper + 1, 0));

    // dp[num][sum] -> dp[num+1][sum+value];
    //              -> dp[num+2][sum+value*2];
    //              -> ...
    dp[0][0] = 1;

    for (int i = 1; i <= x; i++) {
        int value = fib[i];
        for (int num = 0; num < n; num++)
            for (int sum = 0; sum <= upper; sum++) {
                auto &f = dp[num][sum];
                // dbg(num, sum, f);
                if (f.val() != 0) {
                    dp[num + 1][sum + value] += f;
                }
            }
        dbg(i, dp);
    }

    Z ret = 0;
    for (int sum = 1; sum <= upper; sum++) {
        int count = 0;

        int num = sum;
        for (int i = fib.size() - 1; i > 0; i--) {
            if (fib[i] <= num) {
                num -= fib[i];
                count += 1;
            }
        }

        assert(num == 0);
        dbg(sum, count);

        if (count == m) {
            ret += dp[n][sum];
        }
    }

    return ret;
}

int main()
{
#ifndef DBG
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif

    cin >> n >> x >> m;

    Z ans = solve();

    cout << ans.val() << endl;

    return 0;
}
