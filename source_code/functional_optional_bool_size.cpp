/* Compilation will fail if
size isn't equal to 2 */
static_assert(
    sizeof(std::optional<bool>) == 2
);
