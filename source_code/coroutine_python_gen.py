def fibonacci():
    a, b = 1, 1
    while True:
        yield a
        a, b = b, a + b
    
def fib_seq(max_cnt):
    f = fibonacci()
    for i in range(max_cnt):
        print(next(f))
