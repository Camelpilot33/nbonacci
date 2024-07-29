# n-bonacci
Analysis of higher level fibonacci algorithms' time complexity.

### Fibonacci sequence

The Fibonacci sequence is a series of numbers in which each number is the sum of the two preceding ones.The sequence starts with 0 and 1. (0,1,1,2,3,5...)

### N-bonacci sequence

We can extend this definition to the N-bonacci sequence, where each number is the sum of the N preceding ones. For example, the 3-bonacci sequence starts with 0,0,1 and then each number is the sum of the 3 preceding ones. (0,0,1,1,2,4,7,13,24...)

### Naive approach

Using recursion, we can calculate

$f(n) = f(n-1) + f(n-2) + ... + f(n-m)$

This approach has exponential time complexity.

### Optimized approach

Using a sliding window, we can calculate the N-bonacci sequence in linear time complexity.

### Matrix powers

Given the vector $v = \langle f(n), f(n+1), ..., f(n+m-1)\rangle$, we can calculate the vector $v' = [f(n+1), f(n+2), ..., f(n-m)]$ by multiplying $v$ by the matrix $M$:

$M = \begin{bmatrix}
0 & 1 & 0 & ... & 0 \\
0 & 0 & 1 & ... & 0 \\
... & ... & ... & ... & ... \\
1 & 1 & 1 & ... & 1
\end{bmatrix}$

Then we can write $v = M^n\cdot v_0$, where $v_0 = \langle 0,0,\dots1\rangle$.

The matrix power can be computed in logarithmic time by writing $M^{2n} = M^n\cdot M^n$.