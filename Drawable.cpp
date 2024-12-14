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

const char *Circle::type() const
{
    return "Circle";
}

Rectangle::Rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t cornerRadius, uint8_t thickness)
    : x(x), y(y), width(width), height(height), cornerRadius(cornerRadius), thickness(thickness) {}

void Rectangle::draw(OLED &oled)
{
    oled.rectangle(x, y, width, height, cornerRadius, thickness);
}

const char *Rectangle::type() const
{
    return "Rectangle";
}

Line::Line(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t thickness)
    : startX(startX), startY(startY), endX(endX), endY(endY), thickness(thickness) {}

void Line::draw(OLED &oled)
{
    oled.line(startX, startY, endX, endY, thickness);
}

const char *Line::type() const
{
    return "Line";
}

Bitmap::Bitmap(const uint8_t *dataSet, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
    : dataSet(dataSet), x(x), y(y), width(width), height(height) {}

void Bitmap::draw(OLED &oled)
{
    oled.draw(dataSet, x, y, width, height);
}

const char *Bitmap::type() const
{
    return "Bitmap";
}

Text::Text(String text, uint8_t x, uint8_t y)
    : text(text), x(x), y(y) {}

void Text::draw(OLED &oled)
{
    oled.print(text, x, y);
}

const char *Text::type() const
{
    return "Text";
}

HighlightedText::HighlightedText(String text, uint8_t x, uint8_t y)
    : text(text), x(x), y(y) {}

void HighlightedText::draw(OLED &oled)
{
    oled.printHighlighted(text, x, y);
}

const char *HighlightedText::type() const
{
    return "HighlightedText";
}

AnimatedText::AnimatedText(String text, uint8_t x, uint8_t y, int delay, bool highlight)
    : text(text), x(x), y(y), delay(delay), highlight(highlight) {}

void AnimatedText::draw(OLED &oled)
{
    oled.printAnimated(text, x, y, delay, highlight);
}

const char *AnimatedText::type() const
{
    return "AnimatedText";
}

GridView::GridView(Drawable *drawable, uint8_t count, uint8_t countPerLine, uint8_t startX, uint8_t startY, uint8_t seperationX, uint8_t seperationY)
    : drawable(drawable), count(count), countPerLine(countPerLine), startX(startX), startY(startY), seperationX(seperationX), seperationY(seperationY) {}

void GridView::draw(OLED &oled)
{
    // uint8_t temp_x = (startX - endX), temp_y = abs(startY - endY);
    if (checkType())
    {
        for (int i = 0; i < count; i++)
        {
            if (drawable->type() == "Line")
            {
                // line(startX+temp_x*i, startY+temp_y*i, )
            }
        }
    }
    else
    {
        delete drawable;
    }
}

bool GridView::checkType()
{
    return drawable->type() == "Line" || drawable->type() == "Rectangle" || drawable->type() == "Circle" || drawable->type() == "Bitmap";
}

const char *GridView::type() const
{
    return "GridView";
}