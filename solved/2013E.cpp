// Created at: Sat Sep 21 14:02:51 CST 2024
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

void reset_globals() { a.clear(); }

i64 solve()
{
    i64 ans = 0;

    while (!a.empty()) {
        sort(a.begin(), a.end());
        ans += a.front();

        decltype(a) b;
        for (auto i = 1u; i < a.size(); i++) {
            b.push_back(gcd(a[0], a[i]));
        }

        if (b.empty()) {
            break;
        }

        sort(b.begin(), b.end());
        if (b.front() == b.back()) {
            ans += (i64) b.front() * b.size();
            break;
        }

        a = b;
    }

    return ans;
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
        int n;
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        auto ans = solve();
        cout << ans << endl;
    }

    return 0;
}
