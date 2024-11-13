```markdown
# SSD1306 OLED Display Library

This library provides an interface to control SSD1306 OLED displays using an Arduino. It includes various functions to display text, images, and animations on the OLED screen.

## Author
**Saurav Sajeev**

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
  - [Initialization](#initialization)
  - [Setting Fonts](#setting-fonts)
  - [Printing Text](#printing-text)
  - [Clearing the Screen](#clearing-the-screen)
  - [Displaying Progress Bars](#displaying-progress-bars)
  - [Drawing Bitmaps](#drawing-bitmaps)
- [Custom Setup](#custom-setup)
- [Examples](#examples)

## Installation
To use this library, download the repository and include the header file in your Arduino project.

```cpp
#include "SSD1306.h"
```

## Usage

### Initialization
To initialize the OLED display, create an instance of the `OLED` class with the desired width and height.

```cpp
OLED display(WIDTH_128, HEIGHT_64);
```

### Setting Fonts
You can set a custom font set for the characters. The font array should be passed to the `setFont` method.

```cpp
const uint8_t customFont[96][5] = { /* Custom font data */ };
display.setFont(customFont);
```

To clear the custom font and use the default font, call the `clearCustomFont` method.

```cpp
display.clearCustomFont();
```

### Printing Text
To print a string on the display at specified coordinates, use the `print` method.

```cpp
display.print("Hello, World!", 0, 0);
```

For a typewriter animation effect, use the `printAnimated` method.

```cpp
display.printAnimated("Hello, World!", 0, 0, 100);
```

To clear the screen and print a string, use the `print_c` method.

```cpp
display.print_c("Hello, World!", 0, 0);
```

### Clearing the Screen
To clear the OLED display, use the `clearScr` method.

```cpp
display.clearScr();
```

### Displaying Progress Bars
To display a progress bar, use the `progressBar` method. You can choose from different styles.

```cpp
display.progressBar(50, 0, 0, 1); // 50% progress, style 1
```

### Drawing Bitmaps
To draw a bitmap image on the display, use the `draw` method. Provide the bitmap array and the coordinates.

```cpp
const uint8_t smileyBitmap[] = {
    0b00111100, 0b01000010, 0b10100101, 0b10100101,
    0b10000001, 0b10111101, 0b01000010, 0b00111100
};
display.draw(smileyBitmap, 0, 0, 8, 8);
```

## Custom Setup
You can manually set up the display with custom preferences using the `manualSetup` method.

```cpp
uint8_t customSetup[] = { OLED_ON, CONTRAST, 0xFF, OLED_OFF };
display.manualSetup(customSetup);
```

## Examples

### Example 1: Basic Usage
```cpp
#include <Arduino.h>
#include "SSD1306.h"

OLED display(WIDTH_128, HEIGHT_64);

void setup() {
    display.print("Hello, World!", 0, 0);
}

void loop() {
    // Nothing to do here
}
```

### Example 2: Typewriter Animation
```cpp
#include <Arduino.h>
#include "SSD1306.h"

OLED display(WIDTH_128, HEIGHT_64);

void setup() {
    display.printAnimated("Hello, World!", 0, 0, 100);
}

void loop() {
    // Nothing to do here
}
```

### Example 3: Progress Bar
```cpp
#include <Arduino.h>
#include "SSD1306.h"

OLED display(WIDTH_128, HEIGHT_64);

void setup() {
    for (int i = 0; i <= 100; i++) {
        display.progressBar(i, 0, 0, 1);
        delay(100);
    }
}

void loop() {
    // Nothing to do here
}
```

### Example 4: Drawing a Bitmap
```cpp
#include <Arduino.h>
#include "SSD1306.h"

OLED display(WIDTH_128, HEIGHT_64);

const uint8_t smileyBitmap[] = {
    0b00111100, 0b01000010, 0b10100101, 0b10100101,
    0b10000001, 0b10111101, 0b01000010, 0b00111100
};

void setup() {
    display.draw(smileyBitmap, 0, 0, 8, 8);
}

void loop() {
    // Nothing to do here
}
```

## License
This project is licensed under the MIT License.

---

Feel free to customize this `README.md` file further to suit your needs. If you have any questions or need more examples, feel free to ask! 😊
```
