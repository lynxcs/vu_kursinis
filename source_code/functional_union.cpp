struct Variant {
    enum variant_type {
        numeric,
        string,
        multi_data
    };
    variant_type type;
    union d {
        uint32_t numeric
        std::string string;
        std::array<uint8_t, 2> multi_data;
    };

    Variant() {
        /* Manual constructor depending on which type*/
    }
    ~Variant() {
        /* Manual destructor depending on which type */
    }
};