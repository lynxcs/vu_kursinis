std::generator<uint64_t> fibonacci() noexcept {
    size_t a = 1, b = 1;
    while (true) {
        co_yield a;
        a = std::exchange(b, a + b);
    }
}

void fib_seq(size_t max_cnt) noexcept {
    auto fib = fibonacci()
            | std::views::take(max_cnt);
    for (auto val : fib) {
        std::cout << val << '\n';
    }
}