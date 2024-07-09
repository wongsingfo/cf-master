#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

const int MAXN = 100005;
const ll MOD = 1e9 + 7; // Ignore if not needed

int n;
ll k;
vector<int> a;

struct Node
{
    int maxl;
    Node *s[2];

    void update_maxl()
    {
        if (s[0] != nullptr) {
            maxl = max(maxl, s[0]->maxl);
        }
        if (s[1] != nullptr) {
            maxl = max(maxl, s[1]->maxl);
        }
    }
};

Node node_pool[MAXN * 32];
Node *node_pool_ptr;

Node *new_node()
{
    node_pool_ptr->maxl = -1;
    node_pool_ptr->s[0] = node_pool_ptr->s[1] = nullptr;
    return node_pool_ptr++;
}

void insert(Node *root, int index, int nbit)
{
    if (nbit < 0) {
        root->maxl = index;
        return;
    }
    int value = a[index];
    int c = (value >> nbit) & 1;
    if (root->s[c] == nullptr) {
        root->s[c] = new_node();
    }
    insert(root->s[c], index, nbit - 1);
    root->update_maxl();
}

int query(Node *root, int upper, int value, int nbit)
{
    if (root == nullptr) {
        return -1;
    }
    if (nbit < 0) {
        return root->maxl;
    }
    int c_upper = (upper >> nbit) & 1;
    int c_value = (value >> nbit) & 1;

    if (c_upper == 1) {
        int ret = root->s[c_value] == nullptr ? -1 : root->s[c_value]->maxl;
        ret = max(ret, query(root->s[c_value ^ 1], upper, value, nbit - 1));
        return ret;
    }

    return query(root->s[c_value], upper, value, nbit - 1);
}

// void free_node(Node *root)
// {
//     if (root == nullptr)
//         return;
//     free_node(root->s[0]);
//     free_node(root->s[1]);
//
//     delete root;
// }

/// count ranges with ans <= upper
ll solve0(int upper)
{
    ll ret = 0;
    node_pool_ptr = node_pool;
    Node *root = new_node();
    int maxl = -1;
    for (int i = 0; i < n; i++) {
        maxl = max(maxl, query(root, upper, a[i], 30));
        // dbg(" i = %d, maxl = %d\n", i, maxl);
        ret += maxl + 1;
        insert(root, i, 30);
    }
    dbg("upper = %d, ret = %lld\n", upper, ret);
    // free_node(root);
    return ret;
}

void solve()
{
    // int low = -1, high = 128;
    ll low = -1, high = 2e9;
    while (low + 1 < high) {
        ll mid = (low + high) / 2;
        ll cnt = solve0(mid);

        if (cnt < k) {
            low = mid;
        } else {
            high = mid;
        }
    }
    printf("%lld\n", high);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%lld", &n, &k);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        solve();
        a.clear();
    }
    return 0;
}
