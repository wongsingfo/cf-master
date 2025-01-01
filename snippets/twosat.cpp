/* Snippet Header */
#include <bits/stdc++.h>
using namespace std;

/* Snippet BEGIN */

// Adapted from: https://codeforces.com/contest/1971/submission/260320149
struct SCC
{
  public:
    // Number of vertices (0, 1, ..., n-1)
    SCC(int n)
    {
        V = n;
        adj.assign(V, {});
    }

    template <typename T> SCC(T &&_adj)
    {
        adj = std::forward<T>(_adj);
        V = static_cast<int>(adj.size());
    }

    // Note that Tarjan's algorithm provides the SCCs in reverse topological
    // order.
    vector<vector<int>> components;
    vector<int> which_component;

    void insert(int u, int v) { adj[u].push_back(v); }

    void work()
    {
        tour_index.assign(V, -1);
        low_link.resize(V);
        which_component.assign(V, -1);

        stack.clear();
        stack.reserve(V);
        in_stack.assign(V, false);
        tour = 0;

        components = {};

        for (int i = 0; i < V; i++)
            if (tour_index[i] < 0)
                dfs(i);
    }

  private:
    int V;
    vector<vector<int>> adj;
    vector<int> tour_index, low_link;
    int tour;

    vector<int> stack;
    vector<bool> in_stack;

    void add_edge(int a, int b) { adj[a].push_back(b); }

    // Tarjan's algorithm.
    void dfs(int node)
    {
        tour_index[node] = tour++;
        low_link[node] = tour_index[node];
        stack.push_back(node);
        in_stack[node] = true;

        for (int neighbor : adj[node])
            if (tour_index[neighbor] < 0) {
                // neighbor is part of our subtree.
                dfs(neighbor);
                low_link[node] = min(low_link[node], low_link[neighbor]);
            } else if (in_stack[neighbor]) {
                // neighbor is a candidate for low_link.
                low_link[node] = min(low_link[node], tour_index[neighbor]);
            }

        if (low_link[node] == tour_index[node]) {
            // node is the highest node in an SCC, which includes everything on
            // the stack up to it.
            components.emplace_back();
            vector<int> &component = components.back();
            int x;

            do {
                assert(!stack.empty());
                x = stack.back();
                stack.pop_back();
                in_stack[x] = false;
                which_component[x] = int(components.size()) - 1;
                component.push_back(x);
            } while (x != node);
        }
    }
};

struct TwoSat
{
  public:
    TwoSat(int n = 0) : n(0)
    {
        for (int i = 0; i < n; i++)
            new_var();
    }

    int inv(int var) { return var ^ 1; }

    int new_var()
    {
        adj.emplace_back();
        adj.emplace_back();
        return 2 * n++;
    }

    void implies(int a, int b)
    {
        adj[a].push_back(b);
        adj[inv(b)].push_back(inv(a));
    }

    void either(int a, int b)
    {
        adj[inv(a)].push_back(b);
        adj[inv(b)].push_back(a);
    }

    void set_value(int a) { adj[inv(a)].push_back(a); }

    void equal(int a, int b)
    {
        implies(a, b);
        implies(inv(a), inv(b));
    }

    void unequal(int a, int b)
    {
        implies(a, inv(b));
        implies(inv(a), b);
    }

    void op_xor(int a, int b) { unequal(a, b); }
    void op_or(int a, int b) { either(a, b); }

    // Warning: this only creates an implication in the negative direction. It
    // is still possible for a = b = true with and_var = false. In particular,
    // it does not work to call set_value on inv(and_var).
    int create_and(int a, int b)
    {
        if (a < 0 || b < 0)
            return max(a, b);
        int result = new_var();
        implies(result, a);
        implies(result, b);
        return result;
    }

    // Warning: this only creates an implication in the positive direction. It
    // is still possible for a = b = false with or_var = true. In particular, it
    // does not work to call set_value on or_var.
    int create_or(int a, int b)
    {
        if (a < 0 || b < 0)
            return max(a, b);
        int result = new_var();
        implies(a, result);
        implies(b, result);
        return result;
    }

    int create_at_most_one(int a, int b)
    {
        if (a < 0 || b < 0)
            return max(a, b);
        either(inv(a), inv(b));
        return create_or(a, b);
    }

    template <typename T_iterable>
    int create_at_most_one(const T_iterable &vars)
    {
        int aux = -1;

        for (int var : vars)
            aux = create_at_most_one(aux, var);

        return aux;
    }

    bool check()
    {
        SCC scc(adj);
        scc.work();

        for (int i = 0; i < n; i++)
            if (scc.which_component[2 * i] == scc.which_component[2 * i + 1])
                return false;

        assignment.resize(2 * n);
        vector<bool> done(n, false);

        // Tarjan's algorithm provides the SCCs in reverse topological order.
        for (auto &component : scc.components)
            for (int x : component) {
                assignment[x] = !done[x / 2];
                done[x / 2] = true;
            }

        for (int i = 0; i < n; i++)
            assert(assignment[2 * i] ^ assignment[2 * i + 1]);

        return true;
    }

    vector<bool> model() { return assignment; }

  private:
    int n;
    vector<vector<int>> adj;
    vector<bool> assignment;
};

void two_sat_example()
{
    TwoSat solver(2);
    solver.set_value(0);
    solver.unequal(0, 2);
    assert(solver.check());
    assert(solver.model() == vector<bool>({true, false, false, true}));
};

/* Snippet END */
