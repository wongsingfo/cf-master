#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

int n, k;
string s;

int inf = 1e9;

struct Mat
{
    std::array<std::array<int, 10>, 10> a;
    Mat()
    {
        for (auto &x : a) {
            x.fill(inf);
        }
    }
    Mat(int x) : Mat()
    {
        // init
        //   0 1 2 3
        //   0 X X X
        //
        // suppose x = 3
        //   0 1 2 3
        // 0 X X X 0
        // 1 1 1 X X
        // 2 2 X 2 X
        // 3 3 X X 3

        a[0][x] = 0;
        for (int i = 1; i <= 9; i++) {
            a[i][0] = i;
            a[i][i] = i;
        }
    }

    static Mat eye()
    {
        Mat ret;
        for (int i = 0; i < 10; i++) {
            ret[i][i] = 0;
        }
        return ret;
    }

    std::array<int, 10> &operator[](int i) { return a[i]; }

    Mat operator*(Mat &b) const
    {
        Mat ret;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++) {
                auto v = inf;
                for (int k = 0; k < 10; k++) {
                    v = min(v, a[i][k] + b[k][j]);
                }
                ret[i][j] = v;
            }
        return ret;
    }
};

int main()
{
#ifndef DBG
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    cin >> n >> k >> s;
    s = '_' + s;

    vector<Mat> mat(10);
    for (int i = 1; i < 10; i++)
        mat[i] = Mat(i);
    mat[0] = Mat::eye();

    vector<Mat> right(n + 1), left(n + 1);

    assert(k >= 2);
    for (int i = 1; i <= n; i++) {
        if (i % k == 1) {
            left[i] = mat[s[i] - '0'];
        } else {
            left[i] = left[i - 1] * mat[s[i] - '0'];
        }
    }

    for (int i = n; i >= 1; i--) {
        if (i == n || i % k == 0)
            right[i] = mat[s[i] - '0'];
        else
            right[i] = mat[s[i] - '0'] * right[i + 1];
    }

    vector<int> ans;
    for (int i = 1; i + k - 1 <= n; i++) {
        Mat m;
        if (i % k == 1)
            m = right[i];
        else
            m = right[i] * left[i + k - 1];

        ans.push_back(m[0][0]);
    }

    for (auto x : ans) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}
