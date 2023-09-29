const HOST: &str = "kpovel.vercel.app";

use std::{
    error::Error,
    process::{Command, Output},
};

fn ping(host: &str) -> Result<Output, Box<dyn Error>> {
    let output = Command::new("ping").arg("-c").arg("3").arg(host).output()?;

    return Ok(output);
}

fn main() {
    for _ in 0..5 {
        match ping(HOST) {
            Ok(output) => {
                let stdout = String::from_utf8_lossy(&output.stdout);
                println!("{}", stdout);
            }
            Err(_) => println!("Ping to {} failed", HOST),
        }
    }
}
