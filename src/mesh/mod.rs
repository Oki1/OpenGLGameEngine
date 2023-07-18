pub struct Mesh {
    pub vao: gl::types::GLuint,
    vbo: gl::types::GLuint,
    ebo: gl::types::GLuint,
}

impl Mesh {
    pub fn new(verts: &[f32], indices: &[i32]) -> Self {
        let mut vao = 0;
        let mut vbo = 0;
        let mut ebo = 0;
        unsafe { // LOAD VERTICES AND IDICES ONTO GPU
            // gen vbo ebo vao
            gl::GenVertexArrays(1, &mut vao);
            gl::GenBuffers(1, &mut vbo);
            gl::GenBuffers(1, &mut ebo);

            //bind vao
            gl::BindVertexArray(vao);
            
            //bind and set vbo
            gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
            gl::BufferData(gl::ARRAY_BUFFER, (verts.len() * std::mem::size_of::<f32>()) as gl::types::GLsizeiptr, verts.as_ptr() as *const _, gl::STATIC_DRAW);

            //bind and set ebo
            gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);
            gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, (indices.len() * std::mem::size_of::<i32>()) as gl::types::GLsizeiptr, indices.as_ptr() as *const _, gl::STATIC_DRAW);

            //configure vao
            gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE, (3 * std::mem::size_of::<f32>()) as gl::types::GLsizei, 0 as *const _);

            gl::EnableVertexAttribArray(0);
            gl::BindVertexArray(0);
        }
        Self {
            vao, vbo, ebo
        }
    }
}

impl Drop for Mesh {
    fn drop(&mut self) {
        unsafe {
            gl::DeleteBuffers(1, &self.vbo);
            gl::DeleteBuffers(1, &self.ebo);
            gl::DeleteVertexArrays(1, &self.vao);
        }
    }
}