// Created at: Tue Aug 13 10:17:22 CST 2024
/*
Problem Summary:
Given a sequence of n balls, each with an initial value, indexed from 1 through
n. For each index i from 1 to n, the task is to determine the number of possible
sets S that can remain consisting of only the ith ball after performing a series
of defined operations.

Key Insight:
- The hint suggests that the problem can be tackled by considering the order and
value properties of the balls.
- Notably, the operations can be interpreted as comparisons and combinations of
the values of the balls.

Step-by-Step Plan:
1. For each test case, read the input values n and x, and the array a.
2. Process each ball from position x to n.
3. Initialize a set S that holds the indices up to i.
4. For iterating j from x to i, simulate the operations defined:
    a. Compare adjacent balls' values.
    b. Depending on the comparison, merge the balls and remove one from the set.
    c. Count such valid operations where only one specific ball remains.
5. Output the result for each test case.
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

int n, x;
vector<int> a;

void reset_globals()
{
    n = 0;
    x = 0;
    a.clear();
}

struct Node
{
    int num;
    int l, r;
    i64 sum;   // sum of left tree
    int count; // count the left tree
};

dbg_export(Node, l, r, num, sum, count);

vector<int> solve()
{
    vector<int> ans(n + 1, 0);

    vector<Node> nodes(n + 1, Node{});
    vector<int> stk; // (id)

    int idx = 0;
    int sum_count = 0;
    i64 sum_idx = 0;
    i64 sum_all = 0;

    for (int i = 1; i <= n; i++) {
        dbg("-----");
        int num = a[i - 1];
        dbg(i, num, stk);

        int k = stk.size() - 1;
        while (k >= 0 && num >= nodes[stk[k]].num)
            k -= 1;

        int count = 0;
        i64 sum_link = 0;
        for (int j = k + 1; j < (int)stk.size(); j++) {
            int p = stk[j];
            sum_link += nodes[p].num;
            sum_link += nodes[p].sum;
        }

        i64 sum_link_ = sum_link;

        for (int j = k + 1, p_num = num; j < (int)stk.size(); j++) {
            int p = stk[j];
            bool ok = sum_link >= p_num;
            if (!ok)
                break;
            count += 1 + nodes[p].count;

            p_num = nodes[p].num;
            sum_link -= nodes[p].num;
            sum_link -= nodes[p].sum;
        }

        dbg(k, sum_link_);

        if (k == -1) {
            nodes[i].num = num;
            nodes[i].l = stk.empty() ? 0 : stk[0];
            nodes[i].sum = sum_link_;
            nodes[i].count = count;

            stk.clear();
            idx = 0;
            sum_count = 0;
            sum_idx = 0;
            stk.push_back(i);
        } else {
            int j = stk[k];
            nodes[i].num = num;
            nodes[i].l = nodes[j].r;
            nodes[i].sum = sum_link_;
            nodes[i].count = count;

            nodes[j].r = i;
            // stk.resize(k + 1);
            while ((int) stk.size() > k + 1) {
                if ((int) stk.size() == idx) {
                    idx -= 1;
                    int p = stk.back();
                    sum_count -= nodes[p].count + 1;
                    sum_idx -= nodes[p].sum + nodes[p].num;
                }
                stk.pop_back();
            }
            stk.push_back(i);
        }

        sum_all += num;

        while (idx < (int)stk.size()) {
            int p = stk[idx];
            i64 sum = sum_all - sum_idx;
            if (sum < (idx > 0 ? nodes[stk[idx-1]].num : 0)) {
                break;
            }

            idx += 1;
            sum_count += 1 + nodes[p].count;
            sum_idx += nodes[p].num + nodes[p].sum;
        }

        dbg(nodes[i]);
        ans[i] = sum_count;
    }

    return vector<int>(ans.begin() + x, ans.end());
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
        cin >> n >> x;
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        auto ans = solve();
        for (int x : ans) {
            cout << x << ' ';
        }
        cout << endl;
    }
    return 0;
}

// Time Complexity: O(n^2) per test case due to the nested loops and set
// operations.
