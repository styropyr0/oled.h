# SSD1306 OLED Display Library

## Description

This project provides an easy-to-use Arduino library for controlling OLED displays with the SSD1306 driver. It supports various features such as custom fonts, animations, progress bars, and more. The library is designed to work with a range of OLED screens, offering flexibility in usage, especially for 128x64 or 128x32 pixel displays. You can display strings, images, progress bars, and even adjust screen brightness, making it ideal for various embedded applications.

---

## Features

- Custom font support (can define custom fonts and languages)
- Animated text with a typewriter effect
- Multiple progress bar styles (including loader variants)
- Brightness control (adjust OLED pixel brightness)
- Image drawing support (for custom bitmaps)
- Screen clear with options to control the display mode (on/off)
- Flexible setup for custom configurations

---

## Enums

### `dimensions`

These enums define the width and height for different OLED screen configurations.

```cpp
enum dimensions
{
    WIDTH_128 = 0x80,  // Width 128 pixels
    WIDTH_64 = 0x40,   // Width 64 pixels
    HEIGHT_64 = 0x40,  // Height 64 pixels
    HEIGHT_32 = 0x20   // Height 32 pixels
};
```

### `registryAddress`

These enums define the various register addresses used for controlling the OLED display.

```cpp
enum registryAddress
{
    OLED_OFF = 0xAE,
    OLED_ON = 0xAF,
    DISP_CLOCK_DIV_RATIO = 0xD5,
    MULTIPLEX = 0xA8,
    CHRG_PUMP = 0x8D,
    DISP_OFFSET = 0xD3,
    MEM_ADDRESS_MODE = 0x20,
    COM_CONFIG = 0xDA,
    CONTRAST = 0x81,
    PRE_CHRG = 0xD9,
    VCOMH_DESEL = 0xDB,
    TURN_ON_ALL_PIXELS = 0xA4,
    SET_DISP_NORMAL = 0xA6,
    SET_COL_ADDR = 0x21,
    SET_PG_ADDR = 0x22
};
```

### `registryCommands`

These enums define specific commands that can be sent to the SSD1306 OLED display to configure various settings.

```cpp
enum registryCommands
{
    CLK_RATIO_RST = 0x80,
    MULTIPLEX_RATIO_RST = 0x3F,
    OFFSET_NO = 0x00,
    HSCROLL_RIGHT = 0x26,
    HSCROLL_LEFT = 0x27,
    VHSCROLL_RIGHT = 0x29,
    VHSCROLL_LEFT = 0x2A,
    STOP_SCROLL = 0x2E,
    START_SCROLL = 0x2F,
    START_LINE = 0x40,
    CHRG_PUMP_75 = 0x14,
    CHRG_PUMP_85 = 0x94,
    CHRG_PUMP_90 = 0x95,
    CHRG_PUMP_OFF = 0x11,
    HORIZONTAL = 0x00,
    VERTICAL = 0x01,
    PAGE = 0x02,
    SEG_REMAP_0 = 0xA0,
    SEG_REMAP_127 = 0xA1,
    COM_OUT_SCAN_NORMAL = 0xC0,
    COM_OUT_SCAN_REMAP = 0xC8,
    COM_ALT = 0x12,
    CONTRAST_RST = 0x7F,
    CONTRAST_MAX = 0xFF,
    PRE_CHRG_RST = 0x22,
    VCOMH_65 = 0x00,
    VCOMH_71 = 0x10,
    VCOMH_77 = 0x20,
    VCOMH_83 = 0x30,
    ZERO = 0x00
};
```

---

## Class: `OLED`

The `OLED` class provides all the functions needed to control the SSD1306 OLED display.

### Constructor

```cpp
OLED(uint8_t width, uint8_t height);
```

- **width**: Width of the display (usually 128).
- **height**: Height of the display (usually 64 or 32).

### Methods

- **`void setFont(const uint8_t (*fontArray)[5])`**  
  Sets a custom font for the characters. `fontArray` is a 2D array representing the custom font.

- **`void clearCustomFont()`**  
  Resets to the default font.

- **`void print(char *string, uint8_t x, uint8_t y)`**  
  Prints a string at the specified coordinates (x, y).

- **`void printAnimated(char *string, uint8_t x, uint8_t y, int delay)`**  
  Prints a string with a typewriter animation effect at the specified coordinates. You can set the delay between characters.

- **`void print_c(char *string, uint8_t x, uint8_t y)`**  
  Clears the screen before printing the string.

- **`void manualSetup(uint8_t *dataSet)`**  
  Allows custom manual setup for the display.

- **`void clearScr()`**  
  Clears the screen.

- **`char *convertString(String string)`**  
  Converts a `String` object to a dynamic `char*` array.

- **`void progressBar(uint8_t progress, uint8_t x, uint8_t y, int style)`**  
  Displays a progress bar at the specified coordinates.  
  **Note**: Styles 1-10 are progress bars, and styles 11-15 are loading animations.

- **`void turnOffOnClr(bool mode)`**  
  Turns the display off when clearing the screen if `mode` is true.

- **`void setBrightness(uint8_t brightness)`**  
  Sets the display brightness as a percentage (0-100).

- **`void draw(const uint8_t *dataSet, uint8_t x, uint8_t y, uint8_t width, uint8_t height)`**  
  Draws a bitmap image at the specified coordinates with the given width and height.

---

## Progress Bar Variants

The `progressBar` method supports different variants, including both standard progress bars and loading animations. You can choose from the following styles:

- **Styles 1-10**: Progress bars that display the completion of a task.
- **Styles 11-15**: Loading animations to show a task is in progress.

Each style has its own unique appearance, and you can customize the `progress` parameter (0-100) to show the completion percentage.

---

## Example Usage

### Basic Example

```cpp
#include <Wire.h>
#include <SSD1306.h>

OLED oled(128, 64);  // Create an OLED object with a 128x64 display

void setup() {
    Wire.begin();
    oled.manualSetup();  // Initialize the display

    oled.print("Hello, World!", 0, 0);  // Print a string at (0, 0)
    oled.setBrightness(80);  // Set brightness to 80%
}

void loop() {
    // Your loop code here
}
```

### Animated Text Example

```cpp
oled.printAnimated("Loading...", 0, 10, 200);  // Print "Loading..." with typewriter effect
```

### Progress Bar Example

```cpp
void loop() {
    for (int i = 0; i <= 100; i++) {
        oled.progressBar(i, 10, 30, 1);  // Show progress bar with style 1
        delay(50);  // Delay to simulate progress
    }
}
```

### Custom Bitmap Example

```cpp
const uint8_t logo[] = {
    // Your bitmap data here (1 byte = 8 pixels)
};

oled.draw(logo, 0, 0, 32, 32);  // Draw the bitmap at position (0, 0) with size 32x32
```

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.