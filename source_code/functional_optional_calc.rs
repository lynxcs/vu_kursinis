fn perform_calculation
        (input: i32)-> Option<i32> {
    if input % 2 != 0 {
        None
    } else {
        Some(input * 3)
    }
}

fn use_optional(input: i32) {
    match perform_calculation(input) {
        Some(res) => println!("{}", res),
        None => println!("error"),
    }
}