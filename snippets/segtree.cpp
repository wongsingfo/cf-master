/* Snippet Header */

#include <bits/stdc++.h>
using namespace std;

/* Snippet BEGIN */

struct NullLazy
{
    void clear() {}
    void apply(const NullLazy &) {}
};

template <typename Info, typename Lazy = NullLazy> class SegmentTree
{
  public:
    void init(
        int l, int r, std::function<Info(int)> map = [](int) { return Info(); })
    {
        auto n_ = r - l + 1;
        root_l = l;
        root_r = r;
        nodes.assign(4 << std::__lg(n_), Node());

        auto build = [&](int p, int l, int r, auto &&self) -> void {
            nodes[p].lazy.clear();
            if (l == r) {
                nodes[p].info = map(l);
                return;
            }
            int m = l + (r - l) / 2;
            self(2 * p, l, m, self);
            self(2 * p + 1, m + 1, r, self);
            pull(p);
        };

        build(1, l, r, build);
    }

    void modify(int p, const Info &v) { modify(1, root_l, root_r, p, v); }

    void modify(int p, const Lazy &v) { modify(1, root_l, root_r, p, p, v); }

    void modify(int l, int r, const Lazy &v)
    {
        if (l > r)
            return;
        assert(l <= r);
        assert(l >= root_l && r <= root_r);
        modify(1, root_l, root_r, l, r, v);
    }

    Info range_query()
    {
        return range_query(1, root_l, root_r, root_l, root_r);
    }

    Info range_query(int l, int r)
    {
        assert(l <= r);
        return range_query(1, root_l, root_r, l, r);
    }

    static constexpr int NOT_FOUND = INT_MIN;

    template <class F>
        requires std::predicate<F, Info>
    int find_first_idx(int x, int y, F &&pred)
    {
        return find_idx<true>(1, root_l, root_r, x, y, std::forward<F>(pred));
    }
    template <class F>
        requires std::predicate<F, Info>
    int find_last_idx(int x, int y, F &&pred)
    {
        return find_idx<false>(1, root_l, root_r, x, y, std::forward<F>(pred));
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
        int m = l + (r - l) / 2;
        if (m >= x) {
            modify(2 * p, l, m, x, y, v);
        }
        if (m + 1 <= y) {
            modify(2 * p + 1, m + 1, r, x, y, v);
        }
        pull(p);
    }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (l == r) {
            nodes[p].info = v;
            return;
        }
        int m = l + (r - l) / 2;
        if (x <= m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }

    Info range_query(int p, int l, int r, int x, int y)
    {
        if (l >= x && r <= y) {
            return nodes[p].info;
        }
        push(p);
        int m = l + (r - l) / 2;

        bool qleft = m >= x;
        bool qright = m + 1 <= y;
        assert(qleft || qright);
        if (qleft && qright) {
            auto left = range_query(2 * p, l, m, x, y);
            auto right = range_query(2 * p + 1, m + 1, r, x, y);
            return left.merge(right);
        }

        if (qleft) {
            return range_query(2 * p, l, m, x, y);
        } else {
            return range_query(2 * p + 1, m + 1, r, x, y);
        }
    }

    template <bool Forward, class F>
        requires std::predicate<F, Info>
    int find_idx(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l > y || r < x) {
            return NOT_FOUND;
        }
        if (l >= x && r <= y && !pred(nodes[p].info)) {
            return NOT_FOUND;
        }
        if (l == r) {
            return l;
        }
        int m = l + (r - l) / 2;
        int res = NOT_FOUND;
        if constexpr (Forward) {
            res = find_idx<Forward>(2 * p, l, m, x, y, pred);
            if (res == NOT_FOUND) {
                res = find_idx<Forward>(2 * p + 1, m + 1, r, x, y, pred);
            }
        } else {
            res = find_idx<Forward>(2 * p + 1, m + 1, r, x, y, pred);
            if (res == NOT_FOUND) {
                res = find_idx<Forward>(2 * p, l, m, x, y, pred);
            }
        }
        return res;
    }
};

struct AddLazy
{
    int lazy;
    void clear() { lazy = 0; }
    void apply(const AddLazy &other) { lazy += other.lazy; }
};

struct MinCountInfo
{
    int min = 0;
    int min_count = 0;

    MinCountInfo merge(const MinCountInfo &other) const
    {
        auto &self = *this;
        MinCountInfo ret{
            std::min(self.min, other.min),
            0,
        };
        if (self.min == ret.min)
            ret.min_count += self.min_count;
        if (other.min == ret.min)
            ret.min_count += other.min_count;
        return ret;
    }

    void apply(const AddLazy &lazy) { min += lazy.lazy; }

    int count_zeros()
    {
        assert(min >= 0);
        return min == 0 ? min_count : 0;
    }
};

template <typename T, typename Comparator = std::less<T>> struct CmpInfo
{
    T value;

    CmpInfo merge(const CmpInfo &other) const
    {
        // Return the max value like a priority queue
        if (Comparator()(value, other.value))
            return other;
        return *this;
    }

    void apply(const NullLazy &) {}
};

int segtree_example()
{
    {
        SegmentTree<MinCountInfo, AddLazy> s;
        int n = 10;
        s.init(1, n, []([[maybe_unused]] int i) { return MinCountInfo{0, 1}; });
        cout << s.range_query().count_zeros() << endl;
        cout << s.range_query(2, 5).count_zeros() << endl;
        s.modify(2, 6, {1});
        cout << s.range_query().count_zeros() << endl;
        s.modify(3, 4, {-1});
        cout << s.range_query().count_zeros() << endl;
    }

    {
        SegmentTree<CmpInfo<int>> s;
        s.init(-5, 5);
        s.modify(-2, CmpInfo{3});
        assert(s.find_first_idx(
                   -4, 0, [](CmpInfo<int> x) { return x.value >= 3; }) == -2);
        assert(s.find_first_idx(-4, -3, [](CmpInfo<int> x) {
            return x.value >= 3;
        }) == s.NOT_FOUND);
    }

    return 0;
}

/* Snippet END */
