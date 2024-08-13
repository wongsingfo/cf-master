#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

i64 n, m, l, f;

/* Snippet Header */
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

/* Snippet BEGIN */
class NumberTheory
{
  public:
    NumberTheory(int n) : n(n), min_divisor(n + 1, 0) { init(); }

    vector<int> factorize(int x)
    {
        vector<int> ret;
        while (x != 1) {
            int xp = min_divisor[x];
            ret.push_back(min_divisor[x]);
            while (x % xp == 0)
                x /= xp;
        }
        return ret;
    }

    vector<int> &all_primes() { return primes; }

    bool is_prime(int n) { return min_divisor[n] == n; }

    // Returns x^(-1) (mod m)
  private:
    int n;
    vector<int> min_divisor;
    vector<int> primes;

    void init()
    {
        for (int i = 2; i <= n; i++) {
            if (min_divisor[i] == 0) {
                min_divisor[i] = i;
                primes.push_back(i);
            }
            for (int j : primes) {
                if (i * j > n)
                    break;
                min_divisor[i * j] = j;
                if (i % j == 0) {
                    break;
                } else {
                }
            }
        }
    }

    static int pow(int a, int n, int mod)
    {
        int res = 1;
        while (n) {
            if (n & 1) {
                res = (i64)res * a % mod;
            }
            a = (i64)a * a % mod;
            n >>= 1;
        }
        return res;
    }
};

// Return [ x, y, d ]
// a * x + b * y = d = gcd(a, b)
//
// All solution x' and y':
//   x' = x + k * (b / d)
//   y' = y - k * (a / d)
tuple<i64, i64, i64> extended_gcd(i64 a, i64 b)
{
    if (b == 0)
        return {1, 0, a};
    auto [x, y, d] = extended_gcd(b, a % b);
    return {y, x - a / b * y, d};
}

// [Tutorial] Chinese Remainder Theorem
// https://codeforces.com/blog/entry/61290
//    x == a1 (mod n1)
//    x == a2 (mod n2)
// Return [ ret, lcm(n1, n2) ]
// Solution:
//    x == ret (mod lcm(n1, n2))
//    0 <= ret < lcm(n1, n2)
optional<tuple<i64, i64>> chinese_remainder(i64 a1, i64 n1, i64 a2, i64 n2)
{
    // x = k1 * n1 + a1 = k2 * n2 + a2
    // n1 * (-k1) + n2 * k2 = a1 - a2
    auto [k1, k2, d] = extended_gcd(n1, n2);
    k1 = -k1;

#ifdef DBG
    assert(n1 * (-k1) + n2 * k2 == d);
#endif
    if ((a1 - a2) % d != 0) {
        return nullopt;
    }
    i64 scaled = (a1 - a2) / d;
    i64 n2_ = n2 / d;
    i64 lcm = n1 * n2_;

    // x = (a1 + k1 * n1 % lcm) % lcm
    // Note that k1 * n1 overflows (because k1~1e18, n1~1e9)
    //
    // Note that X * n1 % lcm
    //         = X * n1 % (n1 * n2 / d)  % lcm
    //         = X * (n2 / d) * n1       % lcm   <-- avoid overflow
    i64 x = (a1 + k1 % n2_ * scaled % n2_ * n1 % lcm) % lcm;
    if (x < lcm)
        x += lcm;

    return {{x, lcm}};
}

// https://stackoverflow.com/questions/63436490/divide-integers-with-floor-ceil-and-outwards-rounding-modes-in-c

i64 floor_div(i64 a, i64 b)
{
    // auto res = lldiv(a, b);
    i64 d = a / b;
    i64 r = a % b;
    bool quotientNegative = (b < 0) != (a < 0);
    return d - (r != 0 && quotientNegative);
}

i64 ceil_div(i64 a, i64 b)
{
    i64 d = a / b;
    i64 r = a % b;
    bool quotientPositive = (b >= 0) == (a >= 0);
    return d + (r != 0 && quotientPositive);
}

// https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

// Away from the zero
i64 up_div(i64 a, i64 b)
{
    i64 d = a / b;
    i64 r = a % b;
    signed char quotientSgn = sgn(a) * sgn(b);
    return d + (r != 0) * quotientSgn;
}

i64 down_div(i64 a, i64 b) { return a / b; }

// Given that x == a (mod m)
// NOT require that 0 <= a < m
// Returns how many x fall in [l, r]
i64 count_in_between(i64 a, i64 m, i64 l, i64 r)
{
    assert(l <= r);
    assert(m > 0);

    i64 k_min = ceil_div(l - a, m);
    i64 k_max = floor_div(r - a, m);

    if (k_max < k_min) {
        return 0;
    }
    return k_max - k_min + 1;
}

// Find the min x that satisfies x == a (mod m) and x >= l
i64 find_min_x(i64 a, i64 m, i64 l)
{
    i64 k_min = ceil_div(l - a, m);
    return a + k_min * m;
}

// Find the max x that satisfies x == a (mod m) and x <= r
i64 find_max_x(i64 a, i64 m, i64 r)
{
    i64 k_max = floor_div(r - a, m);
    return a + k_max * m;
}

/* Snippet END */

#ifdef DBG
NumberTheory number_theory(100000);
#else
NumberTheory number_theory((int)2e7 + 5);
#endif

i64 solve()
{
    assert(n <= m);
    assert(n >= 2);

    auto &primes = number_theory.all_primes();

    auto iter = upper_bound(primes.begin(), primes.end(), m);
    iter--;
    int q = *iter;

    auto iter2 = upper_bound(primes.begin(), primes.end(), min((int)n, q - 1));

    if (iter2 != primes.begin()) {
        iter2--;
        // require: gdb(i, p) == 1 for all i in [q, m]
        while (*iter2 > 2 && q / *iter2 < m / *iter2) {
            iter2--;
        }
    }

    int p = *iter2;
    if (p == 2)
        p = 1;
    else {
        assert(q % p != 0);
    }
    dbg(p, n, q, m);

    i64 ret = 0;

    vector<vector<char>> vis(n - p + 1, vector<char>(m - q + 1));
    for (int op = 0; p + op <= n; op++)
        for (int oq = 0; q + oq <= m; oq++) {
            int pp = p + op;
            int qq = q + oq;

            if (pp >= qq)
                continue;

            auto &visit = vis[op][oq];
            if (op == 0 || oq == 0) {
                visit = true;
            } else {
                int g = gcd(pp, qq);
                if (g == 1) {
                    visit = vis[op - 1][oq] || vis[op][oq - 1];
                }
            }

            if (visit) {
                dbg(pp, qq);
                i64 value = l * pp + f * qq;
                ret = max(ret, value);

                if (pp <= m && qq <= n) {
                    i64 value = l * qq + f * pp;
                    ret = max(ret, value);
                }
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
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> l >> f;
        cout << solve() << endl;
    }
    return 0;
}
