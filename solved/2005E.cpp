// Created at: Sun Sep 22 11:44:05 CST 2024
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

int l, n, m;
vector<int> a;
vector<vector<int>> b;
vector<vector<int>> dp;

void reset_globals()
{
    l = n = m = 0;
    a.clear();
    b.clear();
    dp.clear();
}

char solve()
{
    vector<int> first_occurrence(n * m + 1, -1);
    for (int i = l - 1; i >= 0; i--) {
        first_occurrence[a[i]] = i;
    }

    // for (int i = 1; i < l; i++) {
    //     if (first_occurrence[a[i]] != i) {
    //         l = i;
    //         break;
    //     }
    // }

    dp.assign(n, vector<int>(m, INT_MAX));

    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            auto &v = dp[i][j];
            if (i + 1 < n)
                v = min(v, dp[i + 1][j]);
            if (j + 1 < m)
                v = min(v, dp[i][j + 1]);

            int index = first_occurrence[b[i][j]];
            if (index == -1)
                continue;

            if (i + 1 == n || j + 1 == m || dp[i + 1][j + 1] >= index + 2)
                v = min(v, index);
        }
    }

    return (dp[0][0] <= 0) ? 'T' : 'N';
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
        cin >> l >> n >> m;
        a.resize(l);
        for (int i = 0; i < l; ++i) {
            cin >> a[i];
        }
        b.resize(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> b[i][j];
            }
        }
        cout << solve() << '\n';
    }
    return 0;
}
