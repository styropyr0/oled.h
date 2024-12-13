#include "SSD1306.h"

/**
 * @author Saurav Sajeev
 */

Circle::Circle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint8_t thickness)
    : centreX(centerX), centreY(centerY), radius(radius), thickness(thickness) {}

void Circle::draw(OLED &oled)
{
    oled.circle(centreX, centreY, radius, thickness);
}

Rectangle::Rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t cornerRadius, uint8_t thickness)
    : x(x), y(y), width(width), height(height), cornerRadius(cornerRadius), thickness(thickness) {}

void Rectangle::draw(OLED &oled)
{
    oled.rectangle(x, y, width, height, cornerRadius, thickness);
}

Line::Line(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t thickness)
    : startX(startX), startY(startY), endX(endX), endY(endY), thickness(thickness) {}

void Line::draw(OLED &oled)
{
    oled.line(startX, startY, endX, endY, thickness);
}

Bitmap::Bitmap(const uint8_t *dataSet, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
    : dataSet(dataSet), x(x), y(y), width(width), height(height) {}

void Bitmap::draw(OLED &oled)
{
    oled.draw(dataSet, x, y, width, height);
}

Text::Text(String text, uint8_t x, uint8_t y)
    : text(text), x(x), y(y) {}

void Text::draw(OLED &oled)
{
    oled.print(text, x, y);
}

HighlightedText::HighlightedText(String text, uint8_t x, uint8_t y)
    : text(text), x(x), y(y) {}

void HighlightedText::draw(OLED &oled)
{
    oled.printHighlighted(text, x, y);
}

AnimatedText::AnimatedText(String text, uint8_t x, uint8_t y, int delay, bool highlight)
    : text(text), x(x), y(y), delay(delay), highlight(highlight) {}

void AnimatedText::draw(OLED &oled)
{
    oled.printAnimated(text, x, y, delay, highlight);
}
