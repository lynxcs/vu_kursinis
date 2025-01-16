static double transform_number(int input);
static void print(double val);
void operate(const auto &container, size_t offset, double early_exit) {
    auto elems = container
        | std::views::drop(offset)
        | std::views::filter(is_odd)
        | std::views::transform(transform_number)
        | std::views::take_while([&](auto v){return v != early_exit;});
    std::ranges::for_each(elems,print);
}