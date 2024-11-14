# SSD1306 Display Library for Arduino

This repository contains a custom library for controlling an **SSD1306 OLED display** with an Arduino. It supports bitmap images, text, and various other display functionalities. Additionally, a **bitmap generator** is included to convert images into displayable bitmap format, which can be used in the Arduino code for rendering images on the screen.

## Features

- Control SSD1306 OLED displays via I2C.
- Support for text and bitmap rendering.
- Bitmap image generator for converting images into displayable formats.
- Easy-to-use functions for drawing pixels, lines, and text.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
  - [Basic Setup](#basic-setup)
  - [Text Rendering](#text-rendering)
  - [Bitmap Rendering](#bitmap-rendering)
  - [Bitmap Generator](#bitmap-generator)
- [Constants](#constants)
- [Methods](#methods)
  - [Constructor](#constructor)
  - [Methods for Displaying Content](#methods-for-displaying-content)
- [License](#license)

## Installation

1. Clone or download this repository to your local machine.
2. Open Arduino IDE.
3. Go to **Sketch > Include Library > Add .ZIP Library...**.
4. Select the ZIP file you downloaded and click **Open**.

Now you can include the library in your Arduino projects.

```cpp
#include <SSD1306.h>
Usage
Basic Setup
To get started, initialize the SSD1306 display in your Arduino code.

cpp
Copy code
#include <SSD1306.h>

// Define the display object
SSD1306 display(SSD1306_I2C_ADDRESS, SDA_PIN, SCL_PIN); // Modify pins as per your setup

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
  display.clearDisplay();
  display.display();
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Hello, SSD1306!");
  display.display();
  delay(1000);
}
Text Rendering
To render text, you can use the setTextSize(), setTextColor(), and setCursor() methods.

cpp
Copy code
display.setTextSize(2);          // Set text size (1, 2, 3, ...)
display.setTextColor(SSD1306_WHITE);  // Set text color (WHITE or BLACK)
display.setCursor(10, 10);      // Set cursor position
display.print("Hello World!");
display.display();               // Display the content on the screen
Bitmap Rendering
You can render bitmap images using the drawBitmap() method. The image should be generated using the Bitmap Generator tool described below.

cpp
Copy code
#include "bitmap.h"  // Include the header where the bitmap is stored

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
  display.clearDisplay();
  display.drawBitmap(0, 0, splash, 128, 64, SSD1306_WHITE); // Render the bitmap
  display.display();
}
Bitmap Generator
The Bitmap Generator is a Python script that converts an image to a format that can be used by the Arduino code. The Python script takes an image, converts it to black and white, and then generates a C array representation of the image that can be used directly in your Arduino code.

How to use the Bitmap Generator (Python)
Install dependencies:

Make sure Python is installed on your system.
Install the Pillow library for image processing:
bash
Copy code
pip install pillow
Run the Bitmap Generator: You can use the bitmap generator via the command line or by running the Python script directly.

Command Line Usage:

bash
Copy code
python bitmap_generator.py <image_path> <output_file>
Example:

bash
Copy code
python bitmap_generator.py image.png splash.h
This will generate a file splash.h containing the bitmap data.

Python Interpreter: Alternatively, you can run the script within a Python interpreter:

python
Copy code
>>> from bitmap_generator import image_to_bitmap
>>> bitmap = image_to_bitmap('image.png', threshold=50)
>>> with open('splash.h', 'w') as f:
>>>     f.write("\n".join(bitmap))
This will save the bitmap data to splash.h, which you can include in your Arduino project.

Example Output:
The generated output will be a C array that can be directly used in your Arduino sketch:

cpp
Copy code
const uint8_t PROGMEM splash[] = {
  0b11111111, 0b11111111, 0b11111111, 0b11111111, ...
};
Bitmap Generator Code:
python
Copy code
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
Constants
SSD1306_I2C_ADDRESS: The I2C address of the SSD1306 display (commonly 0x3C or 0x3D).
SSD1306_WHITE: The color constant for white pixels.
SSD1306_BLACK: The color constant for black pixels.
Methods
Constructor
cpp
Copy code
SSD1306(uint8_t i2c_address, uint8_t sda_pin, uint8_t scl_pin);
i2c_address: The I2C address of the SSD1306 display.
sda_pin: The SDA pin used for I2C communication.
scl_pin: The SCL pin used for I2C communication.
begin()
cpp
Copy code
void begin(uint8_t vcc, uint8_t address);
vcc: Power supply setting (SSD1306_SWITCHCAPVCC or SSD1306_EXTERNALVCC).
address: The I2C address of the display.
clearDisplay()
cpp
Copy code
void clearDisplay();
Clears the display buffer.

display()
cpp
Copy code
void display();
Pushes the buffer content to the display.

setCursor()
cpp
Copy code
void setCursor(uint8_t x, uint8_t y);
x: The horizontal position (0–127).
y: The vertical position (0–63).
setTextSize()
cpp
Copy code
void setTextSize(uint8_t size);
Sets the text size (1 is the smallest, 2 is double the size, etc.).

setTextColor()
cpp
Copy code
void setTextColor(uint8_t color);
color: SSD1306_WHITE or SSD1306_BLACK.
drawBitmap()
cpp
Copy code
void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);
x: The x-coordinate.
y: The y-coordinate.
bitmap: The pointer to the bitmap array.
w: The width of the bitmap.
h: The height of the bitmap.
color: SSD1306_WHITE or SSD1306_BLACK.
License
This project is licensed under the MIT License - see the LICENSE file for details.