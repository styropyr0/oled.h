#include <Arduino.h>
#include <math.h>
#include <SSD1306.h>

// Define the cube’s 8 corners in 3D
float cube[8][3] = {
    {-1, -1, -1},
    {1, -1, -1},
    {1, 1, -1},
    {-1, 1, -1},
    {-1, -1, 1},
    {1, -1, 1},
    {1, 1, 1},
    {-1, 1, 1}};

// Edge connections between cube points
int edges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
    {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
    {0, 4}, {1, 5}, {2, 6}, {3, 7}  // sides
};

float angle = 0;
int fps = 0;

OLED oled(128, 64);

void setup()
{
    oled.begin();
    oled.clearScr();

    // Set performance mode for maximum fps
    oled.setPowerMode(PERFORMANCE_MODE);
}

void loop()
{
    long int start = millis();
    float rotated[8][3];

    // Rotate cube in 3D
    for (int i = 0; i < 8; i++)
    {
        float x = cube[i][0];
        float y = cube[i][1];
        float z = cube[i][2];

        // Rotate around Y axis
        float x1 = x * cos(angle) + z * sin(angle);
        float z1 = -x * sin(angle) + z * cos(angle);

        // Rotate around X axis
        float y1 = y * cos(angle) - z1 * sin(angle);
        float z2 = y * sin(angle) + z1 * cos(angle);

        rotated[i][0] = x1;
        rotated[i][1] = y1;
        rotated[i][2] = z2;
    }

    oled.clearScr();

    // Project 3D to 2D and draw edges
    for (int i = 0; i < 12; i++)
    {
        int p1 = edges[i][0];
        int p2 = edges[i][1];

        float d = 3.0;
        float s = 40.0;
        int cx = 64;
        int cy = 32;

        int x0 = (rotated[p1][0] / (rotated[p1][2] + d)) * s + cx;
        int y0 = (rotated[p1][1] / (rotated[p1][2] + d)) * s + cy;
        int x1 = (rotated[p2][0] / (rotated[p2][2] + d)) * s + cx;
        int y1 = (rotated[p2][1] / (rotated[p2][2] + d)) * s + cy;

        oled.line(x0, y0, x1, y1, 1);
    }

    // Display FPS on lower left corner
    oled << String(fps) + " fps" << 3 << 54;

    // Inflate the contents
    oled.inflate();
    
    angle += 0.05;
    fps = 1 / ((float)(millis() - start) / 1000);
    delay(30);
}
