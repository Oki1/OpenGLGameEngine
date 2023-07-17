extern crate nalgebra_glm as glm;

pub struct Camera {
    forward: bool,
    back: bool,
    left: bool,
    right: bool,
    up: bool,
    down: bool,

    pos: glm::Vec3,
    view_matrix: glm::Mat4,
    changed: bool
}

impl Camera {
    pub fn new() -> Self {
        let pos = glm::vec3(0.0, 0.0, 0.0);
        let view_matrix = glm::identity::<f32, 4>();
        let changed = false;

        let forward = false;
        let back = false;
        let left = false;
        let right = false;
        let up = false;
        let down = false;

        Self {forward, back, left, right, up, down, pos, view_matrix, changed}
    }
    pub fn new_from_position(x:f32, y:f32, z:f32) -> Self {
        let pos = glm::vec3(x,y,z);
        let view_matrix = glm::identity::<f32, 4>();
        let changed = true;
        Self {pos, view_matrix, changed}
    }

    pub fn move_cam_by_vector(&mut self, delta: glm::Vec3) {
        self.pos += delta;
        self.changed = true;
    }
    pub fn move_cam(&mut self, x: f32, y: f32, z: f32){
        self.pos += glm::vec3(x,y,z);
        self.changed = true;
    }
    pub fn get_view_matrix(&mut self) -> &glm::Mat4 {
        if(self.changed) {
            self.view_matrix = glm::translation::<f32>(&self.pos);
        }
        &self.view_matrix
    }
}