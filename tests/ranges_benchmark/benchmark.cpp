#include "functions.hpp"
#include <charconv>
#include <cmath>
#include <cstring>
#include <iostream>
#include <locale>
#include <optional>
#include <vector>
#include <numeric>
#include <chrono>

#ifndef COMPILER_NAME
#define COMPILER_NAME "UNKNOWN"
#endif

static size_t call_cnt = 0;

extern "C" {
    void do_nothing(double val) {
        ++call_cnt;
        return;
    }
}

static std::vector<int> gen_vector(size_t size) {
    std::vector<int> vec(size);
    std::iota(vec.begin(), vec.end(), 0);
    return vec;
}

struct BenchCalc {
    using Hp = std::chrono::high_resolution_clock;
    using HpClk = std::chrono::time_point<Hp, std::chrono::nanoseconds>::clock;

    using Tp = decltype(HpClk::now() - HpClk::now());

    decltype(HpClk::now()) begin;

    BenchCalc() : begin(HpClk::now()) {}

    Tp time() {
        return HpClk::now() - begin;
    }

    template <typename TFunc>
    static Tp calc(TFunc &&func, size_t avg_cnt = 10, size_t warmup_cnt = 2) {
        Tp accum{};
        for (size_t i = 0; i < warmup_cnt; ++i) {
            func();
        }
        for (size_t i = 0; i < avg_cnt; ++i) {
            BenchCalc c;
            func();
            accum += c.time();
        }

        return accum / avg_cnt;
    }
};

template <typename T>
static std::optional<T> parse_input(const char *ptr) {
    T val;
    if constexpr (std::is_floating_point_v<T>) {
        char *out = nullptr;
        val = ::strtod(ptr, &out);
        if (out != ptr + strlen(ptr)) {
            return std::nullopt;
        }
        return val;
    } else {
        auto [res, err] = std::from_chars<T>(ptr, ptr + strlen(ptr), val);
        if (err == std::errc()) {
            return val;
        }

        return std::nullopt;
    }
}

// extern "C" {
int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: ./x A B C -- where A - vec count, B - offset, C - 'magic number'";
        return -1;
    }

    auto vec_size = parse_input<size_t>(argv[1]);
    auto offset = parse_input<size_t>(argv[2]);
    auto magic_nr = parse_input<double>(argv[3]);

    if (!vec_size || !offset || !magic_nr) {
        std::cerr << "Usage: ./x A B C -- where A - vec count, B - offset, C - 'magic number'";
        return -1;
    }

    auto vec = gen_vector(*vec_size);
    
    call_cnt = 0;
    auto raw_ns = BenchCalc::calc([&](){
        execute_raw_loop(vec, *offset, *magic_nr);
    });
    // std::cerr << "Cal cnt: " << call_cnt << '\n';

    call_cnt = 0;
    auto find_if_ns = BenchCalc::calc([&](){
        execute_find_if(vec, *offset, *magic_nr);
    });
    // std::cerr << "Cal cnt: " << call_cnt << '\n';

    call_cnt = 0;
    auto view_ns = BenchCalc::calc([&](){
        execute_view(vec, *offset, *magic_nr);
    });
    // std::cerr << "Cal cnt: " << call_cnt << '\n';

    call_cnt = 0;
    auto view_lambda_ns = BenchCalc::calc([&](){
        execute_view_lambdas(vec, *offset, *magic_nr);
    });
    // std::cerr << "Cal cnt: " << call_cnt << '\n';

    std::cout << *vec_size << " " COMPILER_NAME << " " << raw_ns << " " << find_if_ns << " " << view_ns << " " << view_lambda_ns << '\n';
    return 0;
}
// }