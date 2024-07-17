// Generate a C++ template to manage input and output according to the given
// problem description:
// 1. Include <bits/stdc++.h> to use the C++ standard library.
// 2. Use 'using ll = long long;' for simplifying the use of 'long long' types.
// 3. Use 'using namespace std;' to simplify the code syntax.
// 4. Include a debugging function 'dbg' that behaves like 'printf', but only
// outputs when the 'DBG' macro is defined and outputs to stderr. The 'DBG'
// macro should not be defined within the code.
//   #ifdef DBG
//   #define dbg(...) fprintf(stderr, __VA_ARGS__)
//   #else
//   #define dbg(...)
//   #endif
// 5. Store input data in global variables. For example, for an array `a`, you
// can use either `vector<int> a` or `int a[MAXN]`, where MAXN can be defined as
// a constant (e.g. const int MAXN = 100005;). The 'solve' function accesses the
// input as global variables.
// 6. Ensure the global input data are properly reset or cleaned before
// processing a new test case. Don't use 'memset' to clear the input data,
// instead use 'std::fill' to clear the input data. Don't reset the whole data
// (e.g. fill(array, array+MAXN, 0)). Instead, only reset the area we will use
// (e.g. fill(array, array+n, 0) where n depends on the input data).
// 7. Implement a main function that calls the 'solve' function to process and
// print the returned values. You do not need to implement the 'solve' function
// itself, just handle the I/O.
// 8. If each test consists of multiple test cases, the 'solve' function should
// be called multiple times, each time for a different test case; each call to
// the 'solve' function returns the result for one test case. If there is only
// one test case, ignore this rule.
// 9. Use 'scanf' and 'printf' for efficient input and output processing.
// 10. Follow the indexing conventions used by the problem statement. If the
// problem use one-indexing (e.g. a_1, a_2, ... a_n), use one-indexing in the
// code.
//   for (int i = 1; i <= n; i++) foo(a[i]);
//   fill(vec + 1, vec + n + 1, 0));
//   vector<int> vec(n + 1);
//   vec.resize(n + 1);
// If the problem uses zero-indexing, use zero-indexing in the code.
// 11. If the answer needs to take modulo, define the constant 'MOD'. Otherwise,
// ignore this rule.
//
// Generate only the code in a quote block. Don't add any explanations.
