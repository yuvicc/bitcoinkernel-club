use bitcoinkernel::{TxOut, KernelError};

fn verify_script(
    prev_script_hex: &str,
    spending_tx_hex: &str,
    prev_amount: i64,
    input_index: usize,
    outputs: Vec<TxOut>,
    flags: u32
)   -> Result<(), KernelError> {
    let prev_script_bytes = hex
}


fn main() {
    println!("Hello, world!");
}
