function timeTest(f, n) {
    let start = Date.now()
    f(n)
    console.log(f.name + ':\n\t' + (Date.now() - start)/1000 + 's')
}

//runtime: O(3^n), space: O(n)
function trib(n) {
    if (n < 2) return 0
    if (n == 2) return 1
    return trib(n - 1) + trib(n - 2) + trib(n - 3)
}

//runtime: O(n), space: O(1)
function lin_trib(n) {
    if (n < 2) return 0
    if (n == 2) return 1
    let a = 0, b = 0, c = 1
    for (let i = 3; i <= n; i++) {
        [a, b, c] = [b, c, a + b + c]
    }
    return c
}

timeTest(trib, 30)
timeTest(lin_trib, 10000000)