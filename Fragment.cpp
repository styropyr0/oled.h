#include "SSD1306.h"
#include "Fragments.h"

/**
 * @author Saurav Sajeev
 */

FragmentManager::FragmentManager(OLED &oled) : oled(&oled) {}

void FragmentManager::addToBackStack(Fragment *fragment)
{
    Fragment **newFragments = new Fragment *[1];
    for (int i = 0; i < fragmentCount; ++i)
    {
        newFragments[i] = fragments[i];
        yield();
    }
    if (fragments != nullptr)
        delete[] fragments;
    fragments = newFragments;
    fragments[fragmentCount++] = fragment;
}

void FragmentManager::popBackStack()
{
    if (fragmentCount > 0)
    {
        fragments[--fragmentCount] = nullptr;
        fragmentCount--;
        oled->clearScr();
        fragments[fragmentCount]->recycleAll();
    }
}

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
    if (!isDetached)
    {
        for (int i = 0; i < drawableCount; ++i)
        {
            delete drawables[i];
        }
        delete[] drawables;
    }
    drawables = nullptr;
    drawableCount = 0;
    drawableCapacity = 0;
    lastCount = 0;
    isDetached = true;
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
        drawables[i]->setChangeState();
    }
    oled.inflate();
    lastCount = drawableCount;
}

void Fragment::recycleNew()
{
    OLED &oled = *manager.getOLED();
    oled.clearScr();
    for (int i = lastCount - 1; i < drawableCount; ++i)
    {
        if (drawables[i]->getVisibility() && drawables[i]->getChangeState())
        {
            drawables[i]->draw(oled);
            drawables[i]->setChangeState();
        }
    }
    oled.inflate();
    lastCount = drawableCount;
}

void Fragment::recycle()
{
    OLED &oled = *manager.getOLED();
    for (int i = 0; i < drawableCount; ++i)
    {
        if (drawables[i]->getChangeState())
        {
            drawables[i]->draw(oled);
        }
    }
    oled.inflate();
    lastCount = drawableCount;
}

void Fragment::recycleAll()
{
    OLED &oled = *manager.getOLED();
    oled.clearScr();
    for (int i = 0; i < drawableCount; ++i)
    {
        if (drawables[i]->getVisibility())
        {
            drawables[i]->draw(oled);
            drawables[i]->setChangeState();
        }
    }
    oled.inflate();
    lastCount = drawableCount;
}

void Fragment::detach()
{
    if (isDetached)
        return;
    isDetached = true;
    for (int i = 0; i < drawableCount; ++i)
    {
        delete drawables[i];
    }
    delete[] drawables;
    drawables = nullptr;
    drawableCount = 0;
    drawableCapacity = 0;
    lastCount = 0;
}