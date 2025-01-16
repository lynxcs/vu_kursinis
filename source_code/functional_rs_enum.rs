enum DataType {
    Numeric(u32),
    MultiData(u8, u8),
    Text(String),
}

fn dispatch(data: DataType) {
    use crate::DataType::*;
    match data {
        Numeric(num)
            => println!("Numeric: {}", num),
        MultiData(d1, d2)
            => println!("Multi: {},{}", d1, d2),
        Text(string)
            => println!("String: {}", string)
    }
}