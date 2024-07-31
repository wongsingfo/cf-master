// Generate a C++ template to manage input and output according to the given
// problem description:
// 1. Include <bits/stdc++.h> to use the C++ standard library.
// 2. Use 'using i64 = long long;' for simplifying the use of 'long long' types.
// 3. Use 'using namespace std;' to simplify the code syntax.
// 4. Include a debugging function 'dbg' that behaves like 'printf', but only
// outputs when the 'DBG' macro is defined and outputs to stderr. The 'DBG'
// macro should not be defined within the code.
//   #ifdef DBG
//   #include "debug.h"
//   #else
//   #define dbg(...)
//   #define dbg_export(...)
//   #endif
// 5. Store input data in global variables. For example, for an array `a`, you
// can use `vector<int> a`. The 'solve' function accesses the input as global
// variables.
// 6. Ensure the global input data are properly reset or cleaned before
// processing a new test case.
// 7. Implement a main function that calls the 'solve' function to process and
// print the returned values. You may choose not to implement the 'solve'
// function and just handle the I/O.
// 8. If each test consists of multiple test cases, the 'solve' function should
// be called multiple times, each time for a different test case; each call to
// the 'solve' function returns the result for one test case. If there is only
// one test case, ignore this rule.
// 9. Use cin and cout for I/O. Add the following to make I/O faster.
//   ios::sync_with_stdio(false); cin.tie(nullptr);
// 10. Follow the indexing conventions used by the problem statement. If the
// problem use one-indexing (e.g. a_1, a_2, ... a_n), use one-indexing in the
// code. If the problem uses zero-indexing, use zero-indexing in the code.
// 11. If the answer needs to take modulo, define the constant 'MOD'. Otherwise,
// ignore this rule.
// 
// Here is a reference implementation:

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
    a.clear();
    a.resize(n + 1);
}

int solve()
{
    // placeholder
    return 0;
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
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        int ans = solve();
        cout << ans << endl;
    }

    return 0;
}

// Generate only the code in a quote block. Don't add any explanations.
