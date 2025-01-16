template <typename T>
concept HasArea = requires(T t) {
    { t.area() } -> std::same_as<std::size_t>;
};

static constexpr int order_areas(const HasArea auto& a, const HasArea auto& b) {
    size_t a_area = a.area();
    size_t b_area = b.area();
    if (a_area == b_area) {
        return 0;
    } else {
        return a_area > b_area ? 1 : -1;
    }
}
static_assert(order_areas(Point{0, 0}, Square{4}) == 0);