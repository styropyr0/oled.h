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

void Circle::setChangeState()
{
    changeState = false;
}

bool Circle::getChangeState()
{
    bool temp = changeState;
    changeState = false;
    return changeState;
}

Circle &Circle::operator=(const Circle &other)
{
    centreX = other.centreX;
    centreY = other.centreY;
    radius = other.radius;
    thickness = other.thickness;
    changeState = true;
    return *this;
}

void Circle::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool Circle::getVisibility()
{
    return visibility;
}

Circle::~Circle()
{
    // delete this;
}

Rectangle::Rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t cornerRadius, uint8_t thickness, bool fill)
    : x(x), y(y), width(width), height(height), cornerRadius(cornerRadius), thickness(thickness), fill(fill) {}

void Rectangle::draw(OLED &oled)
{
    oled.rectangle(x, y, width, height, cornerRadius, thickness, fill);
}

const char *Rectangle::type() const
{
    return "Rectangle";
}

void Rectangle::setChangeState()
{
    changeState = false;
}

bool Rectangle::getChangeState()
{
    bool temp = changeState;
    changeState = false;
    return changeState;
}

Rectangle &Rectangle::operator=(const Rectangle &other)
{
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
    cornerRadius = other.cornerRadius;
    thickness = other.thickness;
    changeState = true;
    return *this;
}

void Rectangle::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool Rectangle::getVisibility()
{
    return visibility;
}

Rectangle::~Rectangle()
{
    // delete this;
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

void Line::setChangeState()
{
    changeState = false;
}

bool Line::getChangeState()
{
    bool temp = changeState;
    changeState = false;
    return changeState;
}

Line &Line::operator=(const Line &other)
{
    startX = other.startX;
    startY = other.startY;
    endX = other.endX;
    endY = other.endY;
    thickness = other.thickness;
    changeState = true;
    return *this;
}

void Line::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool Line::getVisibility()
{
    return visibility;
}

Line::~Line()
{
    // delete this;
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

void Bitmap::setChangeState()
{
    changeState = false;
}

bool Bitmap::getChangeState()
{
    bool temp = changeState;
    changeState = false;
    return changeState;
}

Bitmap &Bitmap::operator=(const Bitmap &other)
{
    dataSet = other.dataSet;
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
    changeState = true;
    return *this;
}

void Bitmap::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool Bitmap::getVisibility()
{
    return visibility;
}

Bitmap::~Bitmap()
{
    // delete this;
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

void Text::setChangeState()
{
    changeState = false;
}

bool Text::getChangeState()
{
    bool temp = changeState;
    changeState = false;
    return temp;
}

Text &Text::operator=(const Text &other)
{
    text = other.text;
    x = other.x;
    y = other.y;
    changeState = true;
    changeState = true;
    return *this;
}

void Text::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool Text::getVisibility()
{
    return visibility;
}

Text::~Text()
{
    // delete this;
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

void HighlightedText::setChangeState()
{
    changeState = false;
}

bool HighlightedText::getChangeState()
{
    bool temp = changeState;
    changeState = false;
    return changeState;
}

HighlightedText &HighlightedText::operator=(const HighlightedText &other)
{
    text = other.text;
    x = other.x;
    y = other.y;
    changeState = true;
    return *this;
}

void HighlightedText::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool HighlightedText::getVisibility()
{
    return visibility;
}

HighlightedText::~HighlightedText()
{
    // delete this;
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

void AnimatedText::setChangeState()
{
    changeState = false;
}

bool AnimatedText::getChangeState()
{
    bool temp = changeState;
    changeState = false;
    return changeState;
}

AnimatedText &AnimatedText::operator=(const AnimatedText &other)
{
    text = other.text;
    x = other.x;
    y = other.y;
    delay = other.delay;
    highlight = other.highlight;
    changeState = true;
    return *this;
}

void AnimatedText::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool AnimatedText::getVisibility()
{
    return visibility;
}

AnimatedText::~AnimatedText()
{
    // delete this;
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

void GridView::setChangeState()
{
    changeState = false;
}

bool GridView::getChangeState()
{
    bool temp = changeState;
    changeState = false;
    return changeState;
}

GridView &GridView::operator=(const GridView &other)
{
    drawable = other.drawable;
    count = other.count;
    countPerLine = other.countPerLine;
    startX = other.startX;
    startY = other.startY;
    seperationX = other.seperationX;
    seperationY = other.seperationY;
    changeState = true;
    return *this;
}

void GridView::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool GridView::getVisibility()
{
    return visibility;
}

GridView::~GridView()
{
    // delete this;
}