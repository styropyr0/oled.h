#ifndef oled
#define oled
#define ADDR 0x3C

/**
 * @author Saurav Sajeev
 */

#include <Arduino.h>
#include <Wire.h>

enum dimensions
{
    WIDTH_128 = 0x80,
    WIDTH_64 = 0x40,
    HEIGHT_64 = 0x40,
    HEIGHT_32 = 0x20
};

enum registryAddress
{
    OLED_OFF = 0xAE,
    OLED_ON = 0xAF,
    DISP_CLOCK_DIV_RATIO = 0xD5,
    MULTIPLEX = 0xA8,
    CHRG_PUMP = 0x8D,
    DISP_OFFSET = 0xD3,
    MEM_ADDRESS_MODE = 0x20,
    COM_CONFIG = 0xDA,
    CONTRAST = 0x81,
    PRE_CHRG = 0xD9,
    VCOMH_DESEL = 0xDB,
    TURN_ON_ALL_PIXELS = 0xA4,
    SET_DISP_NORMAL = 0xA6,
    SET_COL_ADDR = 0x21,
    SET_PG_ADDR = 0x22
};

enum registryCommands
{
    CLK_RATIO_RST = 0x80,
    MULTIPLEX_RATIO_RST = 0x3F,
    OFFSET_NO = 0x00,
    HSCROLL_RIGHT = 0x26,
    HSCROLL_LEFT = 0x27,
    VHSCROLL_RIGHT = 0x29,
    VHSCROLL_LEFT = 0x2A,
    STOP_SCROLL = 0x2E,
    START_SCROLL = 0x2F,
    START_LINE = 0x40,
    CHRG_PUMP_75 = 0x14,
    CHRG_PUMP_85 = 0x94,
    CHRG_PUMP_90 = 0x95,
    CHRG_PUMP_OFF = 0x11,
    HORIZONTAL = 0x00,
    VERTICAL = 0x01,
    PAGE = 0x02,
    SEG_REMAP_0 = 0xA0,
    SEG_REMAP_127 = 0xA1,
    COM_OUT_SCAN_NORMAL = 0xC0,
    COM_OUT_SCAN_REMAP = 0xC8,
    COM_ALT = 0x12,
    CONTRAST_RST = 0x7F,
    CONTRAST_MAX = 0xFF,
    PRE_CHRG_RST = 0x22,
    VCOMH_65 = 0x00,
    VCOMH_71 = 0x10,
    VCOMH_77 = 0x20,
    VCOMH_83 = 0x30,
    ZERO = 0x00
};

class OLED
{
public:
    /**
     * @brief Constructor which initialize OLED display object.
     * @param width The width of the OLED display.
     * @param height The height of the OLED display.
     */
    OLED(uint8_t width, uint8_t height);
    /**
     * @brief Set a custom font set for the characters. You could also set a custom language character.
     * @param fontArray The array of fonts.
     */
    void setFont(const uint8_t (*fontArray)[5]);
    /**
     * @brief Set the font as the default font.
     */
    void clearCustomFont();
    /**
     * @brief Prints the string passed on the display at the specified X, Y coordinates.
     * @param string The string to be printed.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     */
    void print(char *string, uint8_t x, uint8_t y);
    /**
     * @brief Prints the string passed on the display at the specified X, Y coordinates with a typewriter animation.
     * @param string The string to be printed.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     * @param delay The delay between each character.
     */
    void printAnimated(char *string, uint8_t x, uint8_t y, int delay);
    /**
     * @brief Clears the screen and prints the string passed on the display at the specified X, Y coordinates.
     * @param string The string to be printed.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     */
    void print_c(char *string, uint8_t x, uint8_t y);
    /**
     * @brief Accepts a dataSet and setup the display with custom preferences.
     * @param dataSet Array of custom preferences.
     */
    void manualSetup(uint8_t *dataSet);
    /**
     * @brief Clears the OLED display.
     */
    void clearScr();
    /**
     * @brief Converts a string to dynamic char* array.
     * @param string Input string.
     * @returns Dynamic char* array of input string.
     */
    char *convertString(String string);
    /**
     * @brief Displays a progress bar.
     * @param progress Progress to be set.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     * @param style Progress bar variant [USE BETWEEN 1-15 VARIANTS].
     * @note Styles 1-10 are progress bars and 11-15 are loaders.
     */
    void progressBar(uint8_t progress, uint8_t x, uint8_t y, int style);
    /**
     * @brief Sets the display mode to off when clear screen is called.
     * @param mode Set true to turn off the display.
     */
    void turnOffOnClr(bool mode);
    /**
     * @brief Sets the brightness of the pixels in percentage.
     * @param brightness Percentage of brightness.
     */
    void setBrightness(uint8_t brightness);

private:
    uint8_t HEIGHT = 0, WIDTH = 0, charWidth = 0, step = 0, fontWidth = 5;
    const uint8_t (*fontSet)[5];
    bool IS_SETUP = false, clear = false;
    void autoSetup();
    void execute(uint8_t instruction);
    void getFont(char c);
    void sendData(uint8_t data);
    void setPosition(uint8_t x, uint8_t y);
    void offset(uint8_t dist);
};

#endif