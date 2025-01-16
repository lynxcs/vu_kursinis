template <typename T>
struct optional_base {
    /* <impl details> */
};

template <typename T>
struct optional_trivial
: public optional_base<T>{
    /* if trivial destr - do nothing */
    ~optional_trivial() = default;
};

template <typename T>
struct optional_nontrivial
: public optional_base<T> {
    /* else only call destr if activated */
    ~optional_nontrivial() {
        if (this->has_value()) {
            this->value.~T();
        }
    }
};

template <typename T>
using optional = std::conditional_t<
    std::is_trivially_destructible_v<T>,
    optional_trivial<T>,
    optional_nontrivial<T>
>;