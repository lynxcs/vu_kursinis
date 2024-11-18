void operate(const auto &container) {
    for (const auto& x : container) {
        std::print("Value: {}", x);
    }
}