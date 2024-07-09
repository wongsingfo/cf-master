use std::io::Write;

// Reference: https://qiita.com/tanakh/items/0ba42c7ca36cd29d0ac8
macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        // Read from string `s`
        let mut iter = $s.split_whitespace();
        input_inner!{ iter, $($r)* }
    };
    ($($r:tt)*) => {
        // Read from standard input
        let s = {
            use std::io::Read;
            let mut s = String::new();
            std::io::stdin().read_to_string(&mut s).unwrap();
            s
        };
        input!{ source = s, $($r)* }
    };
}

macro_rules! input_inner {
    ($iter:expr) => {};
    ($iter:expr,) => {};
    ($iter:expr, $var:ident : $t:tt $($r:tt)*) => {
        #[allow(unused_mut)]
        let mut $var = read_value!($iter, $t);
        input_inner!{ $iter $($r)* }
    };
}

macro_rules! read_value {
    ($iter:expr, ( $($t:tt),* )) => {
        // `edge: (usize, usize)`
        ( $(read_value!($iter, $t)),* )
    };
    ($iter:expr, [ $t:tt; $len:expr ]) => {
        // `mat: [[i32: m]; n]` is expanded into `mat: [i32: m]` and then `mat: i32`
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };
    ($iter:expr, [ $t:tt ]) => {
        {
            let len = read_value!($iter, usize);
            (0..len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
        }
    };
    ($iter:expr, chars) => {
        $iter.next().unwrap().chars().collect::<Vec<char>>()
    };
    ($iter:expr, bytes) => {
        $iter.next().unwrap().bytes().collect::<Vec<u8>>()
    };
    ($iter:expr, usize1) => {
        // `edges: [(usize1, usize1); m]`
        read_value!($iter, usize) - 1
    };
    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

const N: usize = 100_000;
// const N: usize = 100;
const LOGN: usize = 17;

#[derive(Debug)]
struct Totient {
    phi_sum: Vec<u64>,
}

impl Totient {
    // O(N)
    fn new() -> Self {
        let mut phi = (0..=N as u32).collect::<Vec<_>>();
        for i in 2..=N {
            if phi[i] == i as u32 {
                for j in (i..=N).step_by(i) {
                    phi[j as usize] -= phi[j as usize] / i as u32;
                }
            }
        }
        Self {
            phi_sum: phi
                .iter()
                .scan(0u64, |s, &x| {
                    *s += x as u64;
                    Some(*s)
                })
                .collect(),
        }
    }

    fn get(&self, n: usize) -> u64 {
        self.phi_sum[n]
    }
}

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 {
        a
    } else {
        gcd(b, a % b)
    }
}

#[allow(unused)]
fn solve_bf(left: usize, right: usize) -> Vec<(usize, usize)> {
    (left..=right)
        .flat_map(|i| {
            (i..=right).filter_map(move |j| {
                if gcd(i as i64, j as i64) >= left as i64 {
                    Some((i, j))
                } else {
                    None
                }
            })
        })
        .collect()
}

/// For a specific `R`, we precompute `phi_sum[ R / k ]` for `k` = 1, 2, 3, ...
/// We store the prefix sum.
#[derive(Debug)]
struct MemoForR<'a> {
    totient: &'a Totient,
    /// Store the precomputed values for `k` = 1, 2, 3, ..., `floor(sqrt(R))`
    memo0: Vec<u64>,
    /// Store the precomputed values for `k`s where `R / k` = 1, 2, 3, ..., `floor(sqrt(R))`.
    /// Note that we need to exclude the `k`s that is less or equal to `sqrt(R)`
    memo1: Vec<u64>,
    r: usize,
    /// `sqrt_r` is the maximum number that `sqrt_r` * `sqrt_r` <= `R`
    sqrt_r: usize,
    sum_r: u64,
}

impl<'a> MemoForR<'a> {
    fn new(totient: &'a Totient, r: usize) -> Self {
        let memo0 = std::iter::once(0) // padding for 1-based indexing
            .chain(
                (1..)
                    .take_while(|&k| k * k <= r)
                    .map(|k| totient.get(r / k))
                    .scan(0u64, |s, x| {
                        *s += x as u64;
                        Some(*s)
                    }),
            )
            .collect::<Vec<_>>();
        let sqrt_r = memo0.len() - 1;
        let mut memo1 = (1..=sqrt_r)
            .map(|i| {
                let value = totient.get(i);
                // `maxk` is the largest `k` where `R / k` = i
                let maxk = r / i;
                // `mink` is the smallest `k` where `R / k` = i
                let mink = std::cmp::max(r / (i + 1) + 1, sqrt_r + 1);
                let count = if (mink..=maxk).is_empty() {
                    0
                } else {
                    maxk - mink + 1
                };
                value * count as u64
            })
            .rev()
            .scan(*memo0.last().unwrap_or(&0), |s, x| {
                *s += x;
                Some(*s)
            })
            .collect::<Vec<_>>();
        let sum_r = *memo1.last().unwrap_or(&0);
        memo1.push(0); // padding for zeo-based indexing
        memo1.reverse();
        Self {
            totient,
            memo0,
            memo1,
            r,
            sqrt_r,
            sum_r,
        }
    }

    /// Get sum for `k` = `l` to `r`, inclusively
    fn get(&self, l: usize) -> u64 {
        let sum_l1 = if l == 0 {
            0
        } else {
            let l = l - 1;
            if l <= self.sqrt_r {
                self.memo0[l]
            } else {
                let i = self.r / l;
                let value = self.totient.get(i);
                // `mink` is the smallest `k` where `R / k` = i
                let mink = std::cmp::max(self.r / (i + 1) + 1, self.sqrt_r);
                let values = value * std::cmp::max(0, (l - mink + 1) as u64);
                values
                    + self
                        .memo1
                        .get(i + 1)
                        .unwrap_or(self.memo0.last().unwrap_or(&0))
            }
        };
        self.sum_r - sum_l1
    }
}

struct Memo<'a> {
    /// O(n ^ ( 3/2 ))
    memos: Vec<MemoForR<'a>>,
}

impl<'a> Memo<'a> {
    fn new(totient: &'a Totient) -> Self {
        let memos = (0..=N)
            .map(|r| MemoForR::new(totient, r))
            .collect::<Vec<_>>();
        Self { memos }
    }

    /// Get the result for `c(l, r)`
    fn get(&self, l: usize, r: usize) -> u64 {
        self.memos[r].get(l)
    }
}

struct DP {
    dp: Vec<Vec<u64>>,
}
impl DP {
    /// O(N * log N)
    fn compute(
        dpi: &mut Vec<u64>,
        dpi1: &Vec<u64>,
        memo: &Memo,
        l: usize,
        r: usize,
        optl: usize,
        optr: usize,
    ) {
        if l > r {
            return;
        }
        let mid = (l + r) / 2;

        let (best, opt) = (optl..=std::cmp::min(optr, mid))
            .map(|i| {
                let cost = dpi1[i - 1] + memo.get(i, mid);
                (cost, i)
            })
            .min()
            .unwrap();

        dpi[mid] = best;
        Self::compute(dpi, dpi1, memo, l, mid - 1, optl, opt);
        Self::compute(dpi, dpi1, memo, mid + 1, r, opt, optr);
    }

    fn new(memo: &Memo) -> Self {
        // k = 1
        let dp0 = (0..=N).map(|i| memo.get(0, i)).collect::<Vec<_>>();
        let mut dp = vec![dp0];
        // k = 2 .. LOGN
        for _ in 1..=LOGN {
            let dpi1 = dp.last().unwrap();
            let mut dpi = vec![0; N + 1];
            Self::compute(&mut dpi, dpi1, memo, 1, N, 1, N);
            dp.push(dpi);
        }
        Self { dp }
    }

    fn answer(&self, n: usize, k1: usize) -> u64 {
        let k = k1 - 1;
        if k >= self.dp.len() {
            n as u64
        } else {
            self.dp[k][n]
        }
    }
}

fn main() {
    let totient = Totient::new();
    let memo = Memo::new(&totient);
// assert_eq!(memo.get(1, 2), 3);
// assert_eq!(memo.get(3, 6), 5);
// assert_eq!(solve_bf(3, 6).len(), 5);
// println!("{:?}", memo.memos[10]);
// assert_eq!(memo.get(3, 10), solve_bf(3, 10).len() as u64);
// assert_eq!(memo.get(8, 100), solve_bf(8, 100).len() as u64);
// assert_eq!(memo.get(70, 100), solve_bf(70, 100).len() as u64);
    let dp = DP::new(&memo);
    input! { queries: [ (usize, usize) ] };
    let stdout = std::io::stdout();
    let lock = stdout.lock();
    let mut buf = std::io::BufWriter::with_capacity(32 * 1024, lock);
    queries.iter().for_each(|(n, k)| {
        let _ = writeln!(buf, "{}", dp.answer(*n, *k)).unwrap();
    });
}
