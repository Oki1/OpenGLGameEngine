use std::{fs::read_to_string,
        ptr::null}
;

pub struct Shader {
    pub program: gl::types::GLuint // to be made private once uniforms are moved here.
}

unsafe fn read_and_compile_shader(shader_type: gl::types::GLenum, filename: &str, check_for_errors:bool) -> gl::types::GLuint {
    // unsafe as shader type must be valid
    let buffer = read_to_string(filename).expect("Shader reading failed!");
    let shader = gl::CreateShader(shader_type);
    gl::ShaderSource(shader, 1, [(buffer).as_ptr().cast()].as_ptr(), null());
    gl::CompileShader(shader);
    if check_for_errors {
        let mut log: [u8; 512] = [0;512];
        
        gl::GetShaderInfoLog(shader, 512, null::<i32>() as *mut i32, (&mut log as *mut u8) as *mut i8);
        
        println!("Vertex shader:\n{}", std::str::from_utf8(&log as &[u8]).unwrap());
    }
    shader
}

impl Shader {
    pub fn new (vertex_shader_path: &str, fragment_shader_path: &str, check_for_errors: bool) -> Self {
        unsafe {
            // vertex shader
            let vertex = read_and_compile_shader(gl::VERTEX_SHADER, vertex_shader_path, check_for_errors);
            
            // fragment shader
            let fragment = read_and_compile_shader(gl::FRAGMENT_SHADER, fragment_shader_path, check_for_errors);
            
            // create shader object
            let program = gl::CreateProgram();
            gl::AttachShader(program, vertex);
            gl::AttachShader(program, fragment);
            gl::DeleteShader(fragment);
            gl::DeleteShader(vertex);
            gl::LinkProgram(program); 
            
            Self {
                program
            }
        } 
    }
    pub fn use_program (&self) {
        unsafe {
            gl::UseProgram(self.program);
        }
    }
}
impl Drop for Shader {
    fn drop(&mut self) {
        unsafe {
            gl::DeleteProgram(self.program);
        }
    }
}