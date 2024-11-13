/* Snippet Header */

#include <bits/stdc++.h>
using namespace std;

/* Snippet BEGIN */

struct NullLazy
{
    void clear() {}
    void apply(const NullLazy &) {}
};

template <typename Info, typename Lazy = NullLazy>
    requires requires(Info info, Lazy lazy) {
        { info.merge(info) } -> std::convertible_to<Info>;
        { info.apply(lazy) };
        { lazy.clear() };
        { lazy.apply(lazy) };
    }
class SegmentTree
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

    void modify(int p, const Info &v)
    {
        assert(p >= root_l && p <= root_r);
        modify(1, root_l, root_r, p, p, v);
    }

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

    template <typename U>
    void modify(int p, int l, int r, int x, int y, const U &v)
    {
        if constexpr (std::is_same_v<U, Lazy>) {
            if (l >= x && r <= y) {
                nodes[p].info.apply(v);
                nodes[p].lazy.apply(v);
                return;
            }
        } else {
            static_assert(std::is_same_v<U, Info>);
            if (l == r) {
                nodes[p].info = v;
                return;
            }
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
    struct Lazy
    {
        T lazy;
        void clear()
        {
            if (Comparator()(std::numeric_limits<T>::lowest(),
                             std::numeric_limits<T>::max())) {
                lazy = std::numeric_limits<T>::lowest();
            } else {
                lazy = std::numeric_limits<T>::max();
            }
        }
        void apply(const Lazy &other)
        {
            if (Comparator()(lazy, other.lazy)) {
                lazy = other.lazy;
            }
        }
    };

    T value;

    CmpInfo() = default;

    CmpInfo(const T &v) : value(v) {}

    CmpInfo merge(const CmpInfo &other) const
    {
        // Return the max value like a priority queue
        if (Comparator()(value, other.value))
            return other;
        return *this;
    }

    void apply(const Lazy &lazy)
    {
        if (Comparator()(value, lazy.lazy)) {
            value = lazy.lazy;
        }
    }

    void apply(const NullLazy &) {}
};

int segtree_example()
{
    {
        /// Support the following operations:
        ///   1. Add/Minus X for A[i], A[i+1], ..., A[j]
        ///   2. Query how many zeros in A[i], A[i+1], ..., A[j]
        SegmentTree<MinCountInfo, AddLazy> s;
        int n = 10;
        s.init(1, n, [](int) { return MinCountInfo{0, 1}; });
        assert(s.range_query().count_zeros() == 10);
        assert(s.range_query(2, 5).count_zeros() == 4);
        s.modify(2, 6, {1});
        assert(s.range_query().count_zeros() == 5);
        s.modify(3, 4, {-1});
        assert(s.range_query().count_zeros() == 7);
        s.modify(4, MinCountInfo{1, 1});
        assert(s.range_query().count_zeros() == 6);
    }

    {
        /// Support the following operations:
        ///   1. Query the maximum number in A[i], ... A[j]
        ///   2. Let A[i] = X
        ///   3. Let A[i] = max(A[i], X) for all i in [left, right]
        using C = CmpInfo<int, less<>>;
        SegmentTree<C, C::Lazy> s;
        s.init(-5, 5);
        s.modify(-2, 3);
        s.modify(-1, 0, C::Lazy{4});

        assert(s.find_first_idx(-4, 0, [](auto x) { return x.value >= 4; }) ==
               -1);
        assert(s.find_first_idx(-4, 0, [](auto x) { return x.value >= 3; }) ==
               -2);
        assert(s.find_first_idx(-4, -3, [](auto x) { return x.value >= 3; }) ==
               s.NOT_FOUND);
    }

    return 0;
}

/* Snippet END */
