#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXN = 300005;

#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

ll n, t;
ll a[MAXN];
vector<int> adj[MAXN];

const int k = 20;
ll f[MAXN][k];

void reset_globals()
{
    fill(a, a + n, 0);
    memset(f, 0, sizeof(ll) * n * k);
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
}

void dfs(int u, int par)
{
    // f[u][3] = a[u] * (3+1) + \sum_v \min{f[v][any but != 3]

    for (int i = 0; i < k; i++) {
        f[u][i] = a[u] * (i + 1);
    }

    for (int v : adj[u]) {
        if (v == par)
            continue;
        dfs(v, u);

        static ll suffix_min[k], prefix_min[k];
        suffix_min[k - 1] = f[v][k - 1];
        for (int i = k - 2; i >= 0; i--) {
            suffix_min[i] = min(suffix_min[i + 1], f[v][i]);
        }

        prefix_min[0] = f[v][0];
        for (int i = 1; i < k; i++) {
            prefix_min[i] = min(prefix_min[i - 1], f[v][i]);
        }

        for (int i = 0; i < k; i++) {
            if (i == 0) {
                f[u][i] += suffix_min[i + 1];
            } else if (i + 1 == k) {
                f[u][i] += prefix_min[i - 1];
            } else {
                f[u][i] += min(prefix_min[i - 1], suffix_min[i + 1]);
            }
        }
    }
}

ll solve()
{
    // Implement your solution here and return the result

    dfs(0, -1);
    ll ans = -1;
    for (int i = 0; i < k; i++) {
        if (ans == -1 || f[0][i] < ans) {
            ans = f[0][i];
        }
    }

    return ans;
}

int main()
{
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld", &n);
        // dbg("n = %d\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--;
            y--; // zero-indexing if the problem requires
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        // Call the solve function and print its result
        printf("%lld\n", solve());

        // Reset the global input data
        reset_globals();
    }
    return 0;
}
