import sys
from PIL import Image

w = 0
h = 0


def image_to_bitmap(image_path, threshold=50):
    image = Image.open(image_path)
    grayscale_image = image.convert("L")
    bw_image = grayscale_image.point(lambda x: 0 if x < threshold else 1, "1")
    width, height = bw_image.size
    bitmap_array = []
    global w, h
    w = (width + 7) & ~7
    h = (height + 7) & ~7
    bitmap_array.append(f"const uint8_t PROGMEM splash[{w//8}*{h}] = " + "{")
    c = 0
    for y in range(h):
        row = []
        row.append("0b")
        for x in range(width):
            c += 1
            if y < height:
                pixel = bw_image.getpixel((x, y))
                row.append(str(pixel))
            else:
                row.append("0")
            if x > 0:
                if c == width and c % 8 != 0:
                    for p in range(((8 - (width % 8)) + width) - c):
                        row.append("0")
                    row.append(",")
                    c = 0
                elif c == width and c % 8 == 0:
                    row.append(",")
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

    print(
        f"Bitmap written to {output_file}.\nBitmap Size: {w}x{h} pixels\nDo you want to print it here?\nPress [Y] to print."
    )
    if len(sys.argv) == 2:
        if sys.argv[1] == "Y".lower():
            print("\n".join(bitmap))
    else:
        if input() == "Y".lower():
            print("\n".join(bitmap))
