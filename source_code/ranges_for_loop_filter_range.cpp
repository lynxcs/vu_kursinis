static double transform_number(int input);
static void print(double val);
void operate(const auto &container, size_t offset, double early_exit) {
    /* Skip first 3 elements (container.begin() + offset isn't supported for all iterator types) */
    std::find_if(std::next(container.begin(), offset), container.end(), [&](int val) {
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
        print(transformed);
        return false;
    });
}