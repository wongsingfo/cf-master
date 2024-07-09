#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 200005;

#ifdef DBG
#define dbg(...) printf(__VA_ARGS__)
#else
#define dbg(...)
#endif

int t;
int n;
vector<int> adj[MAXN]; // adjacency list
int degree[MAXN];      // to track the degree of each node

// Reset global variables
void reset() {
    for (int i = 0; i <= n; ++i) {
        adj[i].clear();
        degree[i] = 0;
    }
}

static int f[MAXN]; // anyhow
static int g[MAXN]; // must be split point

static int f_up[MAXN]; // anyhow
static int g_up[MAXN]; // must be split point
//

static int par[MAXN];

void dfs(int u, int par) {
    ::par[u] = par;

    if (degree[u] == 1 && par != -1) {
        f[u] = 1;
        g[u] = 0;
        return;
    }
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == par) {
            continue;
        }

        dfs(v, u);
    }

    int gg = 0;
    // be split point

    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == par) {
            continue;
        }

        gg += f[v];
    }

    int ff = 1;
    // be leaf, then all chilerens must be split point

    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == par) {
            continue;
        }
        ff += g[v];
    }

    f[u] = max(ff, gg);
    g[u] = gg;

    dbg("u=%d, ff=%d, gg=%d, f[u]=%d, g[u]=%d\n", u, ff, gg, f[u], g[u]);
}

void dfs2(int u, int par) {
    if (degree[u] == 1 && par != -1) {
        return;
    }

    int sumg = 0, sumf = 0;
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == par) {
            continue;
        }
        sumg += g[v];
        sumf += f[v];
    }

    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == par) {
            continue;
        }
        // ff_up[v] = g[others child of u] + g_up[u] + 1;
        // gg_up[v] = f[others child of u] + f_up[u];

        int ff_up = (sumg - g[v]) + g_up[u] + 1;
        int gg_up = (sumf - f[v]) + f_up[u];

        f_up[v] = max(ff_up, gg_up);
        g_up[v] = gg_up;
        dfs2(v, u);
    }

}

// Example solve function, adjust as necessary for your logic
int solve() {

    dfs(1, -1);
    f_up[1] = 0;
    g_up[1] = 0;
    dfs2(1, -1);

    int ans = 0;
    for (int u = 1; u <= n; u++) {
        int count = 0;

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (v == par[u]) {
                continue;
            }

            count += f[v];
        }

        count += f_up[u];

        if (degree[u] == 1) {
            count++;
        }

        dbg("u=%d, count=%d, f[u]=%d, g[u]=%d, f_up[u]=%d, g_up[u]=%d\n", u,
            count, f[u], g[u], f_up[u], g_up[u]);
        ans = max(ans, count);
    }

    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        reset();
        scanf("%d", &n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d", &u);
            scanf("%d", &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }
        printf("%d\n", solve());
    }
    return 0;
}
