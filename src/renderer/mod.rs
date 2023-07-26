
use std::{ptr,time};

use std::ffi::{CStr, CString};

use glutin::{display::GlDisplay,
    prelude::GlSurface};

use crate::model::Model;
use crate::shader;

use super::camera::Camera;
use super::mesh::Mesh;
use super::model;
use super::texture::Texture;
use super::shader::Shader;
extern crate nalgebra_glm as glm;

pub struct Renderer {
    shader: Shader,
/*     vao: gl::types::GLuint,
    vbo: gl::types::GLuint,
    ebo: gl::types::GLuint, */
    time_since_last_frame: time::Instant,
    model: glm::Mat4,
    projection: glm::Mat4,
    model_uniform: gl::types::GLuint,
    view_uniform: gl::types::GLuint,
    projection_uniform: gl::types::GLuint,
    //cam_pos: glm::vec3;

    cube_object: Model,
    test_texture: Texture
}

impl Renderer {
    pub fn new(display: &glutin::display::Display) -> Self {     

        // setup renderer
        //put vertext positions into vbo
        /*         let mut vao: gl::types::GLuint;
        let mut vbo: gl::types::GLuint;
        let mut ebo: gl::types::GLuint; */
        
        let mut model_uniform;
        let mut view_uniform;
        let mut projection_uniform;
        
        unsafe {/* 
            vao = std::mem::zeroed();
            vbo = std::mem::zeroed();
            ebo = std::mem::zeroed(); */
            //bind opengl functions
            gl::load_with(|symbol| {
                let symbol = CString::new(symbol).unwrap();
                display.get_proc_address(symbol.as_c_str()).cast()
            });
        }
        let shader = Shader::new("tex.vs", "tex.fs", true);
        unsafe {
            //MAKE THIS DYNAMIC
            //gl::Viewport(0,0, 2560, 1440); // set viewport, currently fixed
            
            
            gl::Enable(gl::DEPTH_TEST);
            //let intsize: gl::types::GLsizeiptr = ;
            
            // GPU STUFF
            /* {
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
                
            } */            
            let mut s: CString = CString::new("model").unwrap();
            model_uniform = gl::GetUniformLocation(shader.program, s.as_ptr()) as u32;
            s = CString::new("view").unwrap();
            view_uniform = gl::GetUniformLocation(shader.program, s.as_ptr()) as u32;
            s = CString::new("projection").unwrap();
            projection_uniform = gl::GetUniformLocation(shader.program, s.as_ptr()) as u32;
            
            
            
        }
        let time_since_last_frame = time::Instant::now();
        
        let model = glm::identity::<f32, 4>();
        let projection = glm::perspective::<f32>(16f32/9f32, 70.0f32.to_radians(), 0.1f32, 100.0f32);
        
        //let cam_pos = glm::vec3(0.0f32, 0.0f32, 0.0f32);
        //let mesh = Mesh::new(&VERTS, &INDICES);

        let cube_object = model::Model::new();
        let test_texture = Texture::new();
        
        Self {
            shader, time_since_last_frame, model_uniform, view_uniform, projection_uniform, model, projection, cube_object, test_texture
        }
    }
    
    pub fn resize_window(&mut self, width: i32, height: i32) {
        self.projection = glm::perspective::<f32>(width as f32/height as f32, 70.0f32.to_radians(), 0.1f32, 100.0f32);
        unsafe{
            gl::Viewport(0,0, width, height); // set viewport
        }
    }

    pub fn draw(&mut self, window_surface: &glutin::surface::Surface<glutin::surface::WindowSurface>, context: &glutin::context::PossiblyCurrentContext, camera: &mut Camera) {
        unsafe {
            gl::ClearColor(0.6f32, 0.6f32, 0.6f32, 1.0f32);
            gl::Clear(gl::COLOR_BUFFER_BIT|gl::DEPTH_BUFFER_BIT);
        }
        let now = time::Instant::now();
        //self.time_since_last_frame = now;
        
        unsafe{
            // bind texture to TEXTURE0
            gl::ActiveTexture(gl::TEXTURE0);
            gl::BindTexture(gl::TEXTURE_2D, self.test_texture.texture_id);
            
            
            self.shader.use_program();

            //gl::DrawArrays(gl::TRIANGLES, 0, 3);
            gl::UniformMatrix4fv(self.model_uniform as i32, 1, gl::FALSE, self.model.as_ptr());
            gl::UniformMatrix4fv(self.view_uniform as i32, 1, gl::FALSE, camera.view_matrix.as_ptr());
            gl::UniformMatrix4fv(self.projection_uniform as i32, 1, gl::FALSE, self.projection.as_ptr());

            gl::BindVertexArray(self.cube_object.mesh.vao);


            gl::DrawElements(gl::TRIANGLES, 36, gl::UNSIGNED_INT, 0 as *const _);




            window_surface.swap_buffers(&context).expect("Swapping buffers failed!");
        }
    }
}


impl Drop for Renderer {
    fn drop(&mut self) {
        unsafe {
            /* 
            gl::DeleteProgram(self.shader_program);
            gl::DeleteBuffers(1, &self.vbo);
            gl::DeleteBuffers(1, &self.ebo);
            gl::DeleteVertexArrays(1, &self.vao); */
        }
    }
}
