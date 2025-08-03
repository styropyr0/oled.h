#include <SSD1306.h>

OLED oled(128, 64);
int fps = 0;

int data[128] = {
    18, 4, 11, 26, 23, 3, 9, 12, 1, 19, 10, 25, 7, 0, 21, 2,
    6, 17, 14, 15, 5, 13, 8, 16, 22, 20, 24, 0, 1, 9, 7, 12,
    5, 14, 10, 3, 6, 11, 17, 15, 23, 13, 26, 8, 4, 19, 18, 2,
    20, 22, 25, 16, 0, 7, 9, 1, 10, 24, 3, 6, 14, 8, 12, 19,
    11, 23, 21, 5, 15, 18, 13, 4, 2, 17, 22, 16, 20, 26, 0, 1,
    7, 3, 9, 5, 14, 10, 6, 12, 24, 11, 19, 15, 8, 13, 23, 2,
    21, 25, 18, 4, 0, 22, 16, 6, 1, 7, 10, 14, 20, 3, 9, 5,
    17, 12, 11, 26, 15, 13, 19, 23, 8, 2, 21, 24, 22, 0, 16, 25
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
    oled.histogramPlot(0, 0, 64, 64, data, 120, 26);

    // Display FPS
    oled << String(fps) + " fps" << 80 << 28;
    oled.inflate();

    fps = 1 / ((float)(millis() - start) / 1000);
    delay(100); // Adjust animation speed
}