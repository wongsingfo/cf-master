/* Snippet Header */
#include <bits/stdc++.h>
using namespace std;

/* Snippet BEGIN */
class EulerianPath
{
  public:
    int edgeCount;
    vector<vector<pair<int, int>>> adj; // adjacency list

    EulerianPath(int n)
    {
        adj.resize(n + 1);
        edgeCount = 0;
    }

    void add_undirected(int u, int v)
    {
        adj[u].push_back({v, edgeCount});
        adj[v].push_back({u, edgeCount});
        edgeCount++;
    }

    void add_directed(int u, int v)
    {
        adj[u].push_back({v, edgeCount});
        edgeCount++;
    }

    bool path_exists_undirected(int start = -1)
    {
        int odd_count = 0;
        for (size_t u = 0; u < adj.size(); ++u) {
            if (adj[u].size() % 2 != 0) {
                odd_count++;
                if (start == -1) {
                    start = u; // Set the first odd degree vertex as the start
                }
            }
        }

        // If start is provided, check if it has an odd degree
        if (start != -1 && adj[start].size() % 2 == 0) {
            return false;
        }

        return odd_count == 0 || odd_count == 2;
    }

    bool path_exists_directed(int start = -1, int end = -1)
    {
        vector<int> in_degree(adj.size(), 0);
        vector<int> out_degree(adj.size(), 0);

        for (size_t u = 0; u < adj.size(); ++u) {
            out_degree[u] = adj[u].size();
            for (auto &e : adj[u]) {
                int v = e.first;
                in_degree[v]++;
            }
        }

        int start_nodes = 0, end_nodes = 0;
        for (size_t u = 0; u < adj.size(); ++u) {
            if (out_degree[u] - in_degree[u] == 1) {
                start_nodes++;
                if (start == -1) {
                    start = u;
                }
            } else if (in_degree[u] - out_degree[u] == 1) {
                end_nodes++;
                if (end == -1) {
                    end = u;
                }
            } else if (in_degree[u] != out_degree[u]) {
                return false;
            }
        }

        // If start or end is provided, check if they meet the criteria
        if (start != -1 && out_degree[start] - in_degree[start] != 1) {
            return false;
        }
        if (end != -1 && in_degree[end] - out_degree[end] != 1) {
            return false;
        }

        return (start_nodes == 0 && end_nodes == 0) ||
               (start_nodes == 1 && end_nodes == 1);
    }

    vector<int> eulerian_path(int start)
    {
        vector<int> ret;
        vector<bool> visited(edgeCount);

        // Lexicographical Order
        for (auto &a : adj) {
            sort(a.rbegin(), a.rend());
        }

        auto dfs = [&](auto self, int u) -> void {
            while (!adj[u].empty()) {
                auto e = adj[u].back();
                adj[u].pop_back();
                int v = e.first;
                int id = e.second;
                if (visited[id])
                    continue;
                visited[id] = true;
                self(self, v);
                ret.push_back(v);
            }
        };

        dfs(dfs, start);
        ret.push_back(start);
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
/* Snippet END */
