/* Snippet Header */
#include <bits/stdc++.h>

/* Snippet BEGIN */
template <class T> class FenwickTree
{
  public:
    FenwickTree(int size) : size(size) { tree.resize(size + 1, 0); }

    void update(int index, T value)
    {
        for (; index <= size; index += index & -index) {
            tree[index] += value;
        }
    }

    T query(int index)
    {
        T sum = 0;
        for (; index > 0; index -= index & -index) {
            sum += tree[index];
        }
        return sum;
    }

    T range_query(int left, int right)
    {
        return query(right) - query(left - 1);
    }

  private:
    std::vector<T> tree;
    int size;
};
/* Snippet END */
