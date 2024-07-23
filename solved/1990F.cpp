#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

#ifdef DBG
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

const i64 INF = 1e18;

vector<i64> a;
int n, q;

struct InfoEnd
{
    int index;
    i64 max;
    i64 sum;
    int limit; // a[limit] >= sum
};

struct Info
{
    int answer;
    vector<InfoEnd> left_end, right_end;
};

Info new_info(int index)
{
    auto left_end1 = InfoEnd{
        .index = index,
        .max = a[index],
        .sum = a[index],
        .limit = index + 1,
    };
    auto right_end1 = left_end1;
    right_end1.limit = index - 1;

    return Info{
        .answer = -1,
        .left_end = {{left_end1}},
        .right_end = {{right_end1}},
    };
};

vector<InfoEnd> merge_ends(const vector<InfoEnd> &a, const vector<InfoEnd> &b)
{
    vector<InfoEnd> result = a;
    auto &back = result.back();
    auto left_sum = back.sum;
    auto left_max = back.max;
    if (::a[back.limit] < back.sum) {
        result.pop_back();
    }

    for (size_t i = 0; i < b.size(); i++) {
        auto elem = b[i];
        elem.max = max(elem.max, left_max);
        elem.sum += left_sum;

        if (i + 1 == b.size() || ::a[elem.limit] >= elem.sum) {
            result.push_back(elem);
        }
    }

    return result;
}

int merge_span(const vector<InfoEnd> &a, const vector<InfoEnd> &b)
{

    int n = a.size(), m = b.size();
    int i = 0, j = 0;
    int answer = -1;

    while (i < n && j < m) {
        int length = b[j].index - a[i].index + 1;
        i64 max = std::max(a[i].max, b[j].max);
        i64 sum = a[i].sum + b[j].sum;

        if (length >= 3 && max * 2 < sum) {
            answer = std::max(answer, length);
        }

        bool addi = (j + 1 == m) || (i + 1 < n && a[i + 1].max <= b[j + 1].max);

        if (addi)
            i += 1;
        else
            j += 1;
    }
    return answer;
}

Info merge(const Info &l, const Info &r)
{
    int ans = max(l.answer, r.answer);
    ans = max(ans, merge_span(l.right_end, r.left_end));

    Info result;
    result.answer = ans;
    result.left_end = merge_ends(l.left_end, r.left_end);
    result.right_end = merge_ends(r.right_end, l.right_end);
    return result;
}

struct Node
{
    Node *s[2];
    int left, right;
    Info info;
};

Node nodes[1 << 19];
Node *nodes_current;

Node *build(int l, int r)
{
    Node *node = nodes_current++;
    node->s[0] = node->s[1] = nullptr;
    node->left = l;
    node->right = r;
    if (l == r) {
        node->info = new_info(l);
        return node;
    }
    int m = (l + r) / 2;
    node->s[0] = build(l, m);
    node->s[1] = build(m + 1, r);
    node->info = merge(node->s[0]->info, node->s[1]->info);
    return node;
}

void modify(Node *node, int p)
{
    if (node->left == node->right) {
        assert(node->left == p);
        node->info = new_info(p);
        return;
    }
    if (p <= node->s[0]->right) {
        modify(node->s[0], p);
    } else {
        modify(node->s[1], p);
    }
    node->info = merge(node->s[0]->info, node->s[1]->info);
}

Info query(Node *node, int l, int r)
{
    if (l <= node->left && r >= node->right) {
        return node->info;
    }

    if (l > node->s[0]->right)
        return query(node->s[1], l, r);
    if (r <= node->s[0]->right)
        return query(node->s[0], l, r);

    auto left = query(node->s[0], l, r);
    auto right = query(node->s[1], l, r);
    return merge(left, right);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        nodes_current = nodes;

        scanf("%d %d", &n, &q);
        a.resize(n + 2); // Using one-indexing
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
        }
        a[0] = INF;
        a[n + 1] = INF;

        Node *root = build(1, n);
        while (q--) {
            int type;
            dbg("--------------\n");
            scanf("%d", &type);
            if (type == 1) {
                int l, r;
                scanf("%d %d", &l, &r);
                auto ans = query(root, l, r);
                auto answer = ans.answer;
                printf("%d\n", answer);
            } else if (type == 2) {
                int i;
                i64 x;
                scanf("%d %lld", &i, &x);
                a[i] = x;
                modify(root, i);
            }
        }
    }
    return 0;
}
