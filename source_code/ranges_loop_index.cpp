void operate(std::span<uint32_t> values) {
    for (size_t i = 0; i < values.size(); ++i) {
        std::print("Value: {}", values[i]);
    }
}