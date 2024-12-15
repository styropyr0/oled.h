#include "SSD1306.h"
#include "Fragments.h"

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
    if (checkType())
    {
        uint8_t tempX;
        if (drawable->type() == "Line")
        {
            Line *line = static_cast<Line *>(drawable);
            uint8_t dX = abs(line->startX - line->endX);
            uint8_t dY = abs(line->startY - line->endY);
            tempX = startX;

            for (uint8_t col = 0; col < count / countPerLine; col++)
            {
                startX = tempX;
                for (uint8_t row = 0; row < countPerLine; row++)
                {
                    line->startX = startX;
                    line->startY = startY;
                    line->endX = line->startX + dX;
                    line->endY = line->startY + dY;
                    startX += dX + seperationX;
                    line->draw(oled);
                    yield();
                }
                startY += dY + seperationY;
            }
        }
        else if (drawable->type() == "Rectangle")
        {
            Rectangle *rectangle = static_cast<Rectangle *>(drawable);
            tempX = startX;
            for (uint8_t col = 0; col < count / countPerLine; col++)
            {
                startX = tempX;
                for (uint8_t row = 0; row < countPerLine; row++)
                {
                    rectangle->x = startX;
                    rectangle->y = startY;
                    startX += rectangle->width + seperationX;
                    rectangle->draw(oled);
                    yield();
                }
                startY += rectangle->height + seperationY;
            }
        }
        else if (drawable->type() == "Circle")
        {
            Circle *circle = static_cast<Circle *>(drawable);
            tempX = startX;
            for (uint8_t col = 0; col < count / countPerLine; col++)
            {
                startX = tempX;
                for (uint8_t row = 0; row < countPerLine; row++)
                {
                    circle->centreX = startX;
                    circle->centreY = startY;
                    startX += circle->radius * 2 + seperationX;
                    circle->draw(oled);
                    yield();
                }
                startY += circle->radius * 2 + seperationY;
            }
        }
        else if (drawable->type() == "Bitmap")
        {
            Bitmap *bitmap = static_cast<Bitmap *>(drawable);
            tempX = startX;
            for (uint8_t col = 0; col < count / countPerLine; col++)
            {
                startX = tempX;
                for (uint8_t row = 0; row < countPerLine; row++)
                {
                    bitmap->x = startX;
                    bitmap->y = startY;
                    startX += bitmap->width + seperationX;
                    bitmap->draw(oled);
                    yield();
                }
                startY += bitmap->height + seperationY;
            }
        }
    }
    delete drawable;
}

bool GridView::checkType()
{
    return drawable->type() == "Line" || drawable->type() == "Rectangle" || drawable->type() == "Circle" || drawable->type() == "Bitmap";
}

const char *GridView::type() const
{
    return "GridView";
}