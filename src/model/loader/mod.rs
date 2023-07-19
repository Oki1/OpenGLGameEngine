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

// unsafe as there is no check if the file is correctly structured
pub unsafe fn load_raw_model(filename: &str) -> std::io::Result<(Box<[f32]>, Box<[i32]>)>{
    let mut file = File::open(filename).unwrap();

    // read size of verts
    let n_verts: u32;
    {
        let mut raw: [u8; 4] = std::mem::zeroed();
        file.read_exact(&mut raw);
        n_verts = u32::from_le_bytes(raw);
    }   
    println!("{}", n_verts);
    let verts: Box<[f32]>;
    {
        let mut verts_raw = vec![0u8; n_verts as usize * std::mem::size_of::<f32>()];
        let mut verts_vec = vec![0f32; n_verts as usize];
        file.read_exact(&mut verts_raw);
        LittleEndian::read_f32_into(&verts_raw, &mut verts_vec);
        verts = verts_vec.into_boxed_slice();
    }
    println!("{:?}", verts);


    let n_indices: u32;
    {
        let mut raw: [u8; 4] = std::mem::zeroed();
        file.read_exact(&mut raw);
        n_indices = u32::from_le_bytes(raw);
    }   
    println!("{}", n_indices);
    let indices: Box<[i32]>;
    {
        let mut indices_raw = vec![0u8; n_indices as usize * std::mem::size_of::<f32>()];
        let mut indices_vec = vec![0i32; n_indices as usize];
        file.read_exact(&mut indices_raw);
        LittleEndian::read_i32_into(&indices_raw, &mut indices_vec);
        indices = indices_vec.into_boxed_slice();
    }
    println!("{:?}", indices);

    Ok((verts, indices))
}