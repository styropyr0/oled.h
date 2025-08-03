#include <SSD1306.h>

OLED oled(128, 64);
int fps = 0;

int data[128] = {
  -5, 14, -22, 8, 0, -11, 26, -27, 3, -18, 6, 17, -3, 28, -19, 12,
  -7, 24, -1, -8, 9, -15, 5, -23, 13, -4, 20, -10, 2, -17, 7, -6,
  -25, 18, -2, 21, -12, 1, -9, 27, -26, 11, -16, 22, -24, 10, -13, 4,
  -20, 19, -14, 15, -21, 25, -28, 16, -18, 0, -5, 6, -2, 14, -22, 7,
  -3, 23, -6, 2, -8, 13, -1, 17, -4, 12, -11, 26, -19, 3, -15, 5,
  -10, 24, -7, 18, -25, 9, -16, 0, -21, 20, -12, 28, -27, 6, -9, 4,
  -17, 1, -23, 7, -13, 11, -26, 22, -20, 10, -14, 19, -3, 8, -5, 16,
  -2, 15, -24, 21, -6, 0, -18, 13, -7, 5, -1, 17, -22, 12, -9, 25
};

void setup()
{
    oled.begin();
    oled.setPowerMode(PERFORMANCE_MODE);
    Serial.begin(9600);
}

void loop()
{
    int avg = 0;
    long int start = millis();
    for (int i = 0; i < 127; i++)
    {
        data[i] = data[i + 1];
        avg += data[i];
    }

    avg /= 127;
    data[127] = random(-26, 27);

    oled.clearScr();

    // Plot updated array
    oled.pulsePlot(0, 0, 64, 64, data, 120, 26);

    // Display FPS on lower left corner
    oled << String(fps) + " fps" << 80 << 28;
    oled.inflate();

    fps = 1 / ((float)(millis() - start) / 1000);
    delay(100); // Adjust animation speed
}