#ifndef Fragments
#define Fragments

#include "SSD1306.h"

#ifdef __cplusplus

class Fragment;

/**
 * @brief Manager for fragments. You can pass different OLED objects for multiple displays to reuse fragments generated
 * by attaching fragment managers to the fragments.
 */
class FragmentManager
{
private:
    OLED *oled;
    Fragment **fragments = nullptr;
    int fragmentCount = 0;

public:
    /**
     * @brief Constructs a FragmentManager with a reference to an OLED object.
     * @param oled Reference to an OLED object.
     */
    FragmentManager(OLED &oled);

    /**
     * @brief Gets the OLED object managed by this FragmentManager.
     * @returns Pointer to the OLED object.
     */
    OLED *getOLED();

    /**
     * @brief Adds a fragment to the back stack.
     */
    void addToBackStack(Fragment *fragment);

    /**
     * @brief Pops the last fragment from the back stack.
     */
    void popBackStack();
};

/**
 * @brief Abstract base class for drawable objects.
 */
class Drawable
{
public:
    /**
     * @brief Draws the object on the OLED display.
     * @param oled Reference to the OLED object.
     */
    virtual void draw(OLED &oled) = 0;

    /**
     * @brief Returns the type of the object.
     */
    virtual const char *type() const = 0;

    /**
     * @brief Virtual destructor for Drawable.
     */
    virtual ~Drawable() = default;

    /**
     * @brief Changes the modifications state of the object.
     */
    virtual void setChangeState() = 0;

    /**
     * @brief Returns the modification state of the object.
     */
    virtual bool getChangeState() = 0;

    /**
     * @brief Set the visibility of the drawable.
     */
    virtual void setVisibility(bool visibility) = 0;

    /**
     * @brief Returns the visibility of the drawable.
     */
    virtual bool getVisibility() = 0;
};

class Circle : public Drawable
{
private:
    struct
    {
        uint8_t centreX = 0, centreY = 0, radius = 0, thickness = 0;
        bool init = false;
    } entity;

    void draw(OLED &oled) override;
    const char *type() const override;
    uint8_t centreX, centreY, radius, thickness;
    bool changeState = true, visibility = true;
    void setChangeState() override;
    bool getChangeState() override;
    bool getVisibility() override;

public:
    /**
     * @brief Constructs a Circle with specified parameters.
     * @param centerX X coordinate of the center.
     * @param centerY Y coordinate of the center.
     * @param radius Radius of the circle.
     * @param thickness Thickness of the circle.
     */
    Circle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint8_t thickness);
    Circle &operator=(const Circle &other);
    void setVisibility(bool visibility) override;
    ~Circle();
    friend class GridView;
};

class Rectangle : public Drawable
{
private:
    struct
    {
        uint8_t x = 0, y = 0, width = 0, height = 0, cornerRadius = 0, thickness = 0;
        bool fill, init = false;
    } entity;

    void draw(OLED &oled) override;
    const char *type() const override;
    uint8_t x, y, width, height, cornerRadius, thickness;
    bool changeState = true, visibility = true, fill = false;
    void setChangeState() override;
    bool getChangeState() override;
    bool getVisibility() override;

public:
    /**
     * @brief Constructs a Rectangle with specified parameters.
     * @param x X coordinate of the top-left corner.
     * @param y Y coordinate of the top-left corner.
     * @param width Width of the rectangle.
     * @param height Height of the rectangle.
     * @param cornerRadius Radius of the corners.
     * @param thickness Thickness of the rectangle.
     */
    Rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t cornerRadius, uint8_t thickness, bool fill);
    Rectangle &operator=(const Rectangle &other);
    void setVisibility(bool visibility) override;
    ~Rectangle();
    friend class GridView;
};

class Line : public Drawable
{
private:
    struct
    {
        uint8_t startX = 0, startY = 0, endX = 0, endY = 0, thickness = 0;
        bool init = false;
    } entity;

    void draw(OLED &oled) override;
    const char *type() const override;
    uint8_t startX, startY, endX, endY, thickness;
    bool changeState = true, visibility = true;
    void setChangeState() override;
    bool getChangeState() override;
    bool getVisibility() override;

public:
    /**
     * @brief Constructs a Line with specified parameters.
     * @param startX X coordinate of the starting point.
     * @param startY Y coordinate of the starting point.
     * @param endX X coordinate of the ending point.
     * @param endY Y coordinate of the ending point.
     * @param thickness Thickness of the line.
     */
    Line(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t thickness);
    Line &operator=(const Line &other);
    void setVisibility(bool visibility) override;
    ~Line();
    friend class GridView;
};

class Text : public Drawable
{
private:
    struct
    {
        String text = "";
        uint8_t x = 0, y = 0;
        bool init = false;
    } entity;

    String text;
    uint8_t x, y;
    void draw(OLED &oled) override;
    const char *type() const override;
    bool changeState = true, visibility = true;
    void setChangeState() override;
    bool getChangeState() override;
    bool getVisibility() override;

public:
    /**
     * @brief Constructs a Text object with specified parameters.
     * @param text The string to be printed.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     */
    Text(String text, uint8_t x, uint8_t y);
    Text &operator=(const Text &other);
    void setVisibility(bool visibility) override;
    ~Text();
};

class HighlightedText : public Drawable
{
private:
    struct
    {
        String text = "";
        uint8_t x = 0, y = 0;
        bool init = false;
    } entity;

    String text;
    uint8_t x, y;
    void draw(OLED &oled) override;
    const char *type() const override;
    bool changeState = true, visibility = true;
    void setChangeState() override;
    bool getChangeState() override;
    bool getVisibility() override;

public:
    /**
     * @brief Constructs a HighlightedText object with specified parameters.
     * @param text The string to be printed.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     */
    HighlightedText(String text, uint8_t x, uint8_t y);
    HighlightedText &operator=(const HighlightedText &other);
    void setVisibility(bool visibility) override;
    ~HighlightedText();
};

class AnimatedText : public Drawable
{
private:
    String text;
    uint8_t x, y;
    int delay;
    bool highlight;
    void draw(OLED &oled) override;
    const char *type() const override;
    bool changeState = true, visibility = true;
    void setChangeState() override;
    bool getChangeState() override;
    bool getVisibility() override;

public:
    /**
     * @brief Constructs an AnimatedText object with specified parameters.
     * @param text The string to be printed.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     * @param delay The delay between each character.
     * @param highlight Whether the text should be highlighted.
     */
    AnimatedText(String text, uint8_t x, uint8_t y, int delay, bool highlight);
    AnimatedText &operator=(const AnimatedText &other);
    void setVisibility(bool visibility) override;
    ~AnimatedText();
};

class Bitmap : public Drawable
{
private:
    struct
    {
        const uint8_t *dataSet = nullptr;
        uint8_t x = 0, y = 0, width = 0, height = 0;
        bool init = false;
    } entity;

    const uint8_t *dataSet;
    uint8_t x, y, width, height;
    void draw(OLED &oled) override;
    const char *type() const override;
    bool changeState = true, visibility = true;
    void setChangeState() override;
    bool getChangeState() override;
    bool getVisibility() override;

public:
    /**
     * @brief Constructs a Bitmap object with specified parameters.
     * @param dataSet Bitmap array.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     * @param width Width of the bitmap.
     * @param height Height of the bitmap.
     */
    Bitmap(const uint8_t *dataSet, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    Bitmap &operator=(const Bitmap &other);
    void setVisibility(bool visibility) override;
    ~Bitmap();
    friend class GridView;
};

class GridView : public Drawable
{
private:
    Drawable *drawable;
    uint8_t count, countPerLine, startX, startY, seperationX, seperationY;
    void draw(OLED &oled) override;
    const char *type() const override;
    bool changeState = true, visibility = true;
    bool checkType();
    void setChangeState() override;
    bool getChangeState() override;
    bool getVisibility() override;

public:
    GridView(Drawable *drawable, uint8_t count, uint8_t countPerLine, uint8_t startX, uint8_t startY, uint8_t seperationX, uint8_t seperationY);
    GridView &operator=(const GridView &other);
    void setVisibility(bool visibility) override;
    ~GridView();
};

/**
 * @brief Fragment is a dynamic collection of drawable objects.
 * Use the add function to add the drawables into the fragment.
 * Use the inflate function to inflate the fragment.
 * Once inflated, if the fragment is modified, you may use the recycle method to apply changes.
 */
class Fragment
{
private:
    FragmentManager &manager;
    Drawable **drawables = nullptr;
    uint8_t drawableCount;
    uint8_t drawableCapacity;
    uint8_t lastCount = 0;
    bool isDetached = false;

public:
    /**
     * @brief Constructs a Fragment with a reference to a FragmentManager.
     * @param manager Reference to a FragmentManager object.
     */
    explicit Fragment(FragmentManager &manager);

    /**
     * @brief Destructor for Fragment. Cleans up dynamically allocated memory.
     */
    ~Fragment();

    /**
     * @brief Adds a drawable object to the fragment.
     * @param drawable Pointer to a Drawable object.
     */
    void add(Drawable *drawable);

    /**
     * @brief Draws all drawable objects in the fragment on the OLED display.
     */
    void inflate();

    /**
     * @brief Applies changes to modified drawables without re-inflating them.
     * It is recommended to call recycle after modifying a fragment which is already inflated.
     */
    void recycle();

    /**
     * @brief Applies changes to modified drawables re-inflating all of them.
     * It is recommended to call recycle after modifying a fragment which is already inflated.
     */
    void recycleAll();

    /**
     * @brief Applies changes to newly added drawables without re-inflating the drawables.
     * It is recommended to call recycle after adding a view to a fragment which is already inflated.
     */
    void recycleNew();

    /**
     * @brief Removes all fragments and frees up memory.
     * It is recommended to call detach if you no longer use a fragment.
     * This will not clear the screen.
     */
    void detach();
};

#endif
#endif