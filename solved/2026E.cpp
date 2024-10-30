// Created at: Wed Oct 30 11:13:17 CST 2024
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

/* Snippet Header */
#include <bits/stdc++.h>

/* Snippet BEGIN */
template <class T> class MaxFlow
{
  public:
    MaxFlow() {}
    MaxFlow(int n) { init(n); }

    void init(int n)
    {
        this->n = n;
        edge.clear();
        graph.assign(n, {});
        cur.resize(n);
        level.resize(n);
    }

    void add_edge(int u, int v, T c)
    {
        graph[u].push_back(edge.size());
        edge.emplace_back(v, c);
        graph[v].push_back(edge.size());
        edge.emplace_back(u, 0);
    }

    void add_edge_inf(int u, int v)
    {
        auto c = std::numeric_limits<T>::max();
        add_edge(u, v, c);
    }

    T flow(int s, int t)
    {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }

    // Returns a vector of boolean values representing the minimum cut.
    // 'true' indicates the vertex is on the source side of the cut.
    // 'false' indicates the vertex is on the sink side of the cut.
    // This function should be called after running the `flow` function.
    std::vector<bool> minCut()
    {
        std::vector<bool> cut(n);
        for (int i = 0; i < n; i++) {
            cut[i] = (level[i] != -1);
        }
        return cut;
    }

    struct Edge
    {
        int from;
        int to;
        T cap;
        T flow;
    };

    std::vector<Edge> edges()
    {
        std::vector<Edge> ret;
        for (int i = 0; i < edge.size(); i += 2) {
            Edge edge;
            edge.from = edge[i + 1].to;
            edge.to = edge[i].to;
            edge.cap = edge[i].cap + edge[i + 1].cap;
            edge.flow = edge[i + 1].cap;
            ret.push_back(edge);
        }
        return ret;
    }

  private:
    bool bfs(int s, int t)
    {
        level.assign(n, -1);
        std::queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : graph[u]) {
                auto [v, c] = edge[i];
                if (c > 0 && level[v] == -1) {
                    level[v] = level[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T flow)
    {
        if (u == t) {
            return flow;
        }
        auto remaining = flow;
        for (int &i = cur[u]; i < int(graph[u].size()); ++i) {
            const int j = graph[u][i];
            auto [v, capacity] = edge[j];
            if (capacity > 0 && level[v] == level[u] + 1) {
                auto f = dfs(v, t, std::min(remaining, capacity));
                edge[j].cap -= f;
                edge[j ^ 1].cap += f;
                remaining -= f;
                if (remaining == 0) {
                    return flow;
                }
            }
        }
        return flow - remaining;
    }

    struct _Edge
    {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };

    int n;
    std::vector<_Edge> edge;
    std::vector<std::vector<int>> graph;
    std::vector<int> cur, level;
};
/* Snippet END */
int n;
vector<i64> a;

void reset_globals()
{
    n = 0;
    a.clear();
}

i64 solve()
{
    int m = 60;
    int s = n + m;
    int t = n + m + 1;

    MaxFlow<int> max_flow(t + 1);

    int ans = n;

    for (int i = 0; i < n; i++) {
        max_flow.add_edge(s, i, 1);
    }

    for (int i = 0; i < m; i++) {
        int node = n + i;
        max_flow.add_edge(node, t, 1);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if ((a[i] >> j) & 1) {
                max_flow.add_edge_inf(i, n + j);
            }
        }

    return ans - max_flow.flow(s, t);
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
        a.resize(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        auto ans = solve();
        cout << ans << endl;
    }

    return 0;
}
