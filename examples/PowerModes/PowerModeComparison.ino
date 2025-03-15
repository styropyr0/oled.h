#include <SSD1306.h>

OLED oled(128, 64);
uint8_t powerMode = LOW_POWER_MODE, cycle = 0;

void setup()
{
    oled.begin();
}

void loop()
{
    String modes[] = {"Low Power Mode", "Balanced Mode", "Performance Mode", "Turbo Mode"};
    oled.clearScr();
    oled << modes[powerMode - 1] << 0 << 26;
    oled.inflate();
    oled.setPowerMode(powerMode); // Set power mode

    // Progress bar
    for (uint8_t dir = 0, i = 0; cycle < 5; delay(10))
    {
        i = dir ? i - 5 : i + 5;
        if (i >= 100 || i <= 0)
            dir = !dir, cycle += dir ? 1 : 0;
        oled.progressBar(i, 25, 5, 13);
    }

    cycle = 0;
    if (++powerMode > TURBO_MODE)
        powerMode = LOW_POWER_MODE;
}
