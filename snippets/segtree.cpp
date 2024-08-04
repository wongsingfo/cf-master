/* Snippet Header */

#include <bits/stdc++.h>
using namespace std;

/* Snippet BEGIN */
struct MinLazy
{
    int lazy;
    void clear() { lazy = 0; }
    void apply(const MinLazy &other) { lazy += other.lazy; }
};

struct MinInfo
{
    int min = 0;
    int min_count = 0;

    MinInfo merge(const MinInfo &other) const
    {
        auto &self = *this;
        MinInfo ret{
            std::min(self.min, other.min),
            0,
        };
        if (self.min == ret.min)
            ret.min_count += self.min_count;
        if (other.min == ret.min)
            ret.min_count += other.min_count;
        return ret;
    }

    void apply(const MinLazy &lazy) { min += lazy.lazy; }

    int countZeros()
    {
        assert(min >= 0);
        return min == 0 ? min_count : 0;
    }
};

template <typename Info, typename Lazy> class SegmentTree
{
  public:
    void init(int l, int r, std::function<Info(int)> map)
    {
        auto n_ = r - l + 1;
        root_l = l;
        root_r = r;
        nodes.assign(4 << std::__lg(n_), Node());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            nodes[p].lazy.clear();
            if (l == r) {
                nodes[p].info = map(l);
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, l, r);
    }

    void modify(int p, const Lazy &v) { modify(1, root_l, root_r, p, p, v); }

    void modify(int l, int r, const Lazy &v)
    {
        if (l > r) return;
        assert(l <= r);
        assert(l >= root_l && r <= root_r);
        modify(1, root_l, root_r, l, r, v);
    }

    Info rangeQuery() { return rangeQuery(1, root_l, root_r, root_l, root_r); }

    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, root_l, root_r, l, r);
    }

  private:
    int root_l, root_r;
    struct Node
    {
        Info info;
        Lazy lazy;
    };
    std::vector<Node> nodes;

    void pull(int p)
    {
        nodes[p].info = nodes[2 * p].info.merge(nodes[2 * p + 1].info);
    }

    void push(int p)
    {
        auto lazy = nodes[p].lazy;
        nodes[2 * p].lazy.apply(lazy);
        nodes[2 * p].info.apply(lazy);
        nodes[2 * p + 1].lazy.apply(lazy);
        nodes[2 * p + 1].info.apply(lazy);
        nodes[p].lazy.clear();
    }

    void modify(int p, int l, int r, int x, int y, const Lazy &v)
    {
        if (l >= x && r <= y) {
            nodes[p].info.apply(v);
            nodes[p].lazy.apply(v);
            return;
        }
        push(p);
        int m = (l + r) / 2;
        if (m >= x) {
            modify(2 * p, l, m, x, y, v);
        }
        if (m + 1 <= y) {
            modify(2 * p + 1, m + 1, r, x, y, v);
        }
        pull(p);
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= x && r <= y) {
            return nodes[p].info;
        }
        push(p);
        int m = (l + r) / 2;

        bool qleft = m >= x;
        bool qright = m + 1 <= y;
        assert(qleft || qright);
        if (qleft && qright) {
            auto left = rangeQuery(2 * p, l, m, x, y);
            auto right = rangeQuery(2 * p + 1, m + 1, r, x, y);
            return left.merge(right);
        }

        if (qleft) {
            return rangeQuery(2 * p, l, m, x, y);
        } else {
            return rangeQuery(2 * p + 1, m + 1, r, x, y);
        }
    }
};

int segtree_example()
{
    SegmentTree<MinInfo, MinLazy> s;
    int n = 10;
    s.init(1, n, []([[maybe_unused]] int i) { return MinInfo{0, 1}; });
    cout << s.rangeQuery().countZeros() << endl;
    cout << s.rangeQuery(2, 5).countZeros() << endl;
    s.modify(2, 6, {1});
    cout << s.rangeQuery().countZeros() << endl;
    s.modify(3, 4, {-1});
    cout << s.rangeQuery().countZeros() << endl;

    return 0;
}

/* Snippet END */
