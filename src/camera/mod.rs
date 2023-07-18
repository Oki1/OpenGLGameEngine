extern crate nalgebra_glm as glm;

pub struct Camera {
    pub forward:bool,
    pub back:bool,
    pub left:bool,
    pub right:bool,
    pub up:bool,
    pub down:bool,

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
        
        let forward = false;
        let back = false;
        let left = false;
        let right = false;
        let up = false;
        let down = false;

        Self {forward, back, left, right, up, down, pos, view_matrix, changed}
    }


    pub fn update_queued_move(&mut self) {
        const SPEED: f32 = 0.1f32;
        self.pos += glm::vec3::<f32>((self.right as i32 -self.left as i32) as f32, (self.up as i32-self.down as i32) as f32, (self.forward as i32-self.back as i32) as f32)*SPEED;
        self.changed = true;
    }
    /*
    pub fn move_cam(&mut self, x: f32, y: f32, z: f32){
        self.pos += glm::vec3(x,y,z);
        self.changed = true;
    } */
    pub fn get_view_matrix(&mut self) -> &glm::Mat4 {
        if(self.changed) {
            self.view_matrix = glm::translation::<f32>(&self.pos);
        }
        &self.view_matrix
    }
}