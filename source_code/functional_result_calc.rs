fn perform_calculation
        (input: i32)
        -> Result<i32, &'static str> {
    if input % 2 != 0 {
        Err("Input must be odd")
    } else {
        Ok(input * 3)
    }
}

fn use_result(input: i32) {
    match perform_calculation(input) {
        Ok(res)
            => println!("{}", res),
        Err(msg)
            => println!("Err: {}", msg),
    }
}