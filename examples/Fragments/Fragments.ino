#include <SSD1306.h>
#include <Fragments.h>

// Create OLED object with width and height (128x64)
OLED oled(128, 64);

// Create a FragmentManager object and attach it to the OLED object
FragmentManager mgr(oled);

void setup() {
  // Initialize the OLED display
  oled.begin();
  
  // Create a Fragment object and attach it to the FragmentManager
  Fragment fragment(mgr);
  
  // Create drawable objects
  Circle* circle = new Circle(0, 0, 8, 2);
  GridView* grid = new GridView(circle, 12, 4, 20, 10, 10, 4);
  
  // Add the GridView to the fragment
  fragment.add(grid);
  
  // Draw all the fragment’s drawables
  fragment.inflate();
}

void loop() {
  // Main loop logic (empty in this example)
}
