# OLED Display Library for Arduino

## Overview

This library provides a set of functions to control an SSD1306 OLED display using I2C without relying on dedicated libraries. It includes basic display initialization, text printing, screen clearing, custom setup, progress bar display, and scrolling functionality.

## Features

- Initialize the OLED display with custom dimensions.
- Print text at specified coordinates.
- Clear the screen.
- Custom setup with user-defined preferences.
- Display progress bars and loaders.
- Control display brightness.
- Scroll text in various directions.

## Getting Started

### Prerequisites

- Arduino IDE
- An Arduino board (e.g., Arduino Uno)
- SSD1306 OLED display
- I2C connection between the Arduino and the OLED display

### Installation

1. Clone this repository or download the ZIP file and extract it.
2. Copy the `oled.h` file to your Arduino libraries folder.

### Wiring

Connect the OLED display to the Arduino as follows:

- **VCC** to 5V (or 3.3V if your display requires it)
- **GND** to GND
- **SCL** to A5 (for Arduino Uno)
- **SDA** to A4 (for Arduino Uno)

### Usage

Include the `oled.h` file in your Arduino sketch and create an instance of the `OLED` class with the desired dimensions.

```cpp
#include "oled.h"

OLED display(WIDTH_128, HEIGHT_64);

void setup() {
  Wire.begin();
  display.autoSetup();
}

void loop() {
  display.clearScr();
  display.print("Hello, World!", 0, 0);
  delay(2000);
  display.scroll(VHSCROLL_RIGHT);
}
```

## API Reference

### Constructor

```cpp
OLED(uint8_t width, uint8_t height);
```

- `width`: Width of the OLED display (e.g., `WIDTH_128`).
- `height`: Height of the OLED display (e.g., `HEIGHT_64`).

### Methods

#### `void print(char *string, uint8_t x, uint8_t y);`

Prints a string at the specified coordinates.

- `string`: The string to be printed.
- `x`: The X coordinate.
- `y`: The Y coordinate.

#### `void print_c(char *string, uint8_t x, uint8_t y);`

Clears the screen and prints a string at the specified coordinates.

- `string`: The string to be printed.
- `x`: The X coordinate.
- `y`: The Y coordinate.

#### `void manualSetup(uint8_t *dataSet);`

Sets up the display with custom preferences.

- `dataSet`: Array of custom preferences.

#### `void clearScr();`

Clears the OLED display.

#### `char *convertString(String string);`

Converts a string to a dynamic `char*` array.

- `string`: Input string.
- Returns: Dynamic `char*` array of the input string.

#### `void progressBar(uint8_t progress, uint8_t x, uint8_t y, int style);`

Displays a progress bar.

- `progress`: Progress to be set.
- `x`: The X coordinate.
- `y`: The Y coordinate.
- `style`: Progress bar variant (1-15).

#### `void turnOffOnClr(bool mode);`

Sets the display mode to off when the screen is cleared.

- `mode`: Set `true` to turn off the display.

#### `void scroll(uint8_t direction);`

Sets the scroll mode.

- `direction`: Scroll direction (use enum values).

#### `void setBrightness(uint8_t brightness);`

Sets the brightness of the pixels.

- `brightness`: Percentage of brightness.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author

- **Saurav Sajeev**

