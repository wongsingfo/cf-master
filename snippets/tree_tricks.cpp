/* Snippet Header */
#include <bits/stdc++.h>
using namespace std;

/* Snippet BEGIN */
class TreeTricks
{
  public:
    int n;

    /// Size of the subtree.
    vector<int> size;

    /// The top of the heavy path
    vector<int> top;

    /// parent[root] = -1;
    vector<int> parent;

    /// dep[root] = 0
    vector<int> dep;

    /// Starts from 1.
    int cur;

    /// `in` and `out` are inclusive. Starts from 1.
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

  private:
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
        seq[cur] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
};
/* Snippet END */
