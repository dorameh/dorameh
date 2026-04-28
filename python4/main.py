# #!/usr/bin/env python3

# import sys
# from PIL import Image
# import numpy as np

# def is_black_row(row):
#     # Проверяет, вся ли строка состоит из черных пикселей (0,0,0)
#     return np.all(row[:, :3] == 0) if row.shape[1] >= 3 else np.all(row == 0)

# def is_black_col(col):
#     # Проверяет, весь ли столбец состоит из черных пикселей (0,0,0)
#     return np.all(col[:, :3] == 0) if col.shape[1] >= 3 else np.all(col == 0)

# def crop_black_borders(im):
#     # Переводим изображение в RGB и массив numpy
#     arr = np.asarray(im.convert('RGB'))
#     h, w, _ = arr.shape

#     # Верхняя граница
#     top = 0
#     while top < h and is_black_row(arr[top]):
#         top += 1

#     # Нижняя граница
#     bottom = h - 1
#     while bottom >= top and is_black_row(arr[bottom]):
#         bottom -= 1

#     # Левая граница
#     left = 0
#     while left < w and is_black_col(arr[:, left]):
#         left += 1

#     # Правая граница
#     right = w - 1
#     while right >= left and is_black_col(arr[:, right]):
#         right -= 1

#     # Обрезаем
#     cropped = im.crop((left, top, right + 1, bottom + 1))
#     return cropped

# def main():
#     if len(sys.argv) != 3:
#         print('Usage: ./prog InputFile OutputFile')
#         sys.exit(1)

#     input_file = sys.argv[1]
#     output_file = sys.argv[2]

#     try:
#         im = Image.open(input_file)
#     except Exception as e:
#         print(f'Error opening {input_file}: {e}')
#         sys.exit(1)

#     cropped = crop_black_borders(im)
#     cropped.save(output_file)

# if __name__ == '__main__':
#     main()

#!/usr/bin/env python3
import sys
from PIL import Image
import numpy as np

def debug_pixel(color, name):
    """Показывает информацию о пикселе"""
    print(f"{name}: R={color[0]}, G={color[1]}, B={color[2]}")

def is_black_row(row):
    black = np.all(row[:, :3] == 0)
    if not black:
        debug_pixel(row[0], "Первый пиксель строки")
    return black

def crop_black_borders(im):
    print("\nАнализ изображения...")
    arr = np.asarray(im.convert('RGB'))
    h, w, _ = arr.shape
    print(f"Размер: {w}x{h} пикселей")

    # Проверка угловых пикселей
    debug_pixel(arr[0, 0], "Левый верхний угол")
    debug_pixel(arr[-1, -1], "Правый нижний угол")

    # Поиск границ
    top = 0
    while top < h and is_black_row(arr[top]):
        top += 1
    print(f"Верхняя граница: {top}px")

    bottom = h - 1
    while bottom >= top and is_black_row(arr[bottom]):
        bottom -= 1
    print(f"Нижняя граница: {h - bottom - 1}px")

    left = 0
    while left < w and np.all(arr[:, left] == 0):
        left += 1
    print(f"Левая граница: {left}px")

    right = w - 1
    while right >= left and np.all(arr[:, right] == 0):
        right -= 1
    print(f"Правая граница: {w - right - 1}px")

    if top == 0 and bottom == h-1 and left == 0 and right == w-1:
        print("\n⚠️ Чёрные границы не найдены! Проверьте:")
        print("- Залиты ли границы чистым чёрным (0,0,0)")
        print("- Достаточно ли широкая граница (минимум 2px)")
        return im
    
    return im.crop((left, top, right + 1, bottom + 1))

def main():
    if len(sys.argv) != 3:
        print('Использование: python main.py входное_изображение.jpg выходное.jpg')
        sys.exit(1)

    try:
        print(f"\nОткрываю {sys.argv[1]}...")
        im = Image.open(sys.argv[1])
        cropped = crop_black_borders(im)
        
        if cropped == im:
            print("Изменений не требуется - границы не обнаружены")
        else:
            print(f"\nСохранение результата в {sys.argv[2]}")
            print(f"Новый размер: {cropped.size[0]}x{cropped.size[1]}")
            cropped.save(sys.argv[2])
        
    except Exception as e:
        print(f"\n❌ Ошибка: {e}")
        print("Проверьте:")
        print("- Существует ли входной файл")
        print("- Корректно ли имя файла")
        print("- Поддерживается ли формат изображения")

if __name__ == '__main__':
    main()
# import sys
# from PIL import Image
# import numpy as np

# def crop_black_borders(img):
#     pixels = np.array(img.convert('RGB'))
    
#     h, w = pixels.shape[:2]
    
   
#     top = 0
#     while top < h and np.all(pixels[top] <= 10):
#         top += 1
        
#     bottom = h - 1
#     while bottom >= top and np.all(pixels[top] <= 10):
#         bottom -= 1
        
#     left = 0
#     while left < w and np.all(pixels[top] <= 10):
#         left += 1
        
#     right = w - 1
#     while right >= left and np.all(pixels[top] <= 10):
#         right -= 1
    
#     return img.crop((left, top, right + 1, bottom + 1))

# if __name__ == '__main__':
#     import sys
    
#     if len(sys.argv) != 3:
#         print("Usage: python crop.py input.jpg output.jpg")
#         sys.exit(1)
        
#     try:
#         img = Image.open(sys.argv[1])
#         print(f"Original size: {img.size}")
        
#         cropped = crop_black_borders(img)
#         cropped.save(sys.argv[2])
#         print(f"Cropped size: {cropped.size}")
        
#     except Exception as e:
#         print(f"Error: {e}")
#         sys.exit(1)
