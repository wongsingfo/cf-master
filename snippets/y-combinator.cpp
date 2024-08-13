/* Snippet Header */
#include <bits/stdc++.h>

/* Snippet BEGIN */
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun> class y_combinator_result
{
    Fun fun_;

  public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun))
    {
    }
    template <class... Args> decltype(auto) operator()(Args &&...args)
    {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
template <class Fun> decltype(auto) y_combinator(Fun &&fun)
{
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

void y_combinator_example()
{
    auto fact = y_combinator([&](auto self, int n) -> int {
        if (n == 0)
            return 1;
        return n * self(n - 1);
    });
    assert(fact(5) == 120);

    // Or y_combinator(...)(args);
}

/* Snippet END */
