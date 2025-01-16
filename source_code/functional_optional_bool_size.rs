/* Compilation will fail if
size isn't equal to 1 */
const SizeChecker: [u8; 1]
= [0; std::mem::size_of::<Option<bool>>()];
