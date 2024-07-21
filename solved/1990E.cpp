#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const int MAXN = 5005;
vector<int> adj[MAXN];
int t, n;

#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
const int B = 2;
#else
#define dbg(...)
const int B = 70;
#endif

//// N / B + B + log N

void reset_globals()
{
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
    }
}

int query(int x)
{
    printf("? %d\n", x);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}

void submit(int x)
{
    printf("! %d\n", x);
    fflush(stdout);
}

int par[MAXN];

void dfs(int u, int par)
{
    ::par[u] = par;
    if (par != -1) {
        adj[u].erase(std::find(adj[u].begin(), adj[u].end(), par));
    }
    for (int v : adj[u])
        dfs(v, u);
}

bool possible[MAXN];
int f[MAXN];

void dfs2(int u)
{
    if (!possible[u])
        return;

    f[u] = 1;
    for (int v : adj[u]) {
        dfs2(v);
        f[u] = max(f[u], f[v] + 1);
    }
}

void make_false(int u)
{
    possible[u] = false;
    for (int v : adj[u]) {
        make_false(v);
    }
}

void solve()
{
    dfs(1, -1);

    int dummy = -1;
    for (int i = 1; i <= n; i++) {
        if (adj[i].empty()) {
            dummy = i;
            break;
        }
    }
    assert(dummy != -1);
    if (query(dummy)) {
        submit(dummy);
        return;
    }

    fill(possible, possible + n + 1, true);

    int in_subtree = -1;
    while (true) {
        fill(f, f + n + 1, 0);

        dfs2(1);

        int u = -1;
        for (int i = 1; i <= n; i++) {
            dbg("f[%d] = %d\n", i, f[i]);
            if (f[i] == B) {
                u = i;
                break;
            }
        }
        if (u == -1) {
            dbg("not found large subtree, move to root\n");
            for (int i = 1; i <= B; i++) {
                query(dummy);
            }
            submit(1);
            return;
        }

        bool in_u = query(u);

        if (!in_u) {
            // make subtree u false, make par[u] false
            dbg("make_false %d\n", u);
            make_false(u);
        } else {
            in_subtree = u;
            break;
        }
    }
    dbg("move out of the subtree\n");

    for (int i = 1; i <= B; i++) {
        query(dummy);
    }

    if (in_subtree == 1) {
        submit(1);
        return;
    } else {
        assert(query(in_subtree) == false);
    }

    dbg("perform binary search\n");

    // from u to the 1
    int u = in_subtree;
    vector<int> path;
    while (u != -1) {
        path.push_back(u);
        u = par[u];
    }

    /// u ---> 1
    int l = 0, r = path.size() - 1;
    while (l < r) {
        int m = (l + r) / 2;
        bool in_m = query(path[m]);
        if (in_m) {
            assert(r != m);
            r = m;
        } else {
            l = m + 1;
            if (path[l] != 1) {
                l += 1;
            }

            if (path[r] != 1) {
                r += 1;
            }
        }
    }

    submit(path[r]);
}

int main()
{
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        reset_globals();
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        solve();
    }
    return 0;
}
