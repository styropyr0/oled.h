# SSD1306 OLED Display Library

A lightweight and versatile library to control SSD1306-based OLED displays with Arduino. This library offers a wide range of features including custom fonts, progress bars, animated text, bitmap rendering, geometric shapes, and much more. It works seamlessly with microcontrollers like **Arduino**, **ESP32**, and **ESP8266** over **I2C** communication.

Additionally, the library includes a **Bitmap Generator** tool in Python, which helps convert images to bitmap arrays for easy display on the OLED screen.

Please note that SSD1306 has 128 independently controllable **Columns** along the width, and 8 independently controllable **Pages** along the height. The total pixel count along the height is divided into **Pages** of 8 pixels high. In scenarios such as printing texts, bitmaps, or progress bars, you should keep this in mind.

## Features

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
- **Display Inversion**: Invert or restore the display colors, or invert the pixel state explicitly.
- **Geometric Shapes**: Draw rectangles, circles, and lines on the display with customizable thickness.
- **Fragments and GridView**: Dynamically manage and render multiple drawable objects on the screen efficiently.
- **Data Visualization Plots**: Ready-to-use pulse, bit bar, scatter, and histogram plots for real-time analytics and sensor data.

## Installation

### 1. Installing the Library

To use the library, you need to download or clone this repository into your **Arduino libraries** folder.

```bash
git clone https://github.com/styropyr0/oled.h.git
```

Alternatively, you can manually download the ZIP file and add it to the **Arduino IDE** by navigating to **Sketch → Include Library → Add .ZIP Library**.

### 2. Installing Dependencies

The library uses the **Wire** library for I2C communication, which is pre-installed with the Arduino IDE. No additional libraries are required.

## Hardware Requirements

- **SSD1306-based OLED display** (typically 128x64 or 128x32 pixels).
- **Arduino Board** (e.g., Arduino UNO, ESP32, or ESP8266).

## Pin Configuration

By default, the library uses I2C communication. The I2C pins are:
- **SDA (Data)**: Typically pin `A4` on most Arduino boards (varies by board).
- **SCL (Clock)**: Typically pin `A5` on most Arduino boards (varies by board).

For ESP32 and other microcontrollers, you can configure these pins in the `Wire.begin(SDA_PIN, SCL_PIN);` function.

## Library Usage

### 1. Initializing the OLED Display

To use the library, instantiate the OLED class with the display’s width and height (e.g., 128x64 or 128x32).

```cpp
#include 

// Create OLED object with width and height (128x64)
OLED oled(128, 64);

void setup() {
  oled.begin();  // Initialize the OLED display
  oled.clearScr();  // Clear the screen
  oled.print("Hello, World!", 0, 0);  // Print text at (0, 0)
  oled  **Note**: To use fragments, you need to include Fragments.h. It is separated from the main library to avoid taking up unnecessary memory when fragments are not used.

#### Using Fragments

You can create a Fragment to hold multiple Drawable objects. Drawables can be added, updated, or removed dynamically.

```cpp
#include 
#include 

// Create OLED and Fragment objects
OLED oled(128, 64);
FragmentManager manager(oled); // Create a manager for the Fragments. The manager is attached to the corresponding oled object.

void setup() {
  oled.begin();
  Fragment fragment(manager);
  // Add drawables to the fragment
  fragment.add(new Text("Hello", 0, 0));
  fragment.add(new Circle(64, 32, 10, 2));

  // Draw all the fragment’s drawables
  fragment.inflate();
}
```

#### Recycling Fragments

Fragments can be updated dynamically without re-adding all drawables, saving memory and processing time. There are three ways to recycle fragments:

1. **Recycle Modified Drawables**: Applies changes to modified drawables without re-inflating them.
   ```cpp
   fragment.recycle();  // Redraw the fragment’s contents on the OLED
   ```

2. **Recycle All Drawables**: Applies changes to all drawables by re-inflating them.
   ```cpp
   fragment.recycleAll();  // Re-inflate all drawables in the fragment
   ```

3. **Recycle New Drawables**: Applies changes to newly added drawables without re-inflating the existing ones.
   ```cpp
   fragment.recycleNew();  // Apply changes to newly added drawables
   ```

#### GridView: Structured Layouts

The `GridView` class allows you to organize and render multiple drawables in a grid-like layout. This is ideal for creating tables or menu systems.

```cpp
#include 
#include 

// Create OLED, Fragment, and GridView objects
OLED oled(128, 64);
FragmentManager manager(oled);

void setup() {
  oled.begin();

  // Add a grid of circles to the fragment
  Fragment fragment(manager); // Attach the manager to the required Fragment.
  Circle* circle = new Circle(0, 0, 8, 2);
  GridView* grid = new GridView(circle, 12, 4, 10, 10, 10, 10);
  fragment.add(grid);
  fragment.inflate(); // Draw the fragment containing the grid
}
```

#### Visibility Modifiers

You can now control the visibility of individual drawables within a fragment. This allows for more dynamic and flexible display management.

```cpp
// Set visibility of a drawable
drawable->setVisibility(false); // Hide the drawable
drawable->setVisibility(true);  // Show the drawable
```

#### Change State Management

Drawables now support change state management, allowing you to track and update only modified drawables.

#### Reassignment or Change of Drawables After Inflating

After inflating a fragment, you can reassign or change the drawables dynamically. This allows for efficient updates without the need to re-inflate the entire fragment.

```cpp
Text* textDrawable = new Text("New Text", 0, 0);
fragment.add(textDrawable);
fragment.inflate();

//Change the text content after some time
*textDrawable = Text("Updated Text", 0, 0);
fragment.recycleAll();  // Apply changes to the newly added drawable
```

#### New Drawable Types

The library now includes additional drawable types such as `Rectangle`, `Line`, `HighlightedText`, `AnimatedText`, and `Bitmap`.

```cpp
// Example of adding new drawable types
fragment.add(new Rectangle(10, 10, 50, 30, 5, 2));
fragment.add(new Line(0, 0, 127, 63, 2));
fragment.add(new HighlightedText("Highlighted", 0, 10));
fragment.add(new AnimatedText("Animated", 0, 20, 100, true));
fragment.add(new Bitmap(bitmapData, 0, 0, 16, 16));
```

#### Fragment Back Stack Management

Inspired by Android fragments, you can manage a back stack of fragments using `addToBackStack()` and `popBackStack()` methods.

##### Example: Adding a Fragment to Back Stack

```cpp
Fragment fragment(manager);
manager.addToBackStack(&fragment);  // Add fragment to back stack
```

##### Example: Popping a Fragment from Back Stack

```cpp
manager.popBackStack();  // Pop the last fragment from the back stack
```

##### Example Code

Here's an example code demonstrating the usage of the new features:

```cpp
#include 
#include 

// Create OLED object with width and height (128x64)
OLED oled(128, 64);

// Create a FragmentManager object and attach it to the OLED object
FragmentManager mgr(oled);

void setup() {
  // Initialize the OLED display
  oled.begin();
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Create a Fragment object and attach it to the FragmentManager
  Fragment fragment(mgr);
  
  // Create drawable objects
  Rectangle* rectangle = new Rectangle(30, 0, 15, 15, 3, 1);
  Text* text = new Text("Hello World!", 0, 0);
  
  // Add drawables to the fragment
  fragment.add(rectangle);
  fragment.add(text);
  
  // Draw all the fragment’s drawables
  fragment.inflate();

  // Wait for 2 seconds
  delay(2000);

  // Reassign the text drawable with new content and position
  *text = Text("This is new text!", 10, 3);
  
  // Hide the rectangle drawable
  rectangle->setVisibility(false);
  
  // Recycle all drawables to apply changes
  fragment.recycle();
}

void loop() {
  // Main loop logic (empty in this example)
}
```

### 3. Custom Fonts

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
  oled.inflate();  // Render items on the display
}
```

#### Revert to Default Font

To go back to the default font:

```cpp
oled.clearCustomFont();
```

### 4. Printing Static Text

You can print static text at a given `(x, y)` coordinate using the `print()` method.

#### Example: Printing Text

```cpp
oled.print("Hello, OLED!", 0, 0);  // Prints "Hello, OLED!" at (0, 0)
```

### 5. Animated Text (Typewriter Effect)

Use the `printAnimated()` method for a typewriter effect, where text is displayed one character at a time.

#### Example: Animated Text

```cpp
oled.printAnimated("Welcome!", 0, 0, 100, false);  // Print text with a 100 ms delay between characters, set true for highlight effect
```

### 6. Progress Bars

You can display progress bars in multiple styles (1-10 for progress bars, 11-15 for loaders). The `progressBar()` method accepts the progress value (0-100) and a style number.

#### Example: Progress Bar

```cpp
oled.progressBar(50, 0, 10, 1);  // Displays a 50% progress bar at (0, 10), style 1
```

### 7. Bitmap Rendering

The library includes the `draw()` method to display bitmaps on the OLED. You can convert images into bitmap arrays using the **Bitmap Generator** Python tool (explained below).

#### Example: Displaying a Bitmap

```cpp
const uint8_t myBitmap[] = {
  // Your bitmap data here, generated by the Bitmap Generator
};

oled.draw(myBitmap, 0, 0, 16, 16);  // Draw a 16x16 bitmap at coordinates (0, 0)
```

### 8. Chaining Operators for Display

The library also includes operator overloading to simplify the process of displaying text and bitmaps. You can use the ` 
```

For example, to convert an image located at `images/logo.png` to a bitmap:

```bash
python bitmap_generator.py images/logo.png output_logo.h
```
One of the best ways to do this is by adding the path to this script as an alias in your Environment Variables. Otherwise, you need to type the entire path of the script every time.

## **License**

This library is licensed under the **MIT License**.