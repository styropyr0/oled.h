# SSD1306 Display Library for Arduino

This repository contains a custom library for controlling an **SSD1306 OLED display** with an Arduino. It supports text rendering, bitmap images, and various other display functionalities. Additionally, a **bitmap generator** is included to convert images into displayable bitmap format, which can be used in your Arduino code for rendering images on the screen.

## Features

- Control SSD1306 OLED displays via I2C.
- Support for text and bitmap rendering.
- Bitmap image generator to convert images into displayable formats.
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
```

## Usage

### Basic Setup

To get started, initialize the SSD1306 display in your Arduino code.

```cpp
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
```

### Text Rendering

To render text, you can use the `setTextSize()`, `setTextColor()`, and `setCursor()` methods.

```cpp
display.setTextSize(2);          // Set text size (1, 2, 3, ...)
display.setTextColor(SSD1306_WHITE);  // Set text color (WHITE or BLACK)
display.setCursor(10, 10);      // Set cursor position
display.print("Hello World!");
display.display();               // Display the content on the screen
```

### Bitmap Rendering

You can render bitmap images using the `drawBitmap()` method. The image should be generated using the Bitmap Generator tool described below.

```cpp
#include "bitmap.h"  // Include the header where the bitmap is stored

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
  display.clearDisplay();
  display.drawBitmap(0, 0, splash, 128, 64, SSD1306_WHITE); // Render the bitmap
  display.display();
}
```

### Bitmap Generator

The **Bitmap Generator** is a Python script that converts an image to a format that can be used by the Arduino code. The Python script takes an image, converts it to black and white, and then generates a C array representation of the image that can be used directly in your Arduino code.

#### How to Use the Bitmap Generator

You can use the **Bitmap Generator** either via the command line or by running the Python script directly within a Python interpreter.

##### Command Line Usage

1. **Install Python Dependencies**:
   - Ensure that Python is installed on your system.
   - Install the `Pillow` library for image processing:
     ```bash
     pip install pillow
     ```

2. **Run the Bitmap Generator**:
   You can run the bitmap generator via the command line as follows:

   ```bash
   python bitmap_generator.py <image_path> <output_file>
   ```

   Example:
   ```bash
   python bitmap_generator.py image.png splash.h
   ```

   Example:
   ```bash
   python bitmap_generator.py image.png splash.txt
   ```

   This command will generate a file `splash.h` or `splash.txt` containing the bitmap data, which you can then include in your Arduino project.

##### Python Interpreter Usage

Alternatively, you can run the Bitmap Generator file manually using a python interpreter like VS-Code. It works same as the command line usage. Enter the image file path and data file name, and the data will be generated and saved to the file.

This will generate a `splash.h` or any kind of file you provide containing the bitmap data for use in your Arduino sketch.

#### Recommended usage

It is better to provide the data file as a `.h` file as you can create multiple of them for different images and include it on your project.

#### Example Output

The generated output will be a C array that can be directly used in your Arduino code. The array will look something like this:

```cpp
const uint8_t PROGMEM splash[] = {
  0b11111111, 0b11111111, 0b11111111, 0b11111111, ...
};
```

### Important Notes:
- The Bitmap Generator converts the image to a **black and white** format.
- The **threshold** parameter (default 50) can be adjusted to control the conversion of grayscale pixels to either black or white. A lower threshold will make more of the image black, while a higher threshold will make it more white.

## Constants

- **SSD1306_I2C_ADDRESS**: The I2C address of the SSD1306 display (commonly `0x3C` or `0x3D`).
- **SSD1306_WHITE**: The color constant for white pixels.
- **SSD1306_BLACK**: The color constant for black pixels.

## Methods

### Constructor

```cpp
SSD1306(uint8_t i2c_address, uint8_t sda_pin, uint8_t scl_pin);
```
- **i2c_address**: The I2C address of the SSD1306 display.
- **sda_pin**: The SDA pin used for I2C communication.
- **scl_pin**: The SCL pin used for I2C communication.

### `begin()`

```cpp
void begin(uint8_t vcc, uint8_t address);
```
- **vcc**: Power supply setting (`SSD1306_SWITCHCAPVCC` or `SSD1306_EXTERNALVCC`).
- **address**: The I2C address of the display.

### `clearDisplay()`

```cpp
void clearDisplay();
```
Clears the display buffer.

### `display()`

```cpp
void display();
```
Pushes the buffer content to the display.

### `setCursor()`

```cpp
void setCursor(uint8_t x, uint8_t y);
```
- **x**: The horizontal position (0–127).
- **y**: The vertical position (0–63).

### `setTextSize()`

```cpp
void setTextSize(uint8_t size);
```
Sets the text size (1 is the smallest, 2 is double the size, etc.).

### `setTextColor()`

```cpp
void setTextColor(uint8_t color);
```
- **color**: `SSD1306_WHITE` or `SSD1306_BLACK`.

### `drawBitmap()`

```cpp
void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);
```
- **x**: The x-coordinate.
- **y**: The y-coordinate.
- **bitmap**: The pointer to the bitmap array.
- **w**: The width of the bitmap.
- **h**: The height of the bitmap.
- **color**: `SSD1306_WHITE` or `SSD1306_BLACK`.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```