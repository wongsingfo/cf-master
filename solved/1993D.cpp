// Created at: Sun Aug 4 23:28:46 CST 2024
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

vector<int> a;
int n, k;

void reset_globals()
{
    n = 0;
    k = 0;
    a.clear();
}

bool canAchieveMedian(int X, [[maybe_unused]] int m, int P)
{
    // pick exactly m elements, m <= k
    // At least P of them is >= X
    dbg(X);
    int inf = INT_MIN;
    int invalid = -inf;

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = a[i] >= X;
    }
    dbg(b);

    // dp[i]: i is the last picked element
    // for the first element, i % k == 0
    vector<int> dp(n, invalid);
    vector<int> pre(n, invalid);

    for (int i = 0; i < n; ++i) {
        int vi = b[i];

        if (i % k == 0) {
            dp[i] = vi;
        } else {
            dp[i] = max(dp[i], pre[i - 1] + vi);
        }
        pre[i] = max(i >= k ? pre[i - k] : invalid, dp[i]);
    }

    dbg(dp);
    dbg(pre);

    auto maxii = invalid;
    for (int i = 0; i < n; i++)
        if (i % k < m) {
            maxii = max(maxii, dp[i]);
        }
    dbg(maxii, P);

    return maxii >= P;
}

i64 solve()
{
    int m = (n % k == 0) ? k : n % k;

    /// m = 1, P = 1
    /// m = 2, P = 2
    /// m = 3, P = 2
    /// m = 4, P = 3
    /// m = 5, P = 3
    int P = (m + 2) / 2;

    dbg(a, k);
    dbg(m, P);

    int low = 1, high = *max_element(a.begin(), a.end());
    int best = low;

    // canAchieveMedian(9, m, P);

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canAchieveMedian(mid, m, P)) {
            best = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return best;
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
        cin >> n >> k;
        a.resize(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        auto ans = solve();
        cout << ans << endl;
    }

    return 0;
}

// Time Complexity: O(n log(max_element)) per test case.
