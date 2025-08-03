# SSD1306 OLED Display Library

A lightweight and versatile library to control SSD1306-based OLED displays with Arduino. This library offers a wide range of features, including custom fonts, progress bars, animated text, bitmap rendering, geometric shapes, advanced scene management with Fragments, and much more. It works seamlessly with microcontrollers like **Arduino**, **ESP32**, and **ESP8266** over **I2C** communication.

Additionally, the library includes a **Bitmap Generator** tool in Python, which helps convert images to bitmap arrays for easy display on the OLED screen.

**Hardware Note**: SSD1306 has 128 individually controllable **columns** (width). Vertically, the height is split into **pages** of 8 pixels each. Plan graphics accordingly.

## Features

- **Text Display**: Print static and animated text (typewriter effect).
- **Custom Fonts**: Supports custom fonts, Unicode, other language glyphs.
- **Progress Bars**: Multiple styles and animated loaders.
- **Bitmap Rendering**: Draw images, icons, and bitmaps from arrays.
- **Brightness Control**: Software PWM, 0–100%.
- **I2C Communication** with address selection.
- **Custom Preferences**: Override display configuration easily.
- **Operator Overloading**: Easy stream-style text/bitmap/coordinate input.
- **Power Modes**: Optimize speed/power with 4 distinct I2C speeds.
- **Super Brightness** (overdrive mode).
- **Display Inversion**: Both display and pixel state inversion.
- **Geometric Shapes**: Draw rectangles, rounded rectangles, circles, lines.
- **Advanced Drawing/Scene Management**:  
  - **Fragments:** Batch and manage collections of drawables for fast, complex UI.
  - **GridView**: Organize drawables in grids or menus.
  - **Drawable Objects**: All primitives (Text, Rectangle, Circle, Line, etc.) can be used both directly and as reusable objects within Fragments.
- **Data Visualization Plots**: Plot raw or processed sensor/analytics data: pulse, bar, scatter, histogram.

## Installation

### 1. Installing the Library

Clone into your Arduino libraries folder:

```bash
git clone https://github.com/styropyr0/oled.h.git
```
Or download the ZIP and use the Arduino IDE’s “Add .ZIP Library”.

### 2. Dependencies

The library uses the built-in **Wire** library for I2C.

## Hardware Requirements

- **SSD1306-based OLED display** (commonly 128x64 or 128x32 px).
- **Arduino** (Uno, ESP32, ESP8266, etc.).

## Pin Configuration

I2C pins:
- **SDA (Data)**: Arduino—A4 (varies by board)
- **SCL (Clock)**: Arduino—A5 (varies)
- ESP32/ESP8266—set with `Wire.begin(SDA, SCL);`

Default I2C address: `ADDR` (0x3C). If your display differs, use the address constructor (see below).

## Basic Library Usage

### 1. Initializing the OLED

```cpp
#include <SSD1306.h>

OLED oled(128, 64);         // Default: 128x64 at address 0x3C

// For displays with a different I2C address:
OLED oled(128, 64, 0x3D);   // Example for address 0x3D

void setup() {
  oled.begin();       // Hardware init
  oled.clearScr();    // Clear display RAM (see note on 'inflate' below!)
  oled.print("Hello!", 0, 0);
}
```

**Fragments** are advanced high-level constructs for complex dynamic UIs, dashboards, menus, and batching animations, inspired by Android fragments.

---

### What Are Fragments?

A **Fragment** is a collection of **Drawable objects** (`Text`, `Rectangle`, `Circle`, `Line`, `Bitmap`, `HighlightedText`, `AnimatedText`, `GridView`, etc.) whose display logic and update cycles are managed together.  
- Unlike direct draw calls, drawables can be created, modified, shown/hidden, and efficiently batched.

#### Benefits

- **Batch updates**: Redraw many items with a single command.  
- **Efficient scene graph**: Only changed parts (and optionally only changed objects) are updated/redrawn.  
- **Reusable UIs**: Fragments can act as entire screens, panels, or widgets, and can be pushed/popped from a stack.

---

### Getting Started with Fragments

**Header:**
```cpp
#include <SSD1306.h>
#include <Fragments.h>
```

**Basic Example:**
```cpp
OLED oled(128, 64);
FragmentManager manager(oled);      // Scene controller
Fragment fragment(manager);         // Create a batch (fragment)

Text* txt = new Text("Dynamic", 10, 0);
Rectangle* rec = new Rectangle(15, 16, 30, 8, 2, 1, false);

fragment.add(txt);
fragment.add(rec);
fragment.inflate();                 // Render all to display

// Later: update and redraw only changed things
*txt = Text("Changed!", 10, 10);
rec->setVisibility(false);
fragment.recycle();                 // Only changed ones are re-inflated
```

### Drawable Object Model

- **Text / HighlightedText / AnimatedText**
- **Rectangle / Circle / Line**
- **Bitmap**
- **GridView** (see below)

All are subclasses of `Drawable`. Each has:
- `draw(OLED&)` — internal; managed by fragment
- `setVisibility(bool)`
- `getVisibility()`
- `setChangeState()`, `getChangeState()` — for efficient redraws when mutated

### GridView

Create a structured layout of any Drawable type for applications like menus or icon panels.

```cpp
Circle* circle = new Circle(0, 0, 8, 2);
GridView* grid = new GridView(circle, 12, 4, 10, 10, 10, 10);
fragment.add(grid);
```
- `count`: Number of items
- `countPerLine`: How many per row
- `startX`, `startY`: grid’s origin
- `separationX`, `separationY`: pixel spacing

### Fragment Back Stack

Push/pop entire UI “screens” in stack order:

```cpp
// Show new
manager.addToBackStack(&fragment);
// Go back
manager.popBackStack();
```
- Use for simple UI routing/scene switching

### Fragment API Summary

- `add(Drawable*)`
- `inflate()`         // Draw all on-screen
- `recycle()`         // Only changed drawables
- `recycleAll()`      // Force all to redraw
- `recycleNew()`      // Only new (not previously displayed) drawables
- `detach()`          // Cleanup (doesn't clear display)
- See class docs for all details

## Method Reference — OLED Class

Each method is ready for copy-paste or quick lookup.

### Constructor
```cpp
OLED(uint8_t width, uint8_t height);
OLED(uint8_t width, uint8_t height, uint8_t address);
```
Create a new OLED display object with given dimensions and optional I2C address.

### begin
```cpp
void begin();
```
Initialize hardware. Call first.

### clearScr
```cpp
void clearScr();
void clearScr(bool refresh);
```
Clear the buffer; with `refresh==true`, update display immediately.

### inflate
```cpp
void inflate();
```
Push buffer to the display.

### print
```cpp
void print(String text, uint8_t x, uint8_t y);
```
Print `text` at position `(x, y)`.

### printHighlighted
```cpp
void printHighlighted(String text, uint8_t x, uint8_t y);
```
Print highlighted (inverted bg) text.

### printAnimated
```cpp
void printAnimated(String text, uint8_t x, uint8_t y, int delay, bool highlight);
```
Typewriter effect.

### print_c
```cpp
void print_c(String text, uint8_t x, uint8_t y);
```
Clear then print at `(x, y)`.

### setFont
```cpp
void setFont(const uint8_t (*fontArray)[5]);
```
Set a custom font array.

### clearCustomFont
```cpp
void clearCustomFont();
```
Revert to default font.

### convertString
```cpp
char* convertString(String str);
```
Get a C-string from Arduino `String`.

### progressBar
```cpp
void progressBar(uint8_t progress, uint8_t x, uint8_t y, int style);
```
Progress bar/loader at `(x, y)` for 0–100% progress.

### draw (bitmap)
```cpp
void draw(const uint8_t* data, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
```
Draw a bitmap.

### rectangle
```cpp
void rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t cornerRadius, uint8_t thickness, bool fill);
```
Draw a rectangle (with optional rounded corners).

### circle
```cpp
void circle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint8_t thickness);
```
Draw a circle.

### line
```cpp
void line(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t thickness);
```
Draw a line.

### clearArea
```cpp
void clearArea(uint8_t startX, uint8_t endX, uint8_t page);
```
Clear rectangular region on a page.

### manualSetup
```cpp
void manualSetup(uint8_t* dataSet);
```
Low-level OLED configuration.

### setBrightness
```cpp
void setBrightness(uint8_t brightness);
```
Set brightness (0–100).

### setPowerMode
```cpp
void setPowerMode(uint8_t mode);
```
Set I2C speed/power (see constants).

### superBrightness
```cpp
void superBrightness(bool mode);
```
Overdrive all pixels (may flicker/unreliable).

### invertDisplay
```cpp
void invertDisplay();
```
Invert current display (black→white).

### invertPixelState
```cpp
void invertPixelState(bool state);
```
Explicitly set inversion on/off.

### entireDisplayON / entireDisplayOFF
```cpp
void entireDisplayON();
void entireDisplayOFF();
```
Light up or restore all pixels.

### turnOffOnClr
```cpp
void turnOffOnClr(bool mode);
```
Display powers down when buffer is cleared.

### Data Plotting Methods

**Pulse/Wave Plot**
```cpp
void pulsePlot(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int* data, uint8_t size, int maxVal, int median = 0);
```

**Bit Bar Plot**
```cpp
void bitBarPlot(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int* data, uint8_t size, int maxVal, int median = 0);
```

**Scatter Plot**
```cpp
void scatterPlot(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int* data, uint8_t size, int maxVal, int median = 0);
```

**Histogram Plot**
```cpp
void histogramPlot(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int* data, uint8_t size, int maxVal);
```
All these display visualizations for sensor or dynamic data.

---

### Operator Overloading and Drawable Management

#### Setup Example
```cpp
#include <SSD1306.h>

OLED oled(128, 64);
FragmentManager mgr(oled);
Fragment fragment(mgr);

// Create drawables
Text* t = new Text("Hi!", 0, 0);
Rectangle* r = new Rectangle(10, 10, 20, 8, 1, 1, false);

// Add to fragment
fragment.add(t);
fragment.add(r);
fragment.inflate();  // Draw all at once

// Update only changed drawables
*t = Text("Bye!", 0, 10);
fragment.recycle();
```

---

#### Drawable Types
- `Text`
- `HighlightedText`
- `AnimatedText`
- `Rectangle`
- `Circle`
- `Line`
- `Bitmap`
- `GridView` — Structured layouts for icons and menus

---

#### Drawable Methods
Each drawable supports:
- `setVisibility(bool visible)`
- `getVisibility()`
- `setChangeState()`
- `getChangeState()`
- Assignment and re-initialization for dynamic updates

---

#### GridView Example
```cpp
Circle* circ = new Circle(0, 0, 8, 2);
GridView* grid = new GridView(circ, 12, 4, 10, 10, 10, 10);
fragment.add(grid);
```

#### Fragment Back Stack

Manage a stack of scenes/configurations:
```cpp
mgr.addToBackStack(&fragment);    // Push
mgr.popBackStack();               // Pop
```

## Fragment/Drawable API Reference

**Fragment**
- `add(Drawable*)` — Add a new element.
- `inflate()` — Draw all on display.
- `recycle()` — Only update changed elements.
- `recycleAll()` — Redraw everything.
- `recycleNew()` — Only draw new (not previously displayed) drawables.
- `detach()` — Remove all drawables.

**Drawable** (for each type):
- `setVisibility(bool)`
- `getVisibility()`
- `setChangeState()`
- `getChangeState()`
- Assignment operator (`=`) for re-use.

## Constants Quick Reference

### Display Setup
| Constant          | Value  | Description                    |
|-------------------|--------|--------------------------------|
| `ADDR`            | 0x3C   | Default I2C address            |
| `WIDTH_128`       | 0x80   | 128 px width                   |
| `WIDTH_64`        | 0x40   | 64 px width                    |
| `HEIGHT_64`       | 0x40   | 64 px height                   |
| `HEIGHT_32`       | 0x20   | 32 px height                   |

### Power Modes
| Constant             | Value  | Description                 |
|----------------------|--------|-----------------------------|
| `LOW_POWER_MODE`     | 0x01   | 100kHz I2C                  |
| `BALANCED_MODE`      | 0x02   | 200kHz I2C                  |
| `PERFORMANCE_MODE`   | 0x03   | 400kHz I2C                  |
| `TURBO_MODE`         | 0x04   | 1MHz I2C (auto fallback)    |

### Addressing Modes
| Constant     | Value  | Description           |
|--------------|--------|-----------------------|
| `HORIZONTAL` | 0x00   | Horizontal addressing |
| `VERTICAL`   | 0x01   | Vertical addressing   |
| `PAGE`       | 0x02   | Page addressing       |

### Special Commands
`OLED_OFF`, `OLED_ON`, `INVERT`, `REVERT`, `ENTIRE_DISP_ON`, `RESUME_FROM_VRAM`, `CHRG_PUMP`, `CONTRAST`, `PRE_CHRG`, `VCOMH_DESEL`, etc. (see header for full list).

## Data Visualization Example (Plots)

```cpp
int values[] = {1, 2, -1, 0, 3, -2, 2, 1, 0};
oled.pulsePlot(0, 0, 128, 32, values, 9, 3, 0);

int binaryValues[] = {0, 1, 0, 1, 1, 0};
oled.bitBarPlot(0, 34, 128, 16, binaryValues, 6, 1, 0);

int samples[] = {3, 0, 2, 1, 3};
oled.scatterPlot(0, 52, 128, 12, samples, 5, 3, 0);

int histogramData[] = {2, 4, 1, 3, 5};
oled.histogramPlot(0, 60, 128, 16, histogramData, 5, 5);
```
---

## Bitmap Generator Tool

Python script for converting images to OLED-ready bitmaps.

```bash
python bitmap_generator.py  
# Example:
python bitmap_generator.py images/logo.png logo.h
```
Add the script’s folder to your `PATH` for even faster use.

## License

**MIT License**