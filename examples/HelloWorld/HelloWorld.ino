#include <SSD1306.h>

OLED oled(128, 64);
void setup()
{
    oled.begin();
    oled << "Hello World!" << 64 << 32; // Print "Hello World!" at the center of the screen
    oled.inflate(); // Render the items on the display
    delay(1000); // Wait for 1 second
    oled.clearScr(); // Clear the screen
    oled.rectangle(15, 15, 100, 30, 5, 2, false); // Draw a rectangle at (15, 15) with width 100, height 30, 5px corner radius, and 2px thickness
    oled << "Hello World!" << 30 << 25; // Print "Hello World!" inside the rectangle
    oled.inflate(); // Render the items on the display
}

void loop()
{
}