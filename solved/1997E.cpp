// Created at: Wed Jul 31 10:35:47 CST 2024
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#endif

class FenwickTree
{
  public:
    FenwickTree(int size) : size(size) { tree.resize(size + 1, 0); }

    void update(int index, int value)
    {
        for (; index <= size; index += index & -index) {
            tree[index] += value;
        }
    }

    int query(int index)
    {
        int sum = 0;
        for (; index > 0; index -= index & -index) {
            sum += tree[index];
        }
        return sum;
    }

    int rangeQuery(int left, int right)
    {
        return query(right) - query(left - 1);
    }

  private:
    std::vector<int> tree;
    int size;
};

int n, q;
vector<int> a;

void reset_globals()
{
    a.clear();
    a.resize(n + 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    reset_globals();

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<int> min_yes_k(n + 1);

    FenwickTree tree(n);

    for (int i = 1; i <= n; i++) {
        int lo = 1, hi = n, ans = -1;
        while (lo <= hi) {
            int mi = (lo + hi) / 2;
            int fights = tree.query(mi);
            int level = fights / mi + 1;
            if (level <= a[i]) {
                ans = mi;
                hi = mi - 1;
            } else {
                lo = mi + 1;
            }
        }

        min_yes_k[i] = ans;
        tree.update(ans, 1);
    }

    while (q--) {
        int i, x;
        cin >> i >> x;
        bool will_fight = min_yes_k[i] <= x;
        if (will_fight)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}
