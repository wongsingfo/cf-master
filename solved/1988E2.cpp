#include <bits/stdc++.h>
using ll = long long;
using namespace std;

#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

const int MAXN = 500005; // Adjust size based on problem constraints

vector<int> a;

void solve(int n)
{
    // Implement the solution for one test case based on the global variable
    // `a`. Example: vector<int> result(n, 0); Process `a` and fill `result`
    // accordingly and print results using 'printf'.

    // increasing elements index, each of which is looking for a smaller element
    vector<int> stk1, stk2;

    auto doit = [&](int i, vector<int> &ans1, vector<int> &ans2) {
        vector<int> to_remove;
        while (!stk1.empty() && a[i] < a[stk1.back()]) {
            int j = stk1.back();
            ans1[j] = i;
            to_remove.push_back(j);
            stk1.pop_back();
        }
        while (!stk2.empty() && a[i] < a[stk2.back()]) {
            int j = stk2.back();
            ans2[j] = i;
            stk2.pop_back();
        }
        stk1.push_back(i);
        stk2.insert(stk2.end(), to_remove.rbegin(), to_remove.rend());
    };

    vector<int> right_min1(n + 1, n + 1);
    vector<int> right_min2(n + 1, n + 1);
    for (int i = 1; i <= n; i++) {
        doit(i, right_min1, right_min2);
    }

    vector<int> left_min1(n + 1, 0);
    vector<int> left_min2(n + 1, 0);
    stk1.clear();
    stk2.clear();
    for (int i = n; i >= 1; i--) {
        doit(i, left_min1, left_min2);
    }

    for (int i = 1; i <= n; i++) {
        dbg("i = %d, right_min = (%d, %d), left_min = (%d, %d)\n", i,
            right_min1[i], right_min2[i], left_min1[i], left_min2[i]);
    }

    vector<ll> ans(n + 2, 0);

    //   A     B      C      D
    // ......L.....i......R........
    for (int i = 1; i <= n; i++) {
        auto add = [&ans, &i](int left, int right, ll v) {
            if (left > right)
                return;
            ll value = v * a[i];
            dbg("add %d %d count=%lld value=%lld\n", left, right, v, value);
            ans[left] += value;
            ans[right + 1] -= value;
        };

        dbg("i = %d\n", i);
        int L = left_min1[i], R = right_min1[i];
        ll Lc = i - L - 1;
        ll Rc = R - i - 1;

        // A, D
        {
            ll v = (Lc + 1) * (Rc + 1);
            add(0, L - 1, v);
            add(R + 1, n, v);
        }
        // B
        {
            ll v = Lc * (Rc + 1);
            add(L + 1, i - 1, v);
        }
        // C
        {
            ll v = (Lc + 1) * Rc;
            add(i + 1, R - 1, v);
        }

        // L
        int LL = left_min2[i], RR = right_min2[i];
        // ..LL...L.....i......R........
        if (L >= 1) {
            ll Lc = i - LL - 2;
            ll v = (Lc + 1) * (Rc + 1);
            add(L, L, v);
        }

        // R
        if (R <= n) {
            ll Rc = RR - i - 2;
            ll v = (Lc + 1) * (Rc + 1);
            add(R, R, v);
        }
    }

    for (int i = 1; i <= n; i++)
        ans[i] += ans[i - 1];
    for (int i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        dbg("n = %d\n", n);

        a.resize(n + 1); // Resize to n+1 to keep 1-based indexing
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        solve(n);
    }
    return 0;
}
