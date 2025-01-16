#include "functions.hpp"

#include <algorithm>
#include <ranges>

extern "C" {
    void do_nothing(double val);
}

static constexpr bool is_odd(int val) noexcept {
    return val % 2 == 1;
}

static constexpr double transform_number(int input) noexcept {
    return input * 5;
}

void execute_raw_loop(std::span<const int> span, size_t offset, double early_exit) {
    for (size_t i = offset; i < span.size(); ++i) {
        auto data = span[i];
        if (!is_odd(data)) {
            continue;
        }

        double transform = transform_number(data);
        if (transform == early_exit) {
            return;
        }


        do_nothing(transform);
    }
}

void execute_find_if(std::span<const int> span, size_t offset, double early_exit) {
    /* Skip first 3 elements (container.begin() + offset isn't supported for all iterator types) */
    std::ignore = std::find_if(std::next(span.begin(), offset), span.end(), [&](int val) {
        /* Filter only for odd values*/
        if (!is_odd(val)) {
            return false;
        }

        /* Apply operation */
        double transformed = transform_number(val);
        
        /* Check if early exit encountered */
        if (transformed == early_exit) {
            return true;
        }

        /* Else - print value & continue */
        do_nothing(transformed);
        return false;
    });
}

void execute_view(std::span<const int> span, size_t offset, double early_exit) {
    auto elems = span
        | std::views::drop(offset)
        | std::views::filter(is_odd)
        | std::views::transform(transform_number)
        | std::views::take_while([&](auto v){return v != early_exit;});
    std::ranges::for_each(elems,do_nothing);
}

void execute_view_lambdas(std::span<const int> span, size_t offset, double early_exit) {
    auto elems = span
        | std::views::drop(offset)
        | std::views::filter([](auto x){return is_odd(x);})
        | std::views::transform([](auto y){return transform_number(y);})
        | std::views::take_while([&](auto v){return v != early_exit;});
    std::ranges::for_each(elems,do_nothing);
}