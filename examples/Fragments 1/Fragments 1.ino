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
  Rectangle* border = new Rectangle(0, 0, 127, 63, 3, 1);
  Circle* circle = new Circle(64, 32, 10, 2);
  Text* text = new Text("Initial Text", 10, 3);
  
  // Add drawables to the fragment
  fragment.add(border);
  fragment.add(circle);
  fragment.add(text);
  
  // Draw all the fragment’s drawables
  fragment.inflate();

  // Wait for 2 seconds
  delay(2000);

  // Change the text and hide the circle
  *text = Text("Updated Text", 10, 3);
  circle->setVisibility(false);
  
  // Recycle all drawables to apply changes
  fragment.recycleAll();
}

void loop() {
  // Main loop logic (empty in this example)
}
