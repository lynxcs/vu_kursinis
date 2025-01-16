struct Point {
    int x, y;
};

struct Square {
    size_t size;

    constexpr size_t area() const noexcept {
        return size * 2;
    }
};

template <typename T, typename = void>
struct HasArea : std::false_type {};

template <typename T>
struct HasArea<T, typename std::enable_if<
    std::is_member_function_pointer<decltype(&T::area)>::value>::type
> : std::true_type {};

template <typename T, typename F>
static constexpr int order_areas(const T& a, const F& b) {
    static_assert(HasArea<T>::value, "arg a doesn't have area()");
    static_assert(HasArea<F>::value, "arg b doesn't have area()");
    size_t a_area = a.area();
    size_t b_area = b.area();
    if (a_area == b_area) {
        return 0;
    } else {
        return a_area > b_area ? 1 : -1;
    }
}
static_assert(order_areas(Point{0, 0}, Square{4}) == 0);
