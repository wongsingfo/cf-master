// Created at: Tue Aug 20 11:21:11 CST 2024
/*
Problem Summary:
Given an array `a` of `n` integers. For all subarrays of `a`, calculate the sum
of the minimum number of operations needed to make each subarray a palindrome.

Key Insight:
Transforming an array to a palindrome can be seen in dynamic programming terms,
where we gradually bridge the elements from both ends till the middle,
incrementing the count of operations for each transformation.

Step-by-Step Plan:
1. Define a DP table `dp` where `dp[l][r]` represents the minimum operations
needed to convert the subarray `a[l..r]` into a palindrome.
2. Fill the DP table using a nested loop where we consider each length of the
subarray from 1 to `n`.
3. Calculate the sum of all `dp[l][r]` for all subarrays in the given array.
4. Use the math property of counting subarrays to iterate through all subarrays
efficiently.

Implementation:
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

int n;
vector<int> a;

void reset_globals()
{
    n = 0;
    a.clear();
}

uint64_t random_address()
{
    char *p = new char;
    delete p;
    return uint64_t(p);
}

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct safe_hash
{
    static unsigned hash32(unsigned x)
    {
        // https://groups.google.com/g/prng/c/VFjdFmbMgZI
        x += 0x9e3779b9;
        x = (x ^ (x >> 16)) * 0x85ebca6b;
        x = (x ^ (x >> 13)) * 0xc2b2ae35;
        return x ^ (x >> 16);
    }

    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    template <typename T> uint64_t operator()(T x) const
    {
        static const uint64_t FIXED_RANDOM =
            splitmix64(chrono::steady_clock::now().time_since_epoch().count() *
                       (random_address() | 1));
        if constexpr (sizeof(x) <= 4)
            return hash32(unsigned(x ^ FIXED_RANDOM));
        else
            return splitmix64(x ^ FIXED_RANDOM);
    }
};

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

i64 solve()
{
    i64 ret = 0;

    vector<int> pre(n + 2);
    for (int i = 1; i <= n + 1; i++)
        pre[i] = pre[i - 1] + a[i - 1];

    gp_hash_table<int, tuple<int, int, int>, custom_hash> dp;

    for (int len = 1; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            int hash = pre[i] + pre[j + 1];

            int ans = -1;
            auto iter = dp.find(hash);
            if (iter == dp.end()) {
                if (hash % 2 == 0 &&
                    binary_search(pre.begin() + i + 1, pre.begin() + j + 1,
                                  hash / 2)) {
                    ans = len - 2;
                } else {
                    ans = len - 1;
                }
            } else {
                auto [l, r, prev_ans] = iter->second;
                int clen = (l - i) + (j - r);
                ans = prev_ans + clen - 2;
            }

            dbg(i, j, ans, hash);
            dp[hash] = {i, j, ans};
            ret += ans;
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
        reset_globals();
        // start input after reset_globals
        cin >> n;
        a.resize(n + 1);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        auto ans = solve();
        cout << ans << endl;
    }
    return 0;
}

// Time Complexity: The DP approach will work in O(n^3) per test case because of
// filling the DP table and then summing the results.
