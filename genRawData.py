from struct import *

#IMPORTANT! EVERYTHING IS IN LITTLE ENDIAN

def gen_raw_data(verts, indices, filename):
    with open(filename, "wb") as f:
        numverts = len(verts)
        f.write(pack("<I", numverts)) # write number of verts
        f.write(pack(f"<{numverts}f", *verts)) # write verts
        numindices = len(indices)
        f.write(pack("<I", numindices))
        f.write(pack(f"<{numindices}I", *indices))
        print("Successfuly written data to file")
        
        
if __name__ == "__main__":
    gen_raw_data([3.0,2.0,1.0], [1,2,3], "test.bin")