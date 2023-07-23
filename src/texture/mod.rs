pub struct Texture {
    texture_id: gl::types::GLuint
}

mod loader;

impl Texture {
    pub fn new() -> Self {
        let mut texture_id = 0;
        unsafe { // is safe if it is run after the opengl functions have been loaded
            // gen and bind texture
            gl::GenTextures(1, &mut texture_id); 
            gl::BindTexture(gl::TEXTURE_2D, texture_id);
            // set how texture acts
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S,       gl::REPEAT as i32);	
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T,       gl::REPEAT as i32);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER,   gl::LINEAR_MIPMAP_LINEAR as i32);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER,   gl::LINEAR as i32);

            let ((width, height), data) = loader::load_raw_image("test_image.bin").unwrap();
            gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA as i32, width as i32, height as i32, 0, gl::RGBA, gl::FLOAT, Box::into_raw(data) as *mut std::ffi::c_void);
        }
        //println!("{:?}\n{:?}\n{:?}", width, height, data);

        Self {texture_id}
    }
}