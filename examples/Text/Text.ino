#include <SSD1306.h>

// Create OLED object with width and height (128x64)
OLED oled(128, 64);

void setup() {
  // Initialize the OLED display
  oled.begin();
  
  // Clear the screen
  oled.clearScr();
  
  // Print text at (0, 0)
  oled.print("Hello, World!", 0, 0);
  
  // Print text at (0, 3) using chaining operators
  oled << "This method also prints!" << 0 << 3;
}

void loop() {
  // Main loop logic (empty in this example)
}
