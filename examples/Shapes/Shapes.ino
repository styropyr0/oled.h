#include <SSD1306.h>

// Create OLED object with width and height (128x64)
OLED oled(128, 64);

void setup() {
  // Initialize the OLED display
  oled.begin();
  
  // Clear the screen
  oled.clearScr();
  
  // Draw a rectangle at (10, 10) with width 50, height 30, 5px corner radius, and 2px thickness
  oled.rectangle(10, 10, 50, 30, 5, 2, false);

  delay(1000);
  
  // Draw a circle at (64, 32) with radius 20, and thickness 2px
  oled.circle(64, 32, 20, 2);

  delay(1000);
  
  // Draw a line from (0, 0) to (127, 63), 2px thick
  oled.line(0, 0, 127, 63, 2);
}

void loop() {
  // Main loop logic (empty in this example)
}
