from PIL import Image
import sys

def process_image(N1, N2, N, input_file, output_file):
    try:
        img = Image.open(input_file)
        img = img.convert('RGB')
        pixels = img.load()
        width, height = img.size

        for x in range(width):
            for y in range(height):
                r, g, b = pixels[x, y]
                brightness = r + g + b
                if N1 <= brightness <= N2:
                    pixels[x, y] = (N, N, N)

        img.save(output_file)
        print(f"Результат сохранён в {output_file}")
    except Exception as e:
        print(f"Ошибка: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 6:
        print("Использование: python prog.py N1 N2 N InputFile OutputFile")
        sys.exit(1)

    try:
        N1 = int(sys.argv[1])
        N2 = int(sys.argv[2])
        N = int(sys.argv[3])
        input_file = sys.argv[4]
        output_file = sys.argv[5]
        process_image(N1, N2, N, input_file, output_file)
    except ValueError:
        print("Ошибка: N1, N2 и N должны быть целыми числами")
        sys.exit(1)