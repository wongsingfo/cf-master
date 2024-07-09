#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXN = 2005;
const int MOD = 998244353;

int t, n, m;
string s;
ll b[MAXN];

#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

// Function to reset the global variables for each test case
void reset_globals() {
    // Resetting the array `b` by setting each element to zero.
    fill(b, b + n + 2, 0);
}

// Function to solve the problem for each test case
int solve() {
    // Implement the solve function logic here
    // This is a placeholder return value

    set<ll> possible_sums;
    for (int i = 0; i <= n; i++) {
        possible_sums.insert(b[i] + b[i + 1]);
    }

    ll ans = 0;

    for (auto sum : possible_sums) {

        dbg("sum = %lld\n", sum);

        static ll f_prefix[MAXN];
        static ll f_suffix[MAXN];

        f_prefix[0] = 1;
        f_suffix[0] = 0;

        for (int i = 1; i <= n + 1; i++) {
            bool can_PP = true;
            can_PP &= s[i] != 'S';
            can_PP &= s[i - 1] != 'S';
            can_PP &= abs(b[i] - b[i - 1]) <= m;

            bool can_SP = true;
            can_SP &= s[i] != 'S';
            can_SP &= s[i - 1] != 'P';
            can_SP &= abs(b[i] + b[i - 1] - sum) <= 2 * m;

            bool can_SS = true;
            can_SS &= s[i] != 'P';
            can_SS &= s[i - 1] != 'P';
            can_SS &= abs(b[i - 1] - b[i]) <= m;

            bool can_PS = true;
            can_PS &= s[i] != 'P';
            can_PS &= s[i - 1] != 'S';
            can_PS &= b[i - 1] + b[i] == sum;

            dbg("can_PP = %d, can_SP = %d, can_SS = %d, can_PS = %d\n", can_PP,
                can_SP, can_SS, can_PS);

            f_prefix[i] =
                (can_PP * f_prefix[i - 1] + can_SP * f_suffix[i - 1]) % MOD;
            f_suffix[i] =
                (can_PS * f_prefix[i - 1] + can_SS * f_suffix[i - 1]) % MOD;

            dbg("f_prefix[%d] = %lld, f_suffix[%d] = %lld\n", i, f_prefix[i], i,
                f_suffix[i]);
        }

        auto cc = (f_prefix[n + 1] + f_suffix[n + 1]) % MOD;
        dbg("cc = %lld\n", cc);
        ans = (ans + cc) % MOD;
    }

    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        // Read inputs
        scanf("%d %d", &n, &m);
        cin >> s;
        s = "P" + s + "S";
        dbg("s = %s\n", s.c_str());
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &b[i]);
        }
        b[0] = b[n + 1] = 0;

        // Reset global variables before processing a new test case
        // reset_globals();

        // Call the solve function and print the result
        int result = solve();
        printf("%d\n", result);
    }
    return 0;
}

