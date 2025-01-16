using DataType =
    std::variant<uint32_t, std::array<uint8_t, 2>, std::string>;

template<class... Ts>
struct overloaded
    : Ts... { using Ts::operator()...; };

void dispatch(const DataType &data) {
    std::visit(overloaded{
        [](uint32_t num)
            { std::print("Numeric: {}\n", num); },
        [](const std::array<uint8_t, 2> &arr)
            { std::print("Multi: {} {}\n", arr[0], arr[1]); },
        [](const std::string &str)
            { std::print("String: {}\n", str); }
    }, data);
}