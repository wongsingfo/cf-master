#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

const int MAXN = 200005; // Adjust as needed

// Global variables to store input data
vector<string> test_cases;

void reset_globals() {
    // Clear or reset global data
    test_cases.clear();
}

vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    z[0] = n;

    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

ll count_nonempty_strings(const string &s) {

    int n = s.length();
    vector<int> to_not_a(n);

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'a') {
            to_not_a[i] = i + 1 < n ? to_not_a[i + 1] : n;
        } else {
            to_not_a[i] = i;
        }
    }

    if (to_not_a[0] == n) {
        dbg("all a\n");
        return n - 1;
    }

    int i0 = to_not_a[0];
    string s0 = s.substr(i0);
    auto z = z_function(s0);

    // print s0 and z
    dbg("s0: %s\n", s0.c_str());
    dbg("z.size()=%d\n", z.size());
    for (int i = 0; i < z.size(); i++) {
        dbg("z[%d]=%d\n", i, z[i]);
    }

    ll ans = 0;
    for (int len = 1; i0 + len <= n; len++) {
        int to_left_a = i0;

        int i = i0;
        bool check = true;
        while (true) {
            if (to_not_a[i] == n) {
                break;
            }

            if (z[i - i0] < len) {
                check = false;
                break;
            }

            assert(i + len <= n);
            if (i + len == n) {
                break;
            }

            int j = to_not_a[i + len];
            if (j == n) {
                break;
            }

            to_left_a = min(to_left_a, j - (i + len));
            i = j;
        }

        if (check) {
            ans += to_left_a + 1;
        }
    }

    return ans;
}

void solve() {
    for (const string &s : test_cases) {
        printf("%lld\n", count_nonempty_strings(s));
    }
}

int main() {
    int t;
    scanf("%d", &t); // Read number of test cases
    test_cases.resize(t);

    for (int i = 0; i < t; ++i) {
        char buffer[MAXN];
        scanf("%s", buffer);
        test_cases[i] = string(buffer);
    }

    solve();
    reset_globals();

    return 0;
}
