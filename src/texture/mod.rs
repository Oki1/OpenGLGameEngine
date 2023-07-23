pub struct Texture {
    pub id: gl::types::GLuint
}
use image::EncodableLayout;
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
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER,   gl::LINEAR as i32);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER,   gl::LINEAR as i32);

            let ((width, height), data) = loader::load_raw_image("test_image.bin").unwrap();    
            println!("{:?}\n{:?}\n{:?}", width, height, data);
            let img = image::open("test.png").unwrap().into_rgba8();
            gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA as i32, 100, 100, 0, gl::RGBA, gl::UNSIGNED_BYTE, img.as_bytes().as_ptr() as *const _);//Box::into_raw(data) as *mut std::ffi::c_void);
            gl::GenerateMipmap(gl::TEXTURE_2D);
        }

        Self {id: texture_id}
    }
}
impl Drop for Texture {
    fn drop(&mut self) {
        unsafe {
            gl::DeleteTextures(1, [self.id].as_ptr());
        }
    }
}