As an experienced coder, your task is to provide an accurate and optimal solution to a coding problem in C++. To accomplish this, follow these steps:

**Solution Design:**

**Step 1:** "Proposed Solution". Then brainstorm and design the solution. Be aware of the time complexity of the solution. The solution should be as optimal as possible. Include your thinking at the beginning of the code header as a block comment.

Here are some guidelines to help you analyze the problem:
- Summarize the problem
- The key insight to solve the problem (Follow the HINT if it presents)
- A step-by-step plan for the solution

**Step 2:** "Implementation". Then implement the proposed solution in C++ (std=c++20). In this step, only include the code in a quote block. Don't add any explanations.

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
- Store input data in global variables. For example, for an array `a`, you can use `vector<int> a`. The `solve` function accesses the input as global variables.
- The global input stores data for only one test case. Ensure the global input data are properly reset or cleaned before processing a new test case.
- If each test consists of multiple test cases, the `solve` function should be called multiple times, each time for a different test case; each call to the `solve` function returns the result for one test case. If there is only one test case, ignore this rule.
- Follow the indexing conventions used by the problem statement. If the problem uses one-indexing (e.g., a_1, a_2, ... a_n), use one-indexing in the code. If the problem uses zero-indexing, use zero-indexing in the code.
- If the answer needs to take modulo, define the constant `MOD`. Otherwise, ignore this rule.
- Analyze the time complexity at the end of the code.

Here is a reference implementation that conforms to the above rules:

```cpp
/* Put your thinking here as a block comment.
Problem Summary: ...

Key Insight: ...

Step-by-Step Plan:
1. ...
    a. ...
    b. ...
2. ...
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#ifdef DBG
#include "debug.h"
#else
#define dbg(...)
#define dbg_export(...)
#endif

int n;
vector<int> a;

void reset_globals()
{
    n = 0;
    a.clear();
}

i64 solve()
{
    if (n == 0) {
        // Check the corner case
        return 1;
    }
    // Placeholder: Solve the general problem
    return answer;
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
        reset_globals();
        // start input after reset_globals
        cin >> n;
        a.resize(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        auto ans = solve();
        cout << ans << endl;
    }

    return 0;
}

// Time Complexity: O(n^2) per test case.
```

**Below content the problem description. At the end of the problem description. You can find a "HINT" section that tells you how to solve the problem. The hint may be messy because it is written in a hurry. Try your best to guess the meaning. Please strictly follow the HINT!!!**
