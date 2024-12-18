#include "SSD1306.h"
#include "Fragments.h"

/**
 * @author Saurav Sajeev
 */

FragmentManager::FragmentManager(OLED &oled) : oled(&oled) {}

OLED *FragmentManager::getOLED()
{
    return oled;
}

Fragment::Fragment(FragmentManager &manager)
    : manager(manager), drawableCount(0), drawableCapacity(2)
{
    drawables = new Drawable *[drawableCapacity];
}

Fragment::~Fragment()
{
    for (int i = 0; i < drawableCount; ++i)
    {
        delete drawables[i];
    }
    delete[] drawables;
}

void Fragment::add(Drawable *drawable)
{
    if (drawableCount >= drawableCapacity)
    {
        drawableCapacity *= 2;
        Drawable **newDrawables = new Drawable *[drawableCapacity];
        for (int i = 0; i < drawableCount; ++i)
        {
            newDrawables[i] = drawables[i];
            yield();
        }
        if (drawables != nullptr)
            delete[] drawables;
        drawables = newDrawables;
    }
    drawables[drawableCount++] = drawable;
}

void Fragment::inflate()
{
    OLED &oled = *manager.getOLED();
    for (int i = 0; i < drawableCount; ++i)
    {
        yield();
        drawables[i]->draw(oled);
    }
    lastCount = drawableCount;
}

void Fragment::recycle()
{
    OLED &oled = *manager.getOLED();
    for (int i = lastCount - 1; i < drawableCount; ++i)
    {
        drawables[i]->draw(oled);
    }
    lastCount = drawableCount;
}

void Fragment::detach()
{
    delete this;
}