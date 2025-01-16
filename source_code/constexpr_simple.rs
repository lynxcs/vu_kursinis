/* Can be called in
run-time or compile-time */
const fn
multiply(a: i32, b: i32) -> i32 {
    return a * b;
}

/* Guarantee compile-time
execution */
const mult: i32
    = multiply(1, 2);

pub fn
runtime_func(a: i32, b: i32) -> i32 {
    multiply(a, b);
}