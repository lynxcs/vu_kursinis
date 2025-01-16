static std::optional<int>
perform_calculation(int input) {
    if (input % 2 != 0) {
        return std::nullopt;
    }
    return input * 3;
}

static void
use_optional(int input) {
    auto res = perform_calculation(input);
    if (res) {
        std::cout << *res;
    } else {
        std::cout << "error";
    }
}