static std::expected<int, std::string_view>
perform_calculation(int input) {
    if (input % 2 != 0) {
        return std::unexpected{
            "Input must be odd"
        };
    }
    return input * 3;
}

static void
use_expected(int input) {
    auto res = perform_calculation(input);
    if (res) {
        std::print("{}", *res);
    } else {
        std::print("Err: {}",
            res.error());
    }
}