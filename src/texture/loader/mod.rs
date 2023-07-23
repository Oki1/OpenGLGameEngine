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

fn read_u8_array(f: &mut File, n: &usize) -> std::io::Result<Box<[u8]>> {
    let mut data = vec![0u8; *n * std::mem::size_of::<u8>()];
    f.read_exact(&mut data)?;
    Ok(data.into_boxed_slice())
}


//methods

pub fn load_raw_image(filename: &str) -> std::io::Result<((u32, u32), Box<[u8]>)> {
    let mut file = File::open(filename)?;
    let width = read_uint(&mut file)?;
    let height = read_uint(&mut file)?;
    
    // read size of verts

    Ok(( (width, height), read_u8_array(&mut file, &((width*height*4) as usize))? ))
}
