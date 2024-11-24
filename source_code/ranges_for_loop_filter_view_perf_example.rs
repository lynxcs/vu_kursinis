fn operate_ranges<T>(
    container: T, 
    offset: usize, 
    early_exit: f64, 
) where
    T: IntoIterator<Item = i32>,
{
    container.into_iter()
        .skip(offset)
        .filter(|&v| { is_odd(v) })
        .map(|v| { transform_number(v) })
        .take_while(|&v| { v != early_exit})
        .for_each(|v| print(v));
}