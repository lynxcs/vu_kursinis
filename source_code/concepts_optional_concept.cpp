template <typename T>
struct optional {
    /* <impl details>*/
    
    /* if trivial destr - do nothing */
    ~optional() requires
        std::is_trivially_destructible_v<T>
            = default;

    /* else only call destr if activated */
    ~optional() {
        if (has_value()) {
            value.~T();
        }
    }
};