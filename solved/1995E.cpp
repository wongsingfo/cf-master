#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...) __VA_ARGS__
#endif

int solve0(vector<int> a)
{
    int n = a.size() / 2;

    int max_desk = -1;
    int min_desk = 2e9 + 1;

    for (int i = 0; i < n / 2; i++) {
        int x = a[i * 2], y = a[i * 2 + 1];
        int p = a[i * 2 + n], q = a[i * 2 + n + 1];

        int sol0 = min(x + y, p + q);
        int sol1 = min(x + q, p + y);

        if (sol0 >= sol1) {
            // choose sol0
            max_desk = max(max_desk, max(x + y, p + q));
            min_desk = min(min_desk, sol0);
        } else {
            max_desk = max(max_desk, max(x + q, p + y));
            min_desk = min(min_desk, sol1);
        }
    }

    dbg(min_desk, max_desk);
    return max_desk - min_desk;
}

using State = array<array<int, 2>, 2>;

State merge(State a, State b)
{
    State result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = (a[i][0] && b[0][j]) || (a[i][1] && b[1][j]);
        }
    }
    return result;
}

struct Node
{
    Node *s[2];
    int left, right;
    State state;
};

Node *current_node;
Node nodes[1 << 18];

Node *build(int l, int r)
{
    Node *ret = current_node++;
    *ret = {{}, l, r, {}};
    if (l == r) {
        return ret;
    }

    int m = (l + r) / 2;
    ret->s[0] = build(l, m);
    ret->s[1] = build(m + 1, r);
    return ret;
}

void modify(Node *node, int i, int s0, int s1, int value)
{
    if (node->left == node->right) {
        assert(node->left == i);
        node->state[s0][s1] = value;
        return;
    }
    if (i <= node->s[0]->right) {
        modify(node->s[0], i, s0, s1, value);
    } else {
        modify(node->s[1], i, s0, s1, value);
    }
    node->state = merge(node->s[0]->state, node->s[1]->state);
}

int solve1(vector<int> a)
{
    vector<pair<int, int>> desk;
    int n = a.size() / 2;
    for (int i = 0, x = 0; i < n; i++) {
        int y = x ^ 1;
        desk.push_back(make_pair(a[x], a[y]));
        x = (y + n) % (2 * n);
    }

    dbg(desk);

    struct Event
    {
        int desk_idx;
        int swap0, swap1;
        int sum;
    };
    vector<Event> events;
    for (int i = 0; i < n; i++) {
        for (int s0 = 0; s0 < 2; s0++)
            for (int s1 = 0; s1 < 2; s1++) {
                int elem0 = s0 ? desk[(i - 1 + n) % n].second : desk[i].first;
                int elem1 = s1 ? desk[(i + 1) % n].first : desk[i].second;
                events.push_back({i, s0, s1, elem0 + elem1});
            }
    }

    sort(events.begin(), events.end(),
         [](const Event &a, const Event &b) { return a.sum < b.sum; });

    dbg(events);

    current_node = nodes;
    Node *root = build(0, n-1);
    int ans = 2e9 + 1;
    for (size_t i = 0, j = 0; i < events.size(); i++) {
        dbg(i);
        while (true) {
            bool ok = root->state[0][0] || root->state[1][1];
            if (ok) {
                int new_ans = events[j-1].sum - events[i].sum;
                dbg(i, j, new_ans, events[i], events[j-1]);
                ans = min(ans, new_ans);
                break;
            }

            if (j == events.size())
                break;
            auto &e = events[j];
            dbg(100, e);
            modify(root, e.desk_idx, e.swap0, e.swap1, true);
            j += 1;
        }

        auto &e = events[i];
        dbg(-99, e);
        modify(root, e.desk_idx, e.swap0, e.swap1, false);
    }

    return ans;
}

void solve()
{
    int n;
    cin >> n;
    dbg(n);
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i];
    }

    int ans;
    if (n % 2 == 0) {
        ans = solve0(a);
    } else {
        ans = solve1(a);
    }

    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
