/* Snippet Header */
#include <bits/stdc++.h>
using namespace std;

/* Snippet BEGIN */
class DSU
{
  public:
    DSU(int size)
    {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    bool in_union(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        return rootX == rootY;
    }

    void join(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    int count_unions()
    {
        int ret = 0;
        for (size_t i = 0; i < parent.size(); i++)
            ret += parent[i] == (int)i;
        return ret;
    }

  private:
    std::vector<int> parent;
    std::vector<int> rank;
};
/* Snippet END */
