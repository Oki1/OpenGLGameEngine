
use std::{ptr,time};

use std::ffi::{CStr, CString};

use glutin::{display::GlDisplay,
    prelude::GlSurface};

extern crate nalgebra_glm as glm;

pub struct Renderer {
    shader_program: gl::types::GLuint,
    vao: gl::types::GLuint,
    vbo: gl::types::GLuint,
    ebo: gl::types::GLuint,
    rot_uniform_location: gl::types::GLuint,
    time_since_last_frame: time::Instant,
}

impl Renderer {
    pub fn new(display: &glutin::display::Display) -> Self {
        const VERTS: [f32;12] = [-0.5, -0.5, 0.0,
                                0.5, -0.5, 0.0,
                                -0.5, 0.5 , 0.0,
                                0.5, 0.5, 0.0
                                ];

        const INDEXES: [u32;6] = [0,1,2,
                                1,2,3];

        const VERTEX_SHADER_SOURCE: &[u8] = b"#version 330 core\n
                                        layout (location = 0) in vec3 aPos;\n
                                        uniform mat4 rotation;\n
                                        void main() {\n;
                                            gl_Position = rotation * vec4(aPos, 1.0f);\n
                                        }\n
                                 \0";

        const FRAGMENT_SHADER_SOURCE: &[u8] = b"#version 330 core //tells pixel colors
                                   out vec4 FragColor;
                                   void main() {
                                       FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
                                    }
                                    \0";
                                    // setup renderer
                                    //put vertext positions into vbo
        let shader_program: gl::types::GLuint;
        let mut vao: gl::types::GLuint;
        let mut vbo: gl::types::GLuint;
        let mut ebo: gl::types::GLuint;
        let mut rot_uniform_location: gl::types::GLuint = 0;
        
        unsafe {
            vao = std::mem::zeroed();
            vbo = std::mem::zeroed();
            ebo = std::mem::zeroed();
            //bind opengl functions
            gl::load_with(|symbol| {
                let symbol = CString::new(symbol).unwrap();
                display.get_proc_address(symbol.as_c_str()).cast()
            });
            //let intsize: gl::types::GLsizeiptr = ;

            // GPU STUFF
            {
                // gen vbo ebo vao
                gl::GenVertexArrays(1, &mut vao);
                gl::GenBuffers(1, &mut vbo);
                gl::GenBuffers(1, &mut ebo);

                //bind vao
                gl::BindVertexArray(vao);
                
                //bind and set vbo
                gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
                gl::BufferData(gl::ARRAY_BUFFER, (VERTS.len() * std::mem::size_of::<f32>()) as gl::types::GLsizeiptr, VERTS.as_ptr() as *const _, gl::STATIC_DRAW);

                //bind and set ebo
                gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);
                gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, (INDEXES.len() * std::mem::size_of::<i32>()) as gl::types::GLsizeiptr, INDEXES.as_ptr() as *const _, gl::STATIC_DRAW);

                //configure vao
                gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE, (3 * std::mem::size_of::<f32>()) as gl::types::GLsizei, 0 as *const _);
                gl::EnableVertexAttribArray(0);

            }
            
            // compile vertex shader
            let vertex_shader = gl::CreateShader(gl::VERTEX_SHADER);
            gl::ShaderSource(vertex_shader, 1, [VERTEX_SHADER_SOURCE.as_ptr().cast()].as_ptr(), std::ptr::null());
            gl::CompileShader(vertex_shader);
            //compile fragment shader
            let fragment_shader = gl::CreateShader(gl::FRAGMENT_SHADER);
            gl::ShaderSource(fragment_shader, 1, [FRAGMENT_SHADER_SOURCE.as_ptr().cast()].as_ptr(), std::ptr::null());
            gl::CompileShader(fragment_shader);

            
            /*
            let mut log: [u8; 512] = [0;512];
            
            gl::GetShaderInfoLog(fragment_shader, 512, ptr::null::<i32>() as *mut i32, (&mut log as *mut u8) as *mut i8);
            
            println!("{}", std::str::from_utf8(&log as &[u8]).unwrap());
            */
            
            // create shader ob
            shader_program = gl::CreateProgram();
            gl::AttachShader(shader_program, vertex_shader);
            gl::AttachShader(shader_program, fragment_shader);
            gl::DeleteShader(fragment_shader);
            gl::DeleteShader(vertex_shader);
            gl::LinkProgram(shader_program);

            let rot: CString = CString::new("rotation").unwrap();
            rot_uniform_location = gl::GetUniformLocation(shader_program, rot.as_ptr()) as u32;
        
        }
        let time_since_last_frame = time::Instant::now();
        Self {
            shader_program, vao, vbo, ebo, rot_uniform_location, time_since_last_frame
        }
    }
    pub fn draw(&mut self, window_surface: &glutin::surface::Surface<glutin::surface::WindowSurface>, context: &glutin::context::PossiblyCurrentContext) {
        unsafe {
            gl::ClearColor(1.0f32, 0f32, 0f32, 1.0f32);
            gl::Clear(gl::COLOR_BUFFER_BIT);
        }
        let now = time::Instant::now();
        let delta_time: f32 = now.duration_since(self.time_since_last_frame).as_millis() as f32;
        //self.time_since_last_frame = now;
        let rotation = glm::rotation::<f32>(delta_time/700.0, &glm::vec3(0.0f32, 0.0f32, -1.0f32));
        
        unsafe{
            gl::UseProgram(self.shader_program);
            gl::BindVertexArray(self.vao);
            gl::DrawElements(gl::TRIANGLES, 6, gl::UNSIGNED_INT, 0 as *const _);
            //gl::DrawArrays(gl::TRIANGLES, 0, 3);
            gl::UniformMatrix4fv(self.rot_uniform_location as i32, 1, gl::FALSE, rotation.as_ptr());
            window_surface.swap_buffers(&context).expect("Swapping buffers failed!");
        }
    }
}

impl Drop for Renderer {
    fn drop(&mut self) {
        
        unsafe {
            gl::DeleteProgram(self.shader_program);
            gl::DeleteBuffers(1, &self.vbo);
            gl::DeleteBuffers(1, &self.ebo);
            gl::DeleteVertexArrays(1, &self.vao);
        }
    }
}
