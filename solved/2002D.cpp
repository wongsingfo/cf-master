// Created at: Mon Aug 12 00:10:08 CST 2024
/*
Problem Summary:
Given a tree and a series of vertex swaps in a permutation representing a DFS
order of the tree, determine if the permutation after each swap can still be a
valid DFS order.

Key Insight:
1. Calculate the size of each subtree.
2. Calculate the parent of each node.
3. Define a helper function to determine if a permutation is a valid DFS order.
4. Process swaps and determine if the new permutation is valid.

Step-by-Step Plan:
1. Parse the input and initialize the tree structure.
2. Calculate subtree sizes using DFS.
3. Determine the parent for each vertex.
4. Implement a helper function to validate the current permutation as a DFS
order.
5. For each query, swap the vertices in the permutation and validate using the
helper function.
6. Print results for each query.
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

struct TreeTricks
{
    int n;
    vector<int> size, top;

    /// parent[root] = -1;
    vector<int> parent;

    /// dep[root] = 0
    vector<int> dep;

    int cur;
    vector<int> in, out, seq;

    /// adj[u][0] is the "heavy" child of u
    vector<std::vector<int>> adj;

    TreeTricks() {}
    TreeTricks(int n) { init(n); }

    void init(int n)
    {
        this->n = n;
        size.resize(n + 1);
        top.resize(n + 1);
        dep.resize(n + 1);
        parent.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        seq.resize(n + 1);
        cur = 0;
        adj.assign(n + 1, {});
    }

    void insert(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work(int root = 1)
    {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
        assert(cur == n);
    }

    void dfs1(int u)
    {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        size[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            size[u] += size[v];
            if (size[v] > size[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }

    void dfs2(int u)
    {
        cur += 1;
        in[u] = cur;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }

    int lca(int u, int v)
    {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }

    int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

    /// Move up k steps
    int jump(int u, int k)
    {
        if (dep[u] < k) {
            return -1;
        }

        int d = dep[u] - k;

        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }

        return seq[in[u] - dep[u] + d];
    }

    /// Is u an ancestor of v?
    ///
    /// Note that it returns true if u == v.
    bool is_ancester(int u, int v) { return in[u] <= in[v] && in[v] <= out[u]; }
};

int n, q;
vector<int> perm;

void reset_globals()
{
    n = 0;
    q = 0;
    perm.clear();
}

TreeTricks tree;

i64 solve(vector<pair<int, int>> &queries)
{

    auto value = [&](int i) -> bool {
        if (i < 1 || i >= n)
            return false;

        int u = perm[i];
        int v = tree.parent[perm[i + 1]];

        if (v == -1)
            return false;

        if (tree.is_ancester(v, u)) {
            return true;
        }
        return false;
    };

    int PP = 0;
    vector<int> value_tmp(n + 1);
    for (int i = 1; i < n; i++) {
        value_tmp[i] = value(i);
        PP += value_tmp[i];
    }

    auto update_value = [&](int i) -> int {
        if (i < 1 || i >= n)
            return 0;
        int ret = -value_tmp[i];
        value_tmp[i] = value(i);
        ret += value_tmp[i];
        return ret;
    };

    for (auto [x, y] : queries) {
        dbg("====");
        for (int i = 1; i < n; i++) {
            dbg(value(i));
        }

        dbg(x, y, x - 1, y - 1);

        swap(perm[x], perm[y]);

        PP += update_value(x);
        PP += update_value(y);
        PP += update_value(x - 1);
        PP += update_value(y - 1);

#ifdef DBG
        dbg("----");
        int PP_ = 0;
        for (int i = 1; i < n; i++) {
            PP_ += value(i);
            dbg(value(i));
        }
        assert(PP == PP_);
#endif

        if (PP == n - 1)
            cout << "YES";
        else
            cout << "NO";
        cout << endl;
    }

    return 0;
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
        cin >> n >> q;

        tree.init(n);

        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            tree.insert(p, i);
        }

        perm.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> perm[i];
        }

        tree.work(1);

        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            cin >> queries[i].first >> queries[i].second;
        }

        solve(queries);
    }

    return 0;
}

// Time Complexity: O(n + q) per test case considering preprocessing and each
// query being O(1).
