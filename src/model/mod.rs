use super::mesh::Mesh;

mod loader;
// the model currently only holds the mesh, it will later be able to hold many meshes, animations, textures, shaders(maybe), etc. etc. It will probably be then contained in an gameobject struct;
pub struct Model {
    //mesh: Mesh
}
impl Model {
    pub fn new() -> Self {
        //implement file loading
        unsafe{
            loader::load_raw_model("test.bin");
        }
        Self{}
    }
}