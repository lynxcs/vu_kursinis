/* Can be called in
run-time or compile-time */
static constexpr
int multiply(int a, int b) {
    return a * b;
}

/* Guarantee compile-time execution*/
static constexpr
    auto mult = multiply(1, 2);

int runtime_func(int a, int b) {
    /* Can also be
    used at run-time*/
    return multiply(a, b);
}

/* Can only be called
at compile-time */
static consteval
int multiply_c(int a, int b) {
    return a * b;
}

int runtime_func_c(int a, int b) {
    /* Will not compile, consteval
    function cannot be called at
    run-time*/
    return multiply_c(a, b);
}