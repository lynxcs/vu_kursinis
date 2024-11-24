static double transform_number(int input) {
    return input * 5;
}

int main() {
    static constexpr auto nums = std::array{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    operate_ranges(nums, 3, 45.0);
    return 0;
}