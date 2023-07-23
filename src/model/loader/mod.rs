/* raw file type contains raw vertices and indices information to be loaded directly into a VBO and EBO. 
The file looks like the following:
ui32 -> number of floats in indices block
f32 * size -> vertices
ui32 -> number of uints in indices block
ui32 * size -> indices

all the values are tightly packed and little endian
*/

use std::fs::File;
use std::io::{Read, Error, ErrorKind};
use byteorder::{ByteOrder, LittleEndian};

/*pub fn load_raw_model_checked(filename: str) {

}*/

// helper functions
fn read_uint(f: &mut File) -> std::io::Result<u32> {
    let mut raw = [0u8;4];
    f.read_exact(&mut raw)?;
    Ok(u32::from_le_bytes(raw))
}

fn read_f32_array(f: &mut File, n: &usize) -> std::io::Result<Box<[f32]>> {
    let mut verts_raw = vec![0u8; *n* std::mem::size_of::<f32>()];
    let mut verts_vec = vec![0f32; *n];
    f.read_exact(&mut verts_raw)?;
    LittleEndian::read_f32_into(&verts_raw, &mut verts_vec);
    Ok(verts_vec.into_boxed_slice())
}

fn read_i32_array(f: &mut File, n: &usize) -> std::io::Result<Box<[i32]>> {
    let mut indices_raw = vec![0u8; *n * std::mem::size_of::<i32>()];
    let mut indices_vec = vec![0i32; *n];
    f.read_exact(&mut indices_raw)?;
    LittleEndian::read_i32_into(&indices_raw, &mut indices_vec);
    Ok(indices_vec.into_boxed_slice())
}


//methods

pub fn load_raw_model_checked(filename: &str, vertex_size: u32) -> std::io::Result<(Box<[f32]>, Box<[i32]>)> {
    let mut file = File::open(filename)?;

    // read size of verts
    let size_of_vertex_array = read_uint(&mut file)?;

    if size_of_vertex_array % vertex_size != 0 {
        return Err(Error::new(ErrorKind::InvalidData, "Number of floats in vertex data is not divisible by size of vertex!"))
    }

    let verts = read_f32_array(&mut file, &(size_of_vertex_array as usize))?;


    let size_of_index_array = read_uint(&mut file)?; 

    if size_of_index_array % 3 != 0 {
        return Err(Error::new(ErrorKind::InvalidData, "Number if u32 in elements array is not divisible by 3!"))
    }

    let indices = read_i32_array(&mut file, &(size_of_index_array as usize))?;
    // check if indices are in range
    let n_vertices = size_of_vertex_array / vertex_size;
    for index in indices.iter() {
        if *index >= n_vertices as i32  || *index < 0 {
            return Err(Error::new(ErrorKind::InvalidData, "Index data out of range!"));
        }
    }

    Ok((verts, indices))
}

// unsafe as there is no check if the file is correctly structured. Indices could be out of range
pub unsafe fn load_raw_model(filename: &str) -> std::io::Result<(Box<[f32]>, Box<[i32]>)>{
    let mut file = File::open(filename)?;

    // read size of verts
    let size_of_vertex_array = read_uint(&mut file)?;


    let verts = read_f32_array(&mut file, &(size_of_vertex_array as usize))?;


    let size_of_index_array = read_uint(&mut file)?;
    let indices = read_i32_array(&mut file, &(size_of_index_array as usize))?; // there is no check if indices are in range

    Ok((verts, indices))
}