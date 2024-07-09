use std::io::Write;

// Inspired by: https://qiita.com/tanakh/items/0ba42c7ca36cd29d0ac8
macro_rules! input {
    (iter = $s:expr, $($r:tt)*) => {
        input_inner!{ $s, $($r)* }
    };
    (source = $s:expr, $var:ident : iter, $($r:tt)*) => {
        // Read from string `s`
        let mut $var = $s.split_whitespace();
        input!{ iter = $var, $($r)* }
    };
    (source = $s:expr, $($r:tt)*) => {
        input!{ source = $s, _: ident, $($r)* }
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
        let $var = read_value!($iter, $t);
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

fn gcd(x: i32, y: i32) -> i32 {
    if y == 0 {
        x
    } else {
        gcd(y, x % y)
    }
}

fn main() {
    input! {
        iter: iter,
        t: usize,
    }
    let stdout = std::io::stdout();
    let lock = stdout.lock();
    let mut buf = std::io::BufWriter::with_capacity(32 * 1024, lock);
    (0..t).for_each(|_| {
        input! {
            iter = iter,
            n: usize,
            m: usize,
            a: [i32; n],
            b: [i32; m],
        }
        let g = b.iter().fold(0, |acc, &x| gcd(acc, x)) as usize;
        // Given a flipping state, how to check if it is valid? Answer: greedy algorithm.
        //
        // Suppose g = 3 now, and n = 3, the only valid state is 000, 111
        // Now, if n = 4, we have 0000, 1001, 1110, 0111. The last two bits are determined by the
        // first two bits.
        //
        // We come to the conclusion:
        //  - The number of valid states is 2^(n-g+1)
        //  - A valid state has the property that the
        //     - a_i xor a_{i+g} xor a_{i+2g} are equal for all i in 0..g
        // sum of abs(a)
        let ans = (0..g)
            .map(|offset| {
                let init_state = (a[offset] as i64, -a[offset] as i64);
                let (f, g) = (offset + g..n).step_by(g).fold(init_state, |(f1, g1), i| {
                    let f = std::cmp::max(f1 + a[i] as i64, g1 - a[i] as i64);
                    let g = std::cmp::max(f1 - a[i] as i64, g1 + a[i] as i64);
                    (f, g)
                });
                (f, g)
            })
            .fold((0, 0), |(fs, gs), (f, g)| (fs + f, gs + g));
        let ans = std::cmp::max(ans.0, ans.1);
        writeln!(buf, "{}", ans).unwrap();
    });
}
