import sys
from PIL import Image
import numpy

def crop_black(img):
    pixels = numpy.array(img.convert('RGB'))
    w, h = img.size

    if numpy.all(pixels <= 10):
     return img
    
   
    top = 0
    while top < h and numpy.all(pixels[top] <=10):
        top += 1
  
    bottom = h - 1
    while bottom >= top and numpy.all(pixels[bottom] <= 10):
        bottom -= 1
        

    left = 0
    while left < w and numpy.all(pixels[0:h, left] <= 10):
        left += 1
  
    right = w - 1
    while right >= left and numpy.all(pixels[0:h, right] <= 10):
        right -= 1
    
    return img.crop((left, top, right+1, bottom+1))

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("3 arguments!")
        sys.exit(1)
        
    try:
        img = Image.open(sys.argv[1]) 
        cropped = crop_black(img)
        cropped.save(sys.argv[2])
       
        
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)