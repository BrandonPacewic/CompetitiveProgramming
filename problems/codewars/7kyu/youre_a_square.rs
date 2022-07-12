// If number is a square, return true else false

fn is_square(n: i64) -> bool {
    let sqrt = (n as f64).sqrt();
    return sqrt.fract() == 0.0
}