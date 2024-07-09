#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXN = 1000005;
const int MOD = 1e9 + 7; // Define MOD if the problem requires modular
                         // arithmetic, otherwise ignore

// Debugging function
void dbg(const char *fmt, ...)
{
#ifdef DBG
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
#endif
}
int p[MAXN];

void init_p()
{
    int n = MAXN;
    for (int i = 2; i < n; i++) {
        if (p[i] == 0) {
            p[i] = i;
        }
        for (int j = 0; j < n; j += i) {
            if (p[j] == 0)
                p[j] = i;
        }
    }

    for (int i = 0; i < 25; i++) {
        dbg("p[%d] = %d\n", i, p[i]);
    }
}

vector<int> factorize(int x)
{
    vector<int> ret;
    while (x != 1) {
        int xp = p[x];
        ret.push_back(p[x]);
        while (x % xp == 0)
            x /= xp;
    }
    return ret;
}

// Global variables
int t, n, k;
vector<int> a;

// sdu

int fa[MAXN * 2];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int x, int y)
{
    dbg("merge %d %d\n", x, y);
    fa[find(x)] = find(y);
}

// Function to clear global input data
void clearData() { a.clear(); }

// Function to solve each test case
void solve()
{
    // Placeholder for the main logic of the solution.
    // Access input using global variables n, k, and a.

    for (int i = 0; i < n * 2; ++i) {
        fa[i] = i;
    }

    map<int, int> prev;
    for (int i = 1; i < n * 2; i++) {
        auto factors = factorize(a[i % n]);

        for (auto fac : factors) {
            if (prev.find(fac) == prev.end()) {
                prev[fac] = i;
                continue;
            }

            if (i - prev[fac] <= k) {
                merge(i, prev[fac]);
            }

            prev[fac] = i;
        }
    }

    ll ans = 0;
    for (int i = 1; i < n * 2; i++) {
        if (a[i % n] == 1) {
            dbg("found 1 at %d\n", i);
            if (i <= n)
                ans += n;
        } else if (find(i) == i) {
            dbg("found root at %d\n", i);
            ans++;
        }
    }

    printf("%lld\n", ans);
}

int main()
{
    init_p();
    scanf("%d", &t);
    for (int test_case = 0; test_case < t; ++test_case) {
        // Read input for each test case
        scanf("%d %d", &n, &k);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }

        // Solve the test case
        solve();

        // Clear input data for the next test case
        clearData();
    }
    return 0;
}
