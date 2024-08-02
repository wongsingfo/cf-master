/* Snippet Header */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tree_policy.hpp>

/* Snippet BEGIN */

// `tree_order_statistics_node_update` is required for order_of_key() and
// find_by_order()
template <typename T, typename Cmp = std::less<T>>
using tree =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, Cmp, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename T, typename Cmp = std::less<T>>
using heap = __gnu_pbds::priority_queue<T, Cmp, __gnu_pbds::pairing_heap_tag>;

#define tree_count_strictly_less_than(t, x) (t.order_of_key(x))
#define tree_count_greater_or_equal_than(t, x) (t.size() - t.order_of_key(x))

void pb_ds_example()
{
    tree<int> X;
    X.insert(1);
    assert(!X.insert(1).second); // A set, without duplicated elements
    X.insert(2);
    X.insert(4);
    X.insert(8);
    X.insert(16);

    assert(*X.find_by_order(1) == 2); // Order: 0...n-1
    // Cannot find
    assert(end(X) == X.find_by_order(-1));
    assert(end(X) == X.find_by_order(5));

    // Find the order of the first elem that is greater or equal to x
    assert(X.order_of_key(-5) == 0);
    assert(X.order_of_key(1) == 0);
    assert(X.order_of_key(3) == 2);
    assert(X.order_of_key(4) == 2);
    assert(tree_count_strictly_less_than(X, 3) == 2);
    assert(tree_count_strictly_less_than(X, 4) == 2);
    assert(tree_count_strictly_less_than(X, 5) == 3);
    assert(tree_count_strictly_less_than(X, 400) == 5);
    assert(tree_count_greater_or_equal_than(X, 0) == 5);
    assert(tree_count_greater_or_equal_than(X, 1) == 5);
    assert(tree_count_greater_or_equal_than(X, 2) == 4);

    assert(*X.lower_bound(3) == 4);

    heap<int> a;
    heap<int>::point_iterator iter1 = a.push(1);
    a.push(2);
    // [1,2]
    assert(a.top() == 2);
    // [2,3]
    a.modify(iter1, 3); // iter1 is still valid after modification to the heap
    assert(a.top() == 3);
    a.push(3);
    // [2,3,3]
    a.pop();
    a.pop();
    assert(a.top() == 2);

    heap<int> b;
    b.push(3);
    a.join(b); // Note that join() is O(1) and b is set to an empty set
    assert(a.top() == 3);
}

/* Snippet END */
