use super::mesh::Mesh;

mod loader;
// the model currently only holds the mesh, it will later be able to hold many meshes, animations, textures, shaders(maybe), etc. etc. It will probably be then contained in an gameobject struct;
pub struct Model {
    pub mesh: Mesh
}
impl Model {
    pub fn new() -> Self {
        //implement file loading
        let verts; 
        let indices;
        unsafe{ // the cube file is safe
            //(verts, indices) = loader::load_raw_model("cube.bin").unwrap();   
        }
        (verts, indices) = loader::load_raw_model_checked("cube.bin", 5).unwrap();
        let mesh = Mesh::new(&verts, &indices, 5);
        Self{mesh}
    }
}