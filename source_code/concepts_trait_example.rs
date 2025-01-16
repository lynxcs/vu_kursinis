struct Point {
    pub x: u32,
    pub y: u32
}

struct Square {
    pub size: u32
}

trait HasArea {
    fn area(&self) -> u32;
}

impl HasArea for Square {
    fn area(&self) -> u32 {
        self.size * self.size
    }
}

fn order_areas(a: &impl HasArea, b: &impl HasArea) -> i32 {
    let a_area = a.area();
    let b_area = b.area();
    if a_area == b_area {
        0
    } else if a_area > b_area {
        1
    } else {
        -1
    }
}

fn try_order(a: &Point, b: &Square) -> i32 {
    /* Won't compile - Point
    doesn't have `HasArea`
    trait implemented*/
    order_areas(a, b)
}