// Created at: Mon Aug 12 18:04:50 CST 2024
/*
Problem Summary:
We need to determine how many seconds it will take for a sequence of integers to
become empty after repeatedly deleting specific elements.

Key Insight:
In each second, we can delete `si` elements such that either `i=1` or `si` is
not equal to `si-1`. Therefore, in each step, we find the minimum element count
from the sequence definitions and decrement this count from all segments until
the sequence is empty.

Step-by-Step Plan:
1. Read the number of test cases.
2. For each test case:
   a. Reset global variables.
   b. Read number of pairs `n`.
   c. Read the sequence pairs (ai, bi).
   d. Track the sequence segments and their counts.
   e. For each prefix of the sequence:
      i. Determine the minimum count among the segments.
      ii. Deduct the minimum count from each segment and compute the total steps
taken.
3. Print the results for each prefix.
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
vector<pair<i64, int>> pairs;

void reset_globals()
{
    n = 0;
    pairs.clear();
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

        cin >> n;
        pairs.resize(n);

        vector<pair<i64, int>> stk;
        for (int i = 0; i < n; ++i) {
            cin >> pairs[i].first >> pairs[i].second;

            while (!stk.empty()) {
                auto top = stk.back();
                assert(top.second != pairs[i].second);
                if (pairs[i].first < top.first) {
                    break;
                }

                stk.pop_back();
                if (stk.empty())
                    break;
                auto top2 = stk.back();

                if (top2.second == pairs[i].second) {
                    stk.pop_back();
                    pairs[i].first += top2.first - top.first;
                }
            }

            stk.push_back(pairs[i]);

            cout << stk.front().first << ' ';
        }

        cout << endl;
    }

    return 0;
}

// Time Complexity: O(n^2) per test case, where n is the maximum length of the
// sequences.
