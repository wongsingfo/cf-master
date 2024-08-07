// Created at: Tue Aug 6 19:58:18 CST 2024
/*
Problem Summary:
Given multiple test cases, each case contains a script describing the movements
of a robot (U, D, L, R). We need to determine how many times the robot returns
to the origin (0, 0) after executing the script 'k' times.

Key Insight:
The number of times the robot returns to the origin in one execution of the
script can be calculated based on the changes in x, y coordinates caused by the
script. If the net displacement for the script is (dx, dy), the robot will
return to the origin whenever: dx * m <= w and dy * m <= h where m is a
multiplier.

Step-by-Step Plan:
1. Parse the input and store necessary values.
2. Compute the net displacement after one execution of the script.
3. Check how many times the robot returns to the origin based on w, h, and the
net displacement.
*/

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

int n, w, h; // 1e6
i64 k;       // 1e12
string s;

/* Snippet Header */
#include <bits/stdc++.h>
using namespace std;

/* Snippet BEGIN */
class NumberTheory
{
  public:
    NumberTheory(int n) : n(n), min_divisor(n + 1, 0), phi(n + 1) { init(); }

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
    int inv(int x, int m)
    {
        assert(2 <= m && m <= n);
        // inv(x, m) = x^(phi(m) - 1)
        int result = pow(x, phi[m] - 1, m);
#ifdef DBG
        assert((i64)result * x % m == 1);
#endif
        return result;
    }

  private:
    int n;
    vector<int> min_divisor;
    vector<int> primes;
    vector<int> phi; // Euler's totient function

    void init()
    {
        phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (min_divisor[i] == 0) {
                min_divisor[i] = i;
                phi[i] = i - 1;
                primes.push_back(i);
            }
            for (int j : primes) {
                if (i * j > n)
                    break;
                min_divisor[i * j] = j;
                if (i % j == 0) {
                    phi[i * j] = phi[i] * j;
                    break;
                } else {
                    phi[i * j] = phi[i] * (j - 1);
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

    dbg(a1, n1, a2, n2, k1, k2, lcm);
    // x = (a1 + k1 * n1 % lcm) % lcm
    // Note that k1 * n1 overflows (because k1~1e18, n1~1e9)
    //
    // Note that X * n1 % lcm
    //         = X * n1 % (n1 * n2 / d)  % lcm
    //         = X * (n2 / d) * n1       % lcm
    i64 x = (a1 + k1 % n2_ * scaled % n2_ * n1 % lcm) % lcm;
    if (x < lcm)
        x += lcm;

    return {{x, lcm}};
}

i64 floor_div(i64 a, i64 b)
{
    // auto res = lldiv(a, b);
    i64 d = a / b;
    i64 r = a % b;
    return r ? (d - ((a < 0) ^ (b < 0))) : d;
}

i64 ceil_div(i64 a, i64 b)
{
    i64 d = a / b;
    i64 r = a % b;
    bool quotientPositive = (b >= 0) == (a >= 0);
    return d + (r != 0 && quotientPositive);
}

// Given that x == a (mod m)
// Returns how many times x fall in [l, r]
i64 count_fallin(i64 a, i64 m, i64 l, i64 r)
{
    dbg(a, m, l, r);
    assert(l <= r);
    assert(m > 0);

    i64 k_min = ceil_div(l - a, m);
    i64 k_max = floor_div(r - a, m);

    if (k_max < k_min) {
        return 0;
    }
    return k_max - k_min + 1;
}

/* Snippet END */

NumberTheory nt(2e6 + 3);

// Function to compute number of times the robot reaches the origin
i64 solve()
{
    int dx = 0, dy = 0;
    i64 result = 0;

    vector<tuple<int, int>> positions;

    int w2 = w * 2;
    int h2 = h * 2;

    dbg(w, h, s, k);

    // Calculate net displacement for one script execution
    for (char dir : s) {
        if (dir == 'L')
            dx--;
        if (dir == 'R')
            dx++;
        if (dir == 'U')
            dy++;
        if (dir == 'D')
            dy--;

        dx = (dx + w2) % w2;
        dy = (dy + h2) % h2;
        positions.push_back({dx, dy});
    }

    auto [dxn, dyn] = positions.back();
    dbg(dxn, dyn);

    for (auto [dx, dy] : positions) {
        // dx + i * dxn == 0 (mod w2), i = 0, 1, 2, ..., k-1
        // dy + i * dyn == 0 (mod h2), i = 0, 1, 2, ..., k-1
        //
        // dx + i * dxn == 0 (mod w2), i = 0, 1, 2, ..., k-1
        //      i * dxn == -dx (mod w2)
        //            i == -dx * dxn^(-1) (mod w2)  <require gcd(dnx, w2)=1>
        // suppose d = gcd(dxn, w2), dxn' = dxn / d, w2' = w2 / d
        //     i * dxn' == -dx / d  (mod w2')
        // if no  d | dx, no solution
        //            i == -dx / d * dxn'^(-1) (mod w2')
        // let rightside = di
        //            i == di (mod w2')
        //            j == dj (mod h2')

        dbg("----", dx, dy);
        i64 d0 = gcd(dxn, w2);
        i64 d1 = gcd(dyn, h2);
        dbg(dxn, w2, d0);
        if (dx % d0 > 0)
            continue;
        if (dy % d1 > 0)
            continue;

        i64 w2_ = w2 / d0;
        i64 h2_ = h2 / d1;
        i64 dxn_ = dxn / d0;
        i64 dyn_ = dyn / d1;

        i64 count;
        if (w2_ == 1 && h2_ == 1) {
            count = k;
        } else if (w2_ == 1) {
            i64 dj = -dy / d1 * nt.inv(dyn_, h2_);
            count = count_fallin(dj, h2_, 0, k - 1);
        } else if (h2_ == 1) {
            i64 di = -dx / d0 * nt.inv(dxn_, w2_);
            count = count_fallin(di, w2_, 0, k - 1);
        } else {
            i64 di = -dx / d0 * nt.inv(dxn_, w2_);
            i64 dj = -dy / d1 * nt.inv(dyn_, h2_);

            dbg(di, dj);
            auto res = chinese_remainder(di, w2_, dj, h2_);
            if (!res)
                continue;
            auto [i, shift] = *res;

            count = count_fallin(i, shift, 0, k - 1);
            dbg(i, shift, count);
        }
        result += count;
    }

    return result;
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
        cin >> n >> k >> w >> h;
        cin >> s;
        auto ans = solve();
        cout << ans << endl;
    }

    return 0;
}

// Time Complexity: O(n) per test case.
