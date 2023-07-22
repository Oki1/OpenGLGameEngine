from struct import *
from PIL import Image

#IMPORTANT! EVERYTHING IS IN LITTLE ENDIAN
# if you use this for big files you will not have a great time



def generate_image_data(image_filename, out_filename):
    """def gen_raw_data(floats, filename):
        with open(filename, "wb") as f:
            f.write(pack(f"<{len(floats)}f", *floats))
            print(f"Successfuly written data to {filename}")
    """
    with Image.open(image_filename) as im:
        data = []
        for rgb in list(im.getdata()): #add alpha
            data += list(map(lambda x: float(x), list(rgb))) + [255.0]
        
        with open(out_filename, "wb") as f:
            f.write(pack(f"<2I", *im.size))
            f.write(pack(f"<{len(data)}f", *data))
        print(f"Successfully wrote to {out_filename}")
    
        
if __name__ == "__main__": 
    generate_image_data("test.png", "test_image.bin")