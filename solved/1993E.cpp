// Created at: Tue Aug 6 15:34:06 CST 2024
/* Problem Summary: Given multiple test cases, each representing a matrix with
dimensions n x m, find the smallest possible "beauty" of the matrix. The beauty
is defined as the maximum value within the matrix minus the minimum value within
the matrix.

Key Insight: We need to determine the difference between the maximum and minimum
values in each matrix for all test cases to calculate the beauty.

Step-by-Step Plan:
1. Read the number of test cases.
2. For each test case:
    a. Read the dimensions of the matrix (n and m).
    b. Read the matrix values and track the minimum and maximum values.
    c. Compute the beauty as the difference between the maximum and minimum
values of the matrix.
3. Output the results for each test case.
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

/* Snippet BEGIN */

template <typename T, T Invalid = std::numeric_limits<T>::min()> struct DpInt
{
    T x;
    constexpr DpInt() : x{Invalid} {}
    constexpr DpInt(T x) : x{x} {}

    constexpr i64 val() const { return x; }

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

int n, m;
vector<vector<int>> a;

void reset_globals()
{
    n = 0;
    m = 0;
    a.clear();
}

template <typename T> vector<vector<T>> transpose(vector<vector<T>> matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<T>> transposed(cols, vector<T>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

vector<vector<int>> solve(vector<vector<int>> matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> ans(rows, vector<int>(cols));

    for (int removed = 0; removed < rows; removed++) {
        vector<vector<int>> dist(cols, vector<int>(cols));
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < cols; j++) {
                int cost = 0;
                for (int k = 0; k < rows; k++) {
                    if (k != removed)
                        cost += std::abs(matrix[k][i] - matrix[k][j]);
                }
                dist[i][j] = cost;
            }
        }

        dbg(removed, dist);

        vector<vector<DInt>> dp(cols, vector<DInt>(1 << cols));
        for (int i = 0; i < cols; i++) {
            dp[i][1 << i] = 0;
        }

        for (int s = 1; s < (1 << cols); s++) {
            for (int i = 0; i < cols; i++) {
                auto &curr = dp[i][s];
                if (curr.invalid())
                    continue;
                dbg(s | cpp_dump::bin(cols), i, curr);
                for (int j = 0; j < cols; j++) {
                    if ((s >> j) & 1)
                        continue;
                    dp[j][s | (1 << j)].min(curr + dist[i][j]);
                }
            }
        }

        for (int i = 0; i < cols; i++) {
            DInt result;
            int set = ((1 << cols) - 1) ^ (1 << i);
            for (int j = 0; j < cols; j++) {
                result.min(dp[j][set]);
            }
            dbg(removed, i, set | cpp_dump::bin(cols), result);
            assert(!result.invalid());
            ans[removed][i] = result.val();
        }
    }

    return ans;
}

int solve()
{
    dbg(a);
    DInt ans;

    auto remove_row = solve(a);
    dbg(remove_row);
    auto remove_col = transpose(solve(transpose(a)));
    dbg(remove_col);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            auto v = remove_row[i][j] + remove_col[i][j];
            ans.min(v);
        }

    return ans.val();
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
        reset_globals();
        // Start input after reset_globals
        cin >> n >> m;
        a.resize(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];

                a[i][m] ^= a[i][j];
                a[n][j] ^= a[i][j];
                a[n][m] ^= a[i][j];
            }
        }
        auto ans = solve();
        cout << ans << endl;
    }

    return 0;
}

// Time Complexity: O(n * m) per test case.
