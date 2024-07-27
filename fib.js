function timeTest(f, n) {
    let start = Date.now()
    f(n)
    console.log(f.name + ':\n\t' + (Date.now() - start)/1000 + 's')
}

//runtime: O(phi^n), space: O(n)
function exp_fib(n) {
    if (n <= 1) return n
    return exp_fib(n - 1) + exp_fib(n - 2)
}

//runtime: O(n), space: O(n)
function lin_fib(n, dp={}) {
    if (n <= 1) return n
    if (dp[n]) return dp[n]
    return dp[n] = lin_fib(n - 1, dp) + lin_fib(n - 2, dp)
}

//runtime: O(n), space: O(1)
function lin_fib_smaller(n) {
    if (n <= 1) return n
    let a = 0, b = 1
    for (let i = 2; i <= n; i++) {
        [a, b] = [b, a + b]
    }
    return b
}

//runtime: O(log(n)), space: O(1)
function log_fib(n) {
    if (n <= 1) return n
    let a = 0,
        b = 1,
        c = 1,
        d = 0,
        t = 0
    while (n > 0) {
        if (n % 2 == 1) {
            t = d * b + c * a
            a = d * a + c * b + c * a
            b = t
        }
        t = d * d + c * c
        c = 2 * d * c + c * c
        d = t
        n = Math.floor(n / 2)
    }
    return a
}


console.log("Size 40")
let testSize = 38
timeTest(exp_fib, testSize) // takes too long to run larger sizes
timeTest(lin_fib, testSize)
timeTest(lin_fib_smaller, testSize)
timeTest(log_fib, testSize)

testSize = 7000
console.log("\nSize "+testSize)
timeTest(lin_fib, testSize) // too much stack memory to run larger sizes
timeTest(lin_fib_smaller, testSize)
timeTest(log_fib, testSize)

testSize = 100000000
console.log("\nSize "+testSize)
timeTest(lin_fib_smaller, testSize) // too slow to run larger sizes
timeTest(log_fib, testSize)

// log_fib is the fastest method