from PIL import Image, ImageDraw, ImageFont


def draw_line(image, x0, y0, x1, y1, color):
    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    steep = dy > dx
    
    if steep:
        x0, y0 = y0, x0
        x1, y1 = y1, x1
        dx, dy = dy, dx
    
    if x0 > x1:
        x0, x1 = x1, x0
        y0, y1 = y1, y0
    
    delta = 2 * dy - dx
    y = y0
    y_step = 1 if y1 > y0 else -1
    pixels = image.load()
    
    for x in range(x0, x1 + 1):
        
        if steep:
            px, py = y, x
        else:
            px, py = x, y
            
        if 0 <= px < image.width and 0 <= py < image.height:
            pixels[px, py] = color
        
        if delta >= 0:
            y += y_step
            delta -= 2 * dx
        delta += 2 * dy

def draw_circle(image, x0, y0, radius, color):
    x = 0
    y = radius
    d = 5 - 4* radius
    pixels = image.load()
    
    def plot_points(x, y):
            points = [
                (x0 + x , y0 + y), (x0 - x , y0 + y),
                (x0 + x , y0 - y), (x0 - x , y0 - y),
                (x0 + y, y0 + x ), (x0 - y, y0 + x ),
                (x0 + y, y0 - x ), (x0 - y, y0 - x )
            ]
            for px, py in points:
                if 0 <= px < image.width and 0 <= py < image.height:
                    pixels[px, py] = color
    
    while x <= y:
        plot_points(x, y)
        if d < 0:
            d += 8 * x + 12
        else:
            d += 8 * (x - y) + 20
            y -= 1
        x += 1

def draw_coordinate_system(draw, width, height, step):
    axis_color = (200, 200, 200)  
    grid_color = (220, 220, 220)  
    text_color = (100, 100, 100)  
    center_x, center_y = width // 2, height // 2
    
    #сетка
    for x in range(0, width, step):
        draw.line([(x, 0), (x, height)], grid_color, 1)
    for y in range(0, height, step):
        draw.line([(0, y), (width, y)], grid_color, 1)
    
  #оси
    draw.line([(center_x, 0), (center_x, height)], axis_color, 2)  
    draw.line([(0, center_y), (width, center_y)], axis_color, 2)  
    draw.line([(center_x,center_y),(center_x+1,center_y+1)], (50,50,50),2)
    
    font = ImageFont.load_default()
   
    
    # шаги по x
    for x in range(center_x % step, width+step, step):
        if x != center_x:
            value = x - center_x
            draw.text((x - 10 if value < 0 else x - 10, center_y + 10), 
                     str(value), text_color, font)
    
    # шаги по y
    for y in range(center_y % step, height+step, step):
        if y != center_y:
            value = center_y - y
            draw.text((center_x + 10, y - 5 if value > 0 else y -10), 
                     str(value), text_color, font)
    
    # x и y и 0
    draw.text((width - 20, center_y + 5), "X", text_color, font)
    draw.text((center_x + 20,5), "Y", text_color, font)
    draw.text((center_x+10,center_y+10),"0",text_color, font)

def get_input(width, height):
    center_x, center_y = width // 2, height // 2
    
    print("\nenter the coordinates of the segment:")
    while True:
        try:
            x0 = int(input("x1: "))
            y0 = int(input("y1: "))
            x1 = int(input("x2: "))
            y1 = int(input("y2: "))
            break
        except ValueError:
            print("Error: integers")
    
    print("\nenter parameters of circle:")
    while True:
        try:
            circle_x = int(input("center X: "))
            circle_y = int(input("center Y: "))
            radius = int(input("radius: "))
            if radius < 0:  
             print("Error: radius must be positive")
             continue
            break
        except ValueError:
            print("Error: integers")
    
    return (x0, y0, x1, y1), (circle_x, circle_y, radius)

def main():
    try:
        width, height = 800, 600
        img = Image.new('RGB', (width, height), (255, 255, 255))
        draw = ImageDraw.Draw(img)
        
        draw_coordinate_system(draw, width, height,50)

        line, circle = get_input(width, height)
        center_x, center_y = width // 2, height // 2
        
        
        x0, y0, x1, y1 = line
        draw_line(img, center_x + x0, center_y - y0, center_x + x1, center_y - y1, (150, 0, 0))
        
       
        circle_x, circle_y, radius = circle
        draw_circle(img, center_x + circle_x, center_y - circle_y, radius, (0, 150, 0))

        img.save("output1.png")
        print("\n image saved")
        img.show()
        
    except Exception as e:
        print("Error: {e}")

if __name__ == "__main__":
    main()
    