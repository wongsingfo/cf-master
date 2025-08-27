As an experienced coder, your task is to provide a C++20 boilerplate code solution to the following coding problem. Enclose the complete code within a quote block. No explanations are necessary.

Here are some rules to follow when coding:
- Include <bits/stdc++.h> and using std namespace to use the C++ standard library.
- Use using i64 = long long; for simplifying the use of long long types.
- Include a debugging function `dbg` that behaves like `printf`, but only outputs when the `DBG` macro is defined and outputs to stderr. The `DBG` macro should not be defined within the code.
   ```cpp
   #ifdef DBG
   #include "debug.h"
   #else
   #define dbg(...)
   #define dbg_export(...)
   #endif
   ```
- If each test consists of multiple test cases, the `solve` function should be called multiple times, each time for a different test case; each call to the `solve` function returns the result for one test case. If there is only one test case, ignore this rule.
- Follow the indexing conventions used by the problem statement. If the problem uses one-indexing (e.g., a_1, a_2, ... a_n), use one-indexing in the code. If the problem uses zero-indexing, use zero-indexing in the code.
- If the answer needs to take modulo, define the constant `MOD`. Otherwise, ignore this rule.

Here is a reference implementation that conforms to the above rules:

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    // Solve the problem here.

    cout << ans.size() << endl;
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i==n];
}

int main()
{
#ifndef DBG
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
```

**Below content the problem description.**
