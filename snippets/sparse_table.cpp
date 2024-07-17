/* Snippet Header */

#include <bits/stdc++.h>

/* Snippet BEGIN */
template <typename T, T (*op)(T, T)> class SparseTable
{
  public:
    void init(const std::vector<T> &a)
    {
        this->n = a.size();
        int maxLog = std::log2(n) + 1;
        st.resize(n, std::vector<T>(maxLog, 0));
        log.resize(n + 1, 0);

        // Precompute the logarithms
        for (int i = 2; i <= n; ++i) {
            log[i] = log[i / 2] + 1;
        }

        // Initialize sparse table with input array values
        for (int i = 0; i < n; ++i) {
            st[i][0] = a[i];
        }

        // Build the sparse table
        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; (i + (1 << j) - 1) < n; ++i) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r)
    {
        int j = log[r - l + 1];
        return op(st[l][j], st[r - (1 << j) + 1][j]);
    }

  private:
    int n;
    std::vector<std::vector<T>> st;
    std::vector<int> log;
};

template <typename T> T minOp(T a, T b) { return std::min(a, b); }
template <typename T> T maxOp(T a, T b) { return std::max(a, b); }

void sparse_table_example()
{
    int n = 6;
    std::vector<int> a = {6, 13, 34, 1, 2, 6};

    // For max query
    SparseTable<int, maxOp> st_max;
    st_max.init(a);
    assert(st_max.query(1, 4) == 34);

    // For min query
    SparseTable<int, minOp> st_min;
    st_min.init(a);
    assert(st_min.query(1, 4) == 1);
}

/* Snippet END */
