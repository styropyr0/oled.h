# **SSD1306 OLED Display Library**

A lightweight and versatile library to control SSD1306-based OLED displays with Arduino. This library offers a wide range of features including custom fonts, progress bars, animated text, bitmap rendering, and more. It works seamlessly with microcontrollers like **Arduino**, **ESP32**, and **ESP8266** over **I2C** communication.

Additionally, the library includes a **Bitmap Generator** tool in Python, which helps convert images to bitmap arrays for easy display on the OLED screen.

Please note that SSD1306 has 128 independently controllable **Columns** along the width, and 8 independently controllable **Pages** along the height. The total pixel count along the height is divided into **Pages** of 8 pixels high. In scenarios such as printing texts, bitmaps, progress bars, you should keep this in mind.

## **Features**
- **Text Display**: Print static text and animated text (typewriter effect).
- **Custom Fonts**: Supports custom fonts and character sets.
- **Progress Bar**: Display progress bars with various styles.
- **Bitmap Rendering**: Draw bitmap images on the OLED display.
- **Brightness Control**: Adjust display brightness (0-100%).
- **I2C Communication**: Built on I2C communication for simple wiring.
- **Custom Preferences**: Customize OLED display setup with a set of options.
- **Operator Overloading**: Use simple operators to display text and bitmaps.
- **Power Modes**: Control the display power for optimized performance.
- **Super Brightness**: Turn super brightness on or off (may be unstable).
- **Display Inversion**: Invert or restore the display colors.
- **Geometric Shapes**: Draw rectangles, circles, and lines on the display with customizable thickness.
- **Fragments and GridView**: Dynamically manage and render multiple drawable objects on the screen efficiently.
- **Fast and efficient**: This library is built from scratch, from the very basic hardware level programming. Hence, it runs faster than libraries which are built on top of existing libraries.

## **Installation**

### 1. Installing the Library

To use the library, you need to download or clone this repository into your **Arduino libraries** folder.

```bash
git clone https://github.com/styropyr0/oled.h.git
```

Alternatively, you can manually download the ZIP file and add it to the **Arduino IDE** by navigating to **Sketch → Include Library → Add .ZIP Library**.

### 2. Installing Dependencies

The library uses the **Wire** library for I2C communication, which is pre-installed with the Arduino IDE. No additional libraries are required.

## **Hardware Requirements**
- **SSD1306-based OLED display** (typically 128x64 or 128x32 pixels).
- **Arduino Board** (e.g., Arduino UNO, ESP32, or ESP8266).

## **Pin Configuration**
By default, the library uses I2C communication. The I2C pins are:
- **SDA (Data)**: Typically pin `A4` on most Arduino boards (varies by board).
- **SCL (Clock)**: Typically pin `A5` on most Arduino boards (varies by board).

For ESP32 and other microcontrollers, you can configure these pins in the `Wire.begin(SDA_PIN, SCL_PIN);` function.

## **Library Usage**

### 1. **Initializing the OLED Display**

To use the library, instantiate the `OLED` class with the display’s width and height (e.g., 128x64 or 128x32).

```cpp
#include <SSD1306.h>

// Create OLED object with width and height (128x64)
OLED oled(128, 64);

void setup() {
  oled.begin();  // Initialize the OLED display
  oled.clearScr();  // Clear the screen
  oled.print("Hello, World!", 0, 0);  // Print text at (0, 0)
  oled << "This method also prints!" << 0 << 3;   // Print text at (0, 3)
}

void loop() {
  // Main loop logic
}
```

### 2. **Fragments: Manage Dynamic Drawables**

Fragments provide a way to dynamically manage and render multiple drawable objects on the screen efficiently. This feature is especially useful for applications that require frequent updates to specific parts of the display.

Fragments in this library are inspired by Android development fragments. Similar to their Android counterparts, they allow developers to handle multiple independent and reusable components within the OLED display. This can be particularly helpful in scenarios where different portions of the screen require updates independently.

> **Note**: To use fragments, you need to include `Fragments.h`. It is separated from the main library to avoid taking up unnecessary memory when fragments are not used.

#### **Using Fragments**

You can create a `Fragment` to hold multiple `Drawable` objects. Drawables can be added, updated, or removed dynamically.

```cpp
#include <SSD1306.h>
#include <Fragments.h>

// Create OLED and Fragment objects
OLED oled(128, 64);
Fragment fragment;

void setup() {
  oled.begin();

  // Add drawables to the fragment
  fragment.add(new Text("Hello", 0, 0));
  fragment.add(new Circle(64, 32, 10));

  // Draw all the fragment’s drawables
  fragment.draw(&oled);
}
```

#### **Recycling Fragments**

Fragments can be updated dynamically without re-adding all drawables, saving memory and processing time.

```cpp
fragment.recycle();  // Redraw the fragment’s contents on the OLED
```

#### **GridView: Structured Layouts**

The `GridView` class allows you to organize and render multiple drawables in a grid-like layout. This is ideal for creating tables or menu systems.

```cpp
#include <SSD1306.h>
#include <Fragments.h>

// Create OLED, Fragment, and GridView objects
OLED oled(128, 64);
Fragment fragment;
GridView gridView;

void setup() {
  oled.begin();

  // Add a grid of circles to the fragment
  gridView.init(new Circle(0, 0, 4), 4, 4, 16, 16);  // 4x4 grid with 16px spacing
  fragment.add(&gridView);

  // Draw the fragment containing the grid
  fragment.draw(&oled);
}
```

### 3. **Custom Fonts**

You can use custom fonts by defining an array of font data. This library uses 5x7 bitmaps for characters by default, but you can change the font with the `setFont()` method.

#### Example: Setting a Custom Font

```cpp
// Define a simple custom font (5x7 pixels)
const uint8_t myFont[5][5] = {
  {0x1F, 0x1F, 0x00, 0x00, 0x00},  // Example character data
  // More characters...
};

OLED oled(128, 64);

void setup() {
  oled.begin();
  oled.setFont(myFont);  // Set the custom font
  oled.print("Custom Font", 0, 0);  // Display with custom font
}
```

### 4. **Printing Static Text**

You can print static text at a given `(x, y)` coordinate using the `print()` method.

#### Example: Printing Text

```cpp
oled.print("Hello, OLED!", 0, 0);  // Prints "Hello, OLED!" at (0, 0)
```

### 5. **Animated Text (Typewriter Effect)**

Use the `printAnimated()` method for a typewriter effect, where text is displayed one character at a time.

#### Example: Animated Text

```cpp
oled.printAnimated("Welcome!", 0, 0, 100, false);  // Print text with a 100 ms delay between characters, set true for highlight effect
```

### 6. **Progress Bars**

You can display progress bars in multiple styles (1-10 for progress bars, 11-15 for loaders). The `progressBar()` method accepts the progress value (0-100) and a style number.

#### Example: Progress Bar

```cpp
oled.progressBar(50, 0, 10, 1);  // Displays a 50% progress bar at (0, 10), style 1
```

### 7. **Bitmap Rendering**

The library includes the `draw()` method to display bitmaps on the OLED. You can convert images into bitmap arrays using the **Bitmap Generator** Python tool (explained below).

#### Example: Displaying a Bitmap

```cpp
const uint8_t myBitmap[] = {
  // Your bitmap data here, generated by the Bitmap Generator
};

oled.draw(myBitmap, 0, 0, 16, 16);  // Draw a 16x16 bitmap at coordinates (0, 0)
```

### 8. **Chaining Operators for Display**

The library also includes operator overloading to simplify the process of displaying text and bitmaps. You can use the `<<` operator to print text and the `[]` operator to display bitmaps.

#### Example: Printing Text Using Chaining Operators

```cpp
oled << "Hello, World!" << 0 << 0;  // Prints "Hello, World!" at (0, 0)
```

#### Example: Displaying a Bitmap Using Chaining Operators

```cpp
oled[myBitmap] << 0 << 0 << 16 << 16;  // Draws a 16x16 bitmap at (0, 0)
```

### 9. **Clearing the Screen**

Use the `clearScr()` method to clear the screen.

```cpp
oled.clearScr();  // Clears the display
```

### 10. **Adjusting Brightness**

Use the `setBrightness()` method to adjust the display’s brightness. It accepts a percentage value (0-100).

```cpp
oled.setBrightness(80);  // Set the brightness to 80%
```

### 11. **Custom OLED Setup**

The `manualSetup()` method allows you to pass an array of settings to configure the OLED display manually.

```cpp
uint8_t customSettings[] = {
  0xA8, 0x3F,  // Multiplex ratio
  0xD3, 0x00,  // Display offset
  // More settings...
};

oled.manualSetup(customSettings);  // Apply custom settings
```

### 12. **Turn Display Off on Clear**

You can disable the display when you clear the screen using the `turnOffOnClr()` method.

```cpp
oled.turnOffOnClr(true);  // Turn off display when cleared
```

### 13. **Power Modes**

The display can operate in different power modes. Choose between low power, balanced, or performance mode to optimize energy consumption or display quality.

#### Example: Setting Power Mode

```cpp
oled.setPowerMode(LOW_POWER_MODE);  // Set the display to low power mode
```

### 14. **Super Brightness**

Enable or disable super brightness for high-intensity display, though note it may cause instability.

#### Example: Super Brightness

```cpp
oled.superBrightness(true);  // Turn on super brightness
```

### 15. **Inverting the Display**

Invert the pixels on the display to change all white pixels to black and vice versa.

#### Example: Inverting Display

```cpp
oled.invertDisplay();  // Invert the display colors
```

### 16. **Entire Display ON/OFF**

You can turn the entire display on or off.

#### Example: Entire Display ON/OFF

```cpp
oled.entireDisplayON();  // Turn all pixels on
oled.entireDisplayOFF();  // Revert back to the content
```

### 17. **Drawing Geometric Shapes**

You can draw shapes such as rectangles, circles, and lines on the OLED display.

#### Example: Drawing a Rectangle

```cpp
oled.rectangle(10, 10, 50, 30, 5, 2);  // Draw a rectangle at (10, 10) with width 50, height 30, 5px corner radius, and 2px thickness
```

#### Example: Drawing a Circle

```cpp
oled.circle(64, 32, 20, 2);  // Draw a circle at (64, 32) with radius 20, and thickness 2px
```

#### Example: Drawing a Line

```cpp
oled.line(0, 0, 127, 63, 2);  // Draw a line from (0, 0) to (127, 63), 2px thick
```

### 18. **Highlighted Text**

Use the `printHighlighted()` method to print the text as highlighted.

#### Example: Highlighted Text

```cpp
oled.printHighlighted("Welcome!", 0, 0);  // Print text with a highlighted effect
```

### 19. **Clear Area**

Use the `clearArea()` method to clear a specific region along the width of the display.

#### Example: Highlighted Text

```cpp
oled.clearArea(20, 40, 0);  // Clears the region from 20 to 40 in the page 0.
```

---

## **Constants**

Here are the constants you can use to configure various settings for your SSD1306 OLED display.

### 1. **Display Settings Constants**

| **Constant**        | **Value** | **Description**                                       |
|---------------------|-----------|-------------------------------------------------------|
| `OLED_OFF`          | 0xAE      | Turns the display off.                                |
| `OLED_ON`           | 0xAF      | Turns the display on.                                 |
| `INVERT`            | 0xA7      | Inverts the display pixels.                           |
| `REVERT`            | 0xA6      | Reverts the display pixels.                           |
| `ENTIRE_DISP_ON`    | 0xA5      | Turns on all the pixels.                              |
| `RESUME_FROM_VRAM`  | 0xA4      | Resumes from VRAM.                                    |

### 2. **Display Power Mode Constants**

| **Constant**        | **Value** | **Description**                                       |
|---------------------|-----------|-------------------------------------------------------|
| `LOW_POWER_MODE`    | 0x00      | Low power mode.                                       |
| `BALANCED_MODE`     | 0x01      | Balanced mode.                                        |
| `PERFORMANCE_MODE`  | 0x02      | Performance mode.                                     |

### 3. **Geometry Constants**

| **Constant**        | **Value** | **Description**                                       |
|---------------------|-----------|-------------------------------------------------------|
| `WIDTH_128`         | 0x80      | Display width of 128 pixels.                          |
| `HEIGHT_64`         | 0x40      | Display height of 64 pixels.                          |

### 4. **Bitmap Mode Constants**

| **Constant**        | **Value** | **Description**                                       |
|---------------------|-----------|-------------------------------------------------------|
| `HORIZONTAL`        | 0x00      | Horizontal memory addressing mode.                    |
| `VERTICAL`          | 0x01      | Vertical memory addressing mode.                      |
| `PAGE`              | 0x02      | Page addressing mode.                                 |

### 5. **Special Commands Constants**

| **Constant**        | **Value** | **Description**                                       |
|---------------------|-----------|-------------------------------------------------------|
| `CHRG_PUMP`         | 0x8D      | Charge pump control command.                          |
| `CONTRAST`          | 0x81      | Set the display contrast.                             |
| `PRE_CHRG`          | 0xD9      | Pre-charge period control.                            |
| `VCOMH_DESEL`       | 0xDB      | VCOMH deselect level.                                 |

---

## **Bitmap Generator Tool**

### Overview

The **Bitmap Generator** tool helps you convert images to bitmaps that can be displayed on your SSD1306 OLED screen. This tool is written in **Python** and uses the **Pillow** library to process images.

### Running the Bitmap Generator

#### Command-Line Usage

You can run the **Bitmap Generator** directly from the command line:

```bash
python image_to_bitmap.py <image_path> <output_file>
```

For example, to convert an image located at `images/logo.png` to a bitmap:

```bash
python image_to_bitmap.py images/logo.png output_logo.h
```

---

## **License**

This library is licensed under the **MIT License**.
