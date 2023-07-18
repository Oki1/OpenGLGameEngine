use crate::camera;

extern crate nalgebra_glm as glm;

pub struct Camera {
    pub forward:bool,
    pub back:bool,
    pub left:bool,
    pub right:bool,
    pub up:bool,
    pub down:bool,

    pitch: f32,
    yaw: f32,

    pos: glm::Vec3,
    pub view_matrix: glm::Mat4,
    changed: bool
}

impl Camera {
    pub fn new() -> Self {
        let pos = glm::vec3(0.0, 0.0, 0.0);
        let view_matrix = glm::identity::<f32, 4>();
        let changed = true;
        let pitch = 0.0;
        let yaw = 0.0;

        let forward = false;
        let back = false;
        let left = false;
        let right = false;
        let up = false;
        let down = false;

        Self {forward, back, left, right, up, down, pitch, yaw, pos, view_matrix, changed}
    }
    pub fn new_from_position(x:f32, y:f32, z:f32) -> Self {
        let pos = glm::vec3(x,y,z);
        let view_matrix = glm::identity::<f32, 4>();
        let changed = true;
        let pitch = 0.0;
        let yaw = 0.0;
        
        let forward = false;
        let back = false;
        let left = false;
        let right = false;
        let up = false;
        let down = false;

        Self {forward, back, left, right, up, down, pitch, yaw, pos, view_matrix, changed}
    }

    pub fn mouseMove(&mut self, delta: (f64, f64)) {
        const MOUSE_SENS: f32 = 0.1;
        self.changed = true;
        let (x,y) = delta;
        self.pitch += MOUSE_SENS*y as f32;
        self.yaw += MOUSE_SENS*x as f32;
    }


    pub fn update_queued_move(&mut self) {
        if self.changed || self.up || self.right || self.down || self.back || self.forward || self.left{
            const SPEED: f32 = 0.1f32;
            let camera_forward = glm::normalize(&glm::vec3(self.yaw.to_radians().sin(), self.pitch.to_radians().sin(), -(self.yaw.to_radians().cos() * self.pitch.to_radians().cos())));
            let camera_up = glm::vec3(0.0, 1.0, 0.0);
            let camera_right = glm::cross(&camera_up, &camera_forward);
            println!("{} {} {}", self.pos.x+camera_forward.x, self.pos.y+camera_forward.y, self.pos.z+camera_forward.z);
            
            // update camera position from queued movements
            self.pos += SPEED * (self.down as i32 - self.up as i32) as f32 * camera_up;
            self.pos += SPEED * (self.left as i32 - self.right as i32) as f32 * camera_right;
            self.pos += SPEED * (self.back as i32 - self.forward as i32) as f32 * camera_forward;  // reversed because we need to move everything the other way
            
            // calculate new view matrix
            self.view_matrix = glm::look_at(&self.pos, &(self.pos - camera_forward), &camera_up); // why do i have to substract and not add camera forward? i dont know. I think i am calculating camera backwards by mistake
            /*self.view_matrix = glm::identity::<f32, 4>();
            self.view_matrix = glm::translate(&self.view_matrix, &self.pos);*/
            self.changed = false;
        }
    }
    /*
    pub fn move_cam(&mut self, x: f32, y: f32, z: f32){
        self.pos += glm::vec3(x,y,z);
        self.changed = true;
    } */
    /*pub fn get_view_matrix(self) -> &glm::Mat4 {
        &self.view_matrix
    }*/
}