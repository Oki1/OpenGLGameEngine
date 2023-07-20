/* raw file type contains raw vertices and indices information to be loaded directly into a VBO and EBO. 
The file looks like the following:
ui32 -> number of floats in indices block
f32 * size -> vertices
ui32 -> number of uints in indices block
ui32 * size -> indices

all the values are tightly packed and little endian
*/

use std::fs::File;
use std::io::Read;
use byteorder::{ByteOrder, LittleEndian};

/*pub fn load_raw_model_checked(filename: str) {

}*/

// helper functions
fn read_uint(f: &mut File) -> u32 {
    let mut raw = [0u8;4];
    f.read_exact(&mut raw).expect("Reading u32 from file failed!");
    u32::from_le_bytes(raw)
}

fn read_f32_array(f: &mut File, n: &usize) -> Box<[f32]> {
    let mut verts_raw = vec![0u8; *n* std::mem::size_of::<f32>()];
    let mut verts_vec = vec![0f32; *n];
    f.read_exact(&mut verts_raw).expect("Reading float array from file failed!");
    LittleEndian::read_f32_into(&verts_raw, &mut verts_vec);
    verts_vec.into_boxed_slice()
}

fn read_i32_array(f: &mut File, n: &usize) -> Box<[i32]> {
    let mut indices_raw = vec![0u8; *n * std::mem::size_of::<f32>()];
    let mut indices_vec = vec![0i32; *n];
    f.read_exact(&mut indices_raw).expect("Reading integer array from file failed!");
    LittleEndian::read_i32_into(&indices_raw, &mut indices_vec);
    indices_vec.into_boxed_slice()
}


//methods
// unsafe as there is no check if the file is correctly structured. Indices could be out of range
pub unsafe fn load_raw_model(filename: &str) -> std::io::Result<(Box<[f32]>, Box<[i32]>)>{
    let mut file = File::open(filename)?;

    // read size of verts
    let n_verts = read_uint(&mut file);


    let verts = read_f32_array(&mut file, &(n_verts as usize));


    let n_indices = read_uint(&mut file);
    let indices = read_i32_array(&mut file, &(n_indices as usize));

    Ok((verts, indices))
}