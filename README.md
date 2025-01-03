# Content History

## 2026: Educational Codeforces Round 171 (Rated for Div. 2)

Date: Oct/28/2024
Rank: 1727
Solved: 3
Rating change: -80
New rating: 1970

- [Problem E](solved/2026E.cpp): The project selection problem.

## 2013: Codeforces Round 973 (Div. 2)

Date: Sep/20/2024
Rank: 936
Solved: 4
Rating change: -49
New rating: 2009

- [Problem E](solved/2013E.cpp): Greedy. Choose the smallest element. Proof: a b c 1 d e --> 1 a b c d e. Sister problem: 1614 D2.

## 2005: Codeforces Round 972 (Div. 2)

Date: Sep/14/2024
Rank: 245
Solved: 5
Rating change: +43
New rating: 2058

- [Problem E](solved/2005E.cpp): Good DP problem. Maintain the smallest array index that can win the game.
- Problem E: Use bitset to speed up.

## 2004: Educational Codeforces Round 169 (Rated for Div. 2)

Date: Aug/15/2024
Rank: 5441
Solved: 3
Rating change: -127
New rating: 1832

- [Problem E](solved/2004E.cpp): Use the SG theorem.
- [Problem F](solved/2004F.cpp): Key technique: find a suffix and a prefix that are equal.
- [Problem G](solved/2004G.cpp): Use segtree (may exceeds the time limit), two-stack technique, prefix/suffix sum.

## 2002: EPIC Institute of Technology Round August 2024 (Div. 1 + Div. 2)

Date: Aug/11/2024
Rank: 1500
Solved: 4
Rating change: 0
New rating: 1934

- [Problem D](solved/2002D.cpp): For a valid DFS order, the parent of `p[i+1]` must be an ancestor of `p[i]`.
- [Problem E](solved/2002E.cpp): Consider an incremental solution. Only keep useful information with a stack.
- [Problem F](solved/2002F.cpp): The prime gap is small: O(log n). Do a bfs search in a small corner (p,n) to (q,m).

## 1998: Codeforces Round 965 (Div. 2)

Date: Aug/10/2024
Rank: 1319
Solved: 3
Rating change: -38
New rating: 1934

- [Problem E](solved/1998E.cpp): Build a Cartesian tree and do dp on it.

## 1993: Codeforces Round 963 (Div. 2)

Date: Aug/04/2024
Rank: 722
Solved: 3
Rating change: -6
New rating: 1972

- [Problem D](solved/1993D.cpp): Key observation: `i%k` is the number of picked elements.
- [Problem E](solved/1993E.cpp): For a fix row, the number of possible values is n+1. Use dp to select a path.
- [Problem F](solved/1993F.cpp): Walking in a map with size of `[w*2, h*2]`. Use math to calculate how many times it visits (0,0). A similar problem [982E](https://codeforces.com/problemset/problem/982/E).

## 1997: Educational Codeforces Round 168 (Rated for Div. 2)

Date: Jul/30/2024
Rank: 2351
Solved: 4
Rating change: -90
New rating: 1978

- [Problem E](solved/1997E.cpp): For each monster, use binary search to find out what is the minimum k that the user will have to fight this monster.
- [Problem F](solved/1997F.cpp): Knapsack counting.

## 1995: Codeforces Round 961 (Div. 2)

Date: Jul/23/2024
Rank: 69
Solved: 5
Rating change: +114
New rating: 2067

- [Problem E](solved/1995E.cpp): Enumerate the min value and the max value. Use segment tree to fast check if the state is valid.

## 1990: Codeforces Round 960 (Div. 2)

Date: Jul/20/2024
Rank: 359
Solved: 4
Rating change: +49
New rating: 1953

- [Problem E](solved/1990E.cpp): Each query removes sqrt N nodes. Then use sqrt N queries to move the Mole to the root.
- [Problem F](solved/1990F.cpp): Key observation: number of possible ends is log N. Use segment tree.

## 1988: Codeforces Round 958 (Div. 2)

Date: Jul/15/2014
Rank: 2194
Solved: 3
Rating change: -81
New rating: 1903

Unsolved problems:
- [Problem D](solved/1988D.cpp): The maximum number of round is limited to log2n.
- [Problem E]: Use Cartesian tree to calculate the answer. What happens if one of the tree node gets removed?
- [Problem E](solved/1988E.cpp): Count the contribution of each number to the final answer. A trick to find the second maximum next value.
- [Problem F](solved/1988F.cpp): For each n, calculate sum i sum p sum q F(i, p) times G(n-i, q). Reduce the time from O(n4) to O(n3).

## 1983: Codeforces Round #956 (Div. 2) and ByteRace 2024

Date: Jul/07/2024
Rank: 131
Solved: 5
Rating change: +114
New rating: 1984

Unsolved problems:
- [Problem F](solved/1983F.cpp): Binary search on the answer and check for each new right end if it can lead to a smaller xor value.
- [Problem G](solved/1983G.cpp): Calculate each bit independently. Use the patterns (e.g. 00110011) to precompute the sum to the tree root.

## 1978: Codeforces Round 953 (Div. 2)

Date: Jun/16/2024
Rank: 340
Solved: 5
Rating change: +63
New rating: 1870

Unsolved problems:
- [Problem F](solved/1978F.cpp): Use DSU to merge the nodes with the same factor.

## 1984: Codeforces Global Round 26

Date: Jun/09/2024
Rank: 2154
Solved: 4
Rating change: -31
New rating: 1807

Unsolved problems:
- [Problem D](solved/1984D.cpp): Use the z-algorithm to check if the string is composed of several identical substrings.
- [Problem E](solved/1984E.cpp): Tree DP. Need to enumerate which node is root.
- [Problem F](solved/1984F.cpp): Enumerate the answer. Use a one-pass DP to check if the answer is valid.
- [Problem G](solved/1984G.cpp): Sort the permutation by constructive solution.
