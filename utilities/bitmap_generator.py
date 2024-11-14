import sys
from PIL import Image


def image_to_bitmap(image_path, threshold=50):
    image = Image.open(image_path)
    grayscale_image = image.convert("L")
    bw_image = grayscale_image.point(lambda x: 0 if x < threshold else 1, "1")
    width, height = bw_image.size
    bitmap_array = []
    bitmap_array.append("const uint8_t PROGMEM splash[] = {")
    c = 0
    for y in range(height):
        row = []
        row.append("0b")
        for x in range(width):
            c += 1
            pixel = bw_image.getpixel((x, y))
            row.append(str(pixel))
            if x > 0:
                if c == width and c % 8 != 0:
                    for p in range(((8 - (width % 8)) + width) - c):
                        row.append("0")
                    row.append(",")
                    c = 0
                elif c == width and c % 8 == 0:
                    c = 0
                elif c % 8 == 0:
                    row.append(", 0b")
        bitmap_array.append("".join(row))
    bitmap_array.append("};")
    return bitmap_array


if __name__ == "__main__":
    print("SSD1306 BITMAP GENERATOR\nDeveloped by: Saurav Sajeev\n")
    if len(sys.argv) == 3:
        image_path = sys.argv[1]
        output_file = sys.argv[2]
    else:
        image_path = input("Enter the path to the image: ")
        output_file = input("Enter the output file name: ")

    bitmap = image_to_bitmap(image_path)
    with open(output_file, "w") as file:
        file.write("\n".join(bitmap))

    print(f"Bitmap written to {output_file}")
