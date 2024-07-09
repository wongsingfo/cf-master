#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#ifdef DBG
#define dbg(...) fprintf(stdout, __VA_ARGS__)
#else
#define dbg(...)                                                               \
    do {                                                                       \
    } while (0)
#endif

const int MAXN = 1005;
const int MAXM = 5 * MAXN * MAXN;
const int MOD = 1e9 + 7;

int n;
vector<int> p;
vector<pair<int, int>> operations;

bool is_sorted() {
    for (int i = 1; i < n; ++i) {
        if (p[i] < p[i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_cyclic() {
    for (int i = 0; i < n; ++i) {
        int x = p[i];
        int y = p[(i + 1) % n];
        if (x + 1 != y && x != n) {
            return false;
        }
    }
    return true;
}

struct Arr {
  public:
    vector<int> arr;
    int split;

    int &get(int i) { return arr[(i + split) % n]; }

    int &first() { return get(0); }
    int &last() { return get(n - 1); }
    int &last2() { return get(n - 2); }

    void output() {
        dbg("arr: ");
        for (int i = 0; i < n; ++i) {
            dbg("%d ", get(i));
        }
        dbg("\n");
    }

    // .......xy
    // x.......y
    void doA() {
        operations.push_back({1, 2});
        swap(get(n - 1), get(n - 2));
        split = (split + n - 1) % n;

        dbg("doA: ");
        output();
    }

    // x......y
    // ......xy
    void doB() {
        operations.push_back({2, 1});
        swap(get(0), get(n - 1));
        split = (split + 1) % n;

        dbg("doB: ");
        output();
    }

    // .....xy
    // xy.....
    void doE() {
        operations.push_back({1, 3});
        split = (split + n - 2) % n;
        dbg("doE: ");
        output();
    }

    int index(int num) {
        for (int i = 0; i < n; ++i) {
            if (get(i) == num) {
                return i;
            }
        }
        assert(false);
    }
};

bool is_inv(int x, int y) {
    if (x == 1 || y == 1) return false;
    return x > y;
}
// solve with k = n - 2
bool solve2(Arr arr) {
    dbg("try to solve: ");
    arr.output();
    int done = 0;
    while (done < n + 5) {
        if (is_inv(arr.last2(), arr.last())) {
            arr.doA();
            done = 0;
        }

        if (is_inv(arr.last(), arr.first())) {
            arr.doB();
            done = 0;
        }

        if (done > 0) {
            arr.doE();
        }

        done += 1;
    }

    int index1 = arr.index(1);
    if (n % 2 == 0 && index1 % 2 == 1)
        return false;

    while (arr.first() != 1) {
        arr.doE();
    }

    return true;
}

void prepare() {
    while (p[n - 1] != n && p[n - 2] != n && p[n - 3] != n) {
        int a = p[n - 3], b = p[n - 2], c = p[n - 1];
        for (int i = n - 1; i >= 3; i--) {
            p[i] = p[i - 3];
        }
        p[0] = a;
        p[1] = b;
        p[2] = c;
        operations.push_back({1, 4});
    }

    dbg("after prepare\n");
    for (int i = 0; i < n; ++i) {
        dbg("%d ", p[i]);
    }
    dbg("\n");

    if (p[n - 1] == n) {
        dbg("prepare: 1\n");
        return;
    }

    // xxxxxxnx
    //   -----
    if (p[n - 2] == n) {
        dbg("prepare: 2\n");
        int a = p[n - 1];
        for (int i = n - 1; i >= 3; i--) {
            p[i] = p[i - 1];
        }
        p[2] = a;
        operations.push_back({3, 4});
        return;
    }

    // xxxxxnxx
    //  -----
    if (p[n - 3] == n) {
        dbg("prepare: 3\n");
        int a = p[n - 2], b = p[n - 1];

        for (int i = n - 1; i >= 3; i--) {
            p[i] = p[i - 2];
        }

        p[1] = a;
        p[2] = b;
        operations.push_back({2, 4});
        return;
    }
}

int solve() {
    // Implement the solution here, using global variables p and operations
    if (is_sorted()) {
        return n;
    }
    if (is_cyclic()) {
        while (!is_sorted()) {
            operations.push_back({1, 2});

            int last = p[n - 1];
            for (int i = n - 1; i > 0; i--) {
                p[i] = p[i - 1];
            }
            p[0] = last;
        }
        return n - 1;
    }

    Arr arr{p, 0};

    if (solve2(arr)) {
        return n - 2;
    }

    operations.clear();

    prepare();

    n -= 1;
    Arr arr2{p, 0};
    assert(solve2(arr2));
    n += 1;

    return n - 3;
}

void reset() {
    p.clear();
    operations.clear();
    // Reset other global variables if needed
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        reset();
        scanf("%d", &n);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &p[i]);
        }
        int k = solve();
        printf("%d\n", k);
        int m = operations.size();
        printf("%d\n", m);
        for (const auto &op : operations) {
            printf("%d %d\n", op.first, op.second);
        }
    }
    return 0;
}
