/* Snippet Header */
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

/* Snippet BEGIN */

template <typename T>
    requires requires(T a) {
        { a.size() } -> std::convertible_to<std::size_t>;
        { a[0] } -> std::convertible_to<typename T::value_type>;
    }
vector<int> ext_kmp(const T &s, const T &t)
{
    int n = s.size(), m = t.size();
    vector<int> z(m, 0), result(n, 0);

    int l = 0, r = 0;
    for (int i = 1; i < m; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < m && t[z[i]] == t[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    l = r = 0;
    for (int i = 0; i < n; ++i) {
        if (i <= r)
            result[i] = min(r - i + 1, z[i - l]);
        while (i + result[i] < n && result[i] < m &&
               s[i + result[i]] == t[result[i]])
            ++result[i];
        if (i + result[i] - 1 > r) {
            l = i;
            r = i + result[i] - 1;
        }
    }

    return result;
}

void ext_kmp_examples()
{
    vector<int> v1 = {1, 2, 3, 4};
    vector<int> v2 = {2, 3};
    auto result = ext_kmp(v1, v2);

    string s1 = "abcdef";
    string s2 = "cde";
    auto result2 = ext_kmp(s1, s2);
}

/* Snippet END */
