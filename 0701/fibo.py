def fibonacci(n):
    """Return the n-th Fibonacci number using recursion."""
    if n <= 0:
        return 0
    if n == 1:
        return 1
    return fibonacci(n - 1) + fibonacci(n - 2)


if __name__ == "__main__":
    for i in range(10):
        print(fibonacci(i))


