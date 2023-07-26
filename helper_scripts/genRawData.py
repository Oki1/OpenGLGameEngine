from struct import *
import pywavefront

#IMPORTANT! EVERYTHING IS IN LITTLE ENDIAN

def gen_raw_data(verts, indices, filename):
    with open(filename, "wb") as f:
        numverts = len(verts)
        f.write(pack("<I", numverts)) # write number of verts
        f.write(pack(f"<{numverts}f", *verts)) # write verts
        numindices = len(indices)
        f.write(pack("<I", numindices))
        f.write(pack(f"<{numindices}i", *indices))
        print(f"Successfuly written data to {filename}")
        

        

if __name__ == "__main__": # cube
    """#POS                            TEXTURE COORDS
    # X Y Z                         TEXX TEXY
    indices = []
    vertices = []
    scene = pywavefront.Wavefront("cube.obj", collect_faces=True)
    mesh = list(scene.meshes.values())[0]
    assert mesh.materials[0].vertex_format == "T2F_V3F"
    verts_all = mesh.materials[0].vertices
    for face in mesh.faces:
       indices+=face
    for x in range(len(verts_all) // 5):
        a = x*5
        vertices += [verts_all[a+2] ,verts_all[a+3] , verts_all[a+4] , verts_all[a] , verts_all[a+1]]
        print([verts_all[a+2:a+5] + verts_all[a:a+2]])
    #print(vertices)
    print(indices)
        
        #vertices += erts_all[x:x+2]
    
    gen_raw_data(
        vertices,
      indices, "cube.bin")"""
    
    gen_raw_data(
        [-1.0,-1.0,-1.0, 0.0, 0.0,
     1.0,-1.0,-1.0, 1.0, 0.0,
     1.0, 1.0,-1.0, 2.0, 0.0,
    -1.0, 1.0,-1.0, 3.0, 0.0,
    -1.0,-1.0,-1.0, 4.0, 0.0,

    -1.0,-1.0, 1.0, 0.0, 1.0,
     1.0,-1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 2.0, 1.0,
    -1.0, 1.0, 1.0, 3.0, 1.0,
    -1.0,-1.0, 1.0, 4.0, 1.0,

    -1.0, 1.0,-1.0, 0.0,-1.0,
     1.0, 1.0,-1.0, 1.0,-1.0,

    -1.0, 1.0, 1.0, 0.0, 2.0,
     1.0, 1.0, 1.0, 1.0, 2.0],
      [0, 1, 5,  5, 1, 6,
     1, 2, 6,  6, 2, 7,
     2, 3, 7,  7, 3, 8,
     3, 4, 8,  8, 4, 9,
    10,11, 0,  0,11, 1,
     5, 6,12, 12, 6,13], "cube.bin")