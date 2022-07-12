// Given two arrays a and b write a function comp(a, b) (orcompSame(a, b)) that 
// checks whether the two arrays have the "same" elements, with the same multiplicities 
// (the multiplicity of a member is the number of times it appears). "Same" means, here, 
// that the elements in b are the elements in a squared, regardless of the order.

// Example
// Valid arrays
// a = [121, 144, 19, 161, 19, 144, 19, 11]  
// b = [121, 14641, 20736, 361, 25921, 361, 20736, 361]

// comp(a, b) returns true because in b 121 is the square of 11, 14641 is the square of 121,

fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    let mut a_squared = a.iter().map(|&x| x * x).collect::<Vec<_>>();
    a_squared.sort_unstable();
    b.sort_unstable();
    return a_squared == b;
}