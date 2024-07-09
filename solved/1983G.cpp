#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
/// ai≤5e5
const int MAXL = 3; // 1<<19 = 524288
#else
const int MAXL = 19; // 1<<19 = 524288
#define dbg(...)
#endif

const int root = 1;
const int MAXN = 500005;

int n, q;

vector<int> adj[MAXN];
int a[MAXN];

int parent[MAXN];
int depth[MAXN];
int siz[MAXN];
int top[MAXN];


int psum[MAXL][MAXN];
int sum[MAXL][MAXN];

int stk[MAXN], stack_top;

int in[MAXN], seq[MAXN], seq_count;

void reset()
{
    fill(adj, adj + n + 1, vector<int>());
    fill(a, a + n + 1, 0);
    seq_count = 0;
}

void dfs(int u, int par, int dep)
{
    // erase par from adj[u]
    if (par != 0)
        adj[u].erase(std::find(adj[u].begin(), adj[u].end(), par));

    parent[u] = par;
    depth[u] = dep;
    siz[u] = 1;
    for (int &v : adj[u]) {
        dfs(v, u, dep + 1);
        siz[u] += siz[v];
        if (siz[v] > siz[adj[u][0]]) {
            swap(v, adj[u][0]);
        }
    }
}

void dfs2(int u, int t)
{
    seq[++seq_count] = u;
    in[u] = seq_count;

    top[u] = t;
    for (int v : adj[u]) {
        if (v == adj[u][0])
            dfs2(v, t);
        else
            dfs2(v, v);
    }

    // out[u] = seq_count;
}

void dfs3(int u)
{
    ///// calc sum
    for (int i = 0; i < MAXL; ++i) {
        sum[i][u] = (a[u] >> i) & 1;
        sum[i][u] += sum[i][parent[u]];
    }

    //// calc psum

    /// 001100110011   i=1
    /// 000011110000   i=2
    /// u   y   x
    for (int i = 0; i < MAXL; ++i) {
        int upcount;
        upcount = 1 << i;
        int y = stack_top >= upcount ? stk[stack_top - upcount] : 0;
        upcount = 2 << i;
        int x = stack_top >= upcount ? stk[stack_top - upcount] : 0;

        // u->y
        int sum1 = sum[i][u] - sum[i][y];
        // y->x
        int sum2 = (depth[y] - depth[x]) - (sum[i][y] - sum[i][x]);
        // x->root
        int sum3 = psum[i][x];
        psum[i][u] = sum1 + sum2 + sum3;
        // dbg("psum[%d][%d] = %d + %d + %d = %d, x=%d, y=%d\n", i, u, sum1,
        // sum2, sum3,
        //     psum[i][u], x, y);
    }
    // dbg("\n");

    stk[stack_top++] = u;

    for (int v : adj[u])
        dfs3(v);

    stk[--stack_top] = 0;
}

int lca(int u, int v)
{
    dbg("lca(%d,%d)", u, v);
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            swap(u, v);
        }
        u = parent[top[u]];
    }
    int ans = depth[u] < depth[v] ? u : v;
    dbg(" = %d\n", ans);
    return ans;
}

int ancester(int u, int k)
{
    int target_depth = depth[u] - k;
    if (target_depth < 1) {
        return 0;
    }
    while (depth[top[u]] > target_depth) {
        u = parent[top[u]];
    }
    int step = depth[u] - target_depth;
    return seq[in[u] - step];
}

int calc(int u, int offset, int level)
{
    dbg("calc(%d,%d,%d) = ", u, offset, level);
    /// 000011110000   level=2
    ///   u
    ///   offset
    int cycle = 2 << level;
    int half = 1 << level;
    offset = (offset % cycle + cycle) % cycle;

    int ans = 0;
    if (offset < half) {
        int v = ancester(u, half - offset);
        int sum1 = sum[level][u] - sum[level][v];
        ans += sum1;

        offset = half;
        u = v;
    }

    int v = ancester(u, cycle - offset);
    int sum2 = (depth[u] - depth[v]) - (sum[level][u] - sum[level][v]);

    int sum3 = psum[level][v];

    dbg("%d + %d + %d = %d\n", ans, sum2, sum3, ans + sum2 + sum3);
    ans += sum2 + sum3;
    return ans;
}

ll getResult(int x, int y)
{
    int z = lca(x, y);

    ll ans = 0;
    for (int i = 0; i < MAXL; i++) {
        ll base = 1 << i;
        ll count = 0;

        // x ---- z ---- y
        //    l1     l2

        int l1 = depth[x] - depth[z];
        int l2 = depth[y] - depth[z];
        count += calc(x, 0, i);
        count -= calc(parent[z], l1 + 1, i);

        // 0000111100001111
        //      ^^

        // i = 2
        int cycle = 2 << i; // 8
        int half = 1 << i;  // 4
        int trans = (l1 + l2) % cycle;
        // 0--3, 1--2,   4--7, 5--6
        trans = trans < half ? half - trans - 1 : cycle - trans + half - 1;

        count += calc(y, trans, i);
        count -= calc(z, l2 + trans, i);

        dbg("level=%d count=%lld\n", i, count);
        ans += base * count;
    }
    return ans;
}

void solve()
{
    dfs(root, 0, 1); // assuming node 1 is the root
    dfs2(root, root);
    dfs3(root);
    for (int i = 1; i <= n; i++) {
        dbg("top[%d] = %d\n", i, top[i]);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%lld\n", getResult(x, y));
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        reset();
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        solve();
    }

    return 0;
}
