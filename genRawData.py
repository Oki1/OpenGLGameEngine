from struct import *

#IMPORTANT! EVERYTHING IS IN LITTLE ENDIAN

def gen_raw_data(verts, indices, filename):
    with open(filename, "wb") as f:
        numverts = len(verts)
        f.write(pack("<I", numverts)) # write number of verts
        f.write(pack(f"<{numverts}f", *verts)) # write verts
        numindices = len(indices)
        f.write(pack("<I", numindices))
        f.write(pack(f"<{numindices}i", *indices))
        print("Successfuly written data to file")
        
        
if __name__ == "__main__": # cube
    gen_raw_data([-1.0,  1.0, -1.0,
        1.0,  1.0, -1.0,
       -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
       -1.0,  1.0,  1.0,
       1.0,  1.0,  1.0,
       -1.0, -1.0,  1.0,
       1.0, -1.0,  1.0], [0, 1, 2,
       2, 1, 3,
       4, 0, 6,
       6, 0, 2,
       7, 5, 6,
       6, 5, 4,
       3, 1, 7,
       7, 1, 5,
        4, 5, 0,
        0, 5, 1,
        3, 7, 2,
        2, 7, 6], "cube.bin")