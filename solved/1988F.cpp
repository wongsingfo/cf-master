// #pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const int MAXN = 1024;
const int MOD = 998244353;
int n;
int a[MAXN], b[MAXN], c[MAXN];

// Debugging macro
#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

/* Snippet BEGIN */

template <class T> constexpr T power(T a, ll b)
{
    T res{1};
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr ll mul(ll a, ll b, ll p)
{
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template <ll P> struct MInt
{
    ll x;
    constexpr MInt() : x{0} {}
    constexpr MInt(ll x) : x{norm(x % P)} {}

    constexpr ll norm(ll x) const
    {
        if (x < 0) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    constexpr ll val() const { return x; }
    constexpr MInt operator-() const
    {
        MInt res;
        res.x = norm(P - x);
        return res;
    }
    constexpr MInt inv() const { return power(*this, P - 2); }
    constexpr MInt &operator*=(MInt rhs) &
    {
        if (P < (1ULL << 31)) {
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
        m = std::min<ll>(m, P - 1);
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

/* Snippet END */

// Reset function for global variables
void reset_arrays(int size)
{
    fill(a, a + size, 0);
    fill(b, b + size, 0);
    fill(c, c + size, 0);
}

// Solve function would be implemented here
void solve()
{
    /// dp[ n ][ prefix max ][ ascent ]
    static Z f[2][MAXN][MAXN];

    using pointer = Z(*)[MAXN];
    pointer curr = f[0];
    pointer next = f[1];

    curr[1][0] = 1;
    static Z F[MAXN][MAXN], G[MAXN][MAXN];

    for (int i = 1; i <= n; i++) {
        // dbg("i: %d, cur: %p\n", i, curr);
        // for (int j = 1; j <= n; j++) {
        //     // ascent
        //     for (int k = 0; k <= n; k++) {
        //         F[i][k] += curr[j][k] * a[j];
        //         G[i][k] += curr[j][i - 1 - k] * b[j];
        //     }
        // }
        //
        // if (i == n)
        //     break;

        // prefix max
        for (int j = 1; j <= i; j++) {
            // ascent
            // Z* next_j = nextj];
            // Z* next_j1 = next[j+1];

            for (int k = j - 1; k < i; k++) {
                // G[i][k] += curr[j][i - 1 - k] * b[j];
                Z current = curr[j][k];
                if (current == 0)
                    continue;

                G[i][i - 1 - k] += current * b[j];
                F[i][k] += current * a[j];

                // 1xxxxxxxx
                next[j + 1][k + 1] += current;
                // xxA1Bxxxx  A<B
                next[j][k] += current * k;
                // xxA1Bxxxx  A>B
                next[j][k + 1] += current * (i - k - 1);

                curr[j][k] = 0;
            }

            // fill(&curr[j][0], &curr[j][i], 0);
        }

        swap(curr, next);
        // memset(next, 0, sizeof(f[0]));
    }

    // if (n == 700)
    //     exit(0);
    //
    dbg("F, G calculated\n");

    static Z H[MAXN][MAXN];
    for (int j = 1; j <= n; j++) {
        for (int p = 0; p <= n; p++) {
            Z &value = H[j][p];
            for (int q = 0; q < j && p + q < n; q++) {
                value += G[j][q] * c[p + q];
            }
        }
    }

    Comb comb(n);
    for (int ni = 1; ni <= n; ni++) {
        dbg("ni: %d\n", ni);
        Z ans = 0;
        for (int i = 1; i <= ni; i++) {
            int j = ni - i + 1;

            for (int p = 0; p < i; p++) {
                // for (int q = 0; q < j; q++) {
                //     Z val = comb.binom(ni - 1, i - 1) * F[i][p] * G[j][q] *
                //             c[p + q];
                //     dbg("%d %d %d %d %lld\n", i, j, p, q, val.val());
                //     ans += val;
                // }

                Z val = comb.binom(ni - 1, i - 1) * F[i][p] * H[j][p];
                ans += val;
            }
        }

        printf("%lld ", ans.val());
    }
    printf("\n");
}

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }

    solve();
    return 0;
}
