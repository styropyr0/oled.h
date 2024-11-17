#include "SSD1306.h"

/**
 * @author Saurav Sajeev
 */

static const uint8_t PROGMEM fonts[96][5] =
    {
        {0x00, 0x00, 0x00, 0x00, 0x00}, // ' '
        {0x00, 0x00, 0x5F, 0x00, 0x00}, // '!'
        {0x00, 0x07, 0x00, 0x07, 0x00}, // '"'
        {0x14, 0x7F, 0x14, 0x7F, 0x14}, // '#'
        {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // '$'
        {0x23, 0x13, 0x08, 0x64, 0x62}, // '%'
        {0x36, 0x49, 0x55, 0x22, 0x50}, // '&'
        {0x00, 0x05, 0x03, 0x00, 0x00}, // '''
        {0x00, 0x1C, 0x22, 0x41, 0x00}, // '('
        {0x00, 0x41, 0x22, 0x1C, 0x00}, // ')'
        {0x14, 0x08, 0x3E, 0x08, 0x14}, // '*'
        {0x08, 0x08, 0x3E, 0x08, 0x08}, // '+'
        {0x00, 0x50, 0x30, 0x00, 0x00}, // ','
        {0x08, 0x08, 0x08, 0x08, 0x08}, // '-'
        {0x00, 0x60, 0x60, 0x00, 0x00}, // '.'
        {0x20, 0x10, 0x08, 0x04, 0x02}, // '/'
        {0x3E, 0x51, 0x49, 0x45, 0x3E}, // '0'
        {0x00, 0x42, 0x7F, 0x40, 0x00}, // '1'
        {0x42, 0x61, 0x51, 0x49, 0x46}, // '2'
        {0x21, 0x41, 0x45, 0x4B, 0x31}, // '3'
        {0x18, 0x14, 0x12, 0x7F, 0x10}, // '4'
        {0x27, 0x45, 0x45, 0x45, 0x39}, // '5'
        {0x3C, 0x4A, 0x49, 0x49, 0x30}, // '6'
        {0x01, 0x71, 0x09, 0x05, 0x03}, // '7'
        {0x36, 0x49, 0x49, 0x49, 0x36}, // '8'
        {0x06, 0x49, 0x49, 0x29, 0x1E}, // '9'
        {0x00, 0x36, 0x36, 0x00, 0x00}, // ':'
        {0x00, 0x56, 0x36, 0x00, 0x00}, // ';'
        {0x08, 0x14, 0x22, 0x41, 0x00}, // '<'
        {0x14, 0x14, 0x14, 0x14, 0x14}, // '='
        {0x00, 0x41, 0x22, 0x14, 0x08}, // '>'
        {0x02, 0x01, 0x51, 0x09, 0x06}, // '?'
        {0x32, 0x49, 0x79, 0x41, 0x3E}, // '@'
        {0x7E, 0x11, 0x11, 0x11, 0x7E}, // 'A'
        {0x7F, 0x49, 0x49, 0x49, 0x36}, // 'B'
        {0x3E, 0x41, 0x41, 0x41, 0x22}, // 'C'
        {0x7F, 0x41, 0x41, 0x22, 0x1C}, // 'D'
        {0x7F, 0x49, 0x49, 0x49, 0x41}, // 'E'
        {0x7F, 0x09, 0x09, 0x09, 0x01}, // 'F'
        {0x3E, 0x41, 0x49, 0x49, 0x7A}, // 'G'
        {0x7F, 0x08, 0x08, 0x08, 0x7F}, // 'H'
        {0x00, 0x41, 0x7F, 0x41, 0x00}, // 'I'
        {0x20, 0x40, 0x41, 0x3F, 0x01}, // 'J'
        {0x7F, 0x08, 0x14, 0x22, 0x41}, // 'K'
        {0x7F, 0x40, 0x40, 0x40, 0x40}, // 'L'
        {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // 'M'
        {0x7F, 0x04, 0x08, 0x10, 0x7F}, // 'N'
        {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 'O'
        {0x7F, 0x09, 0x09, 0x09, 0x06}, // 'P'
        {0x3E, 0x41, 0x51, 0x21, 0x5E}, // 'Q'
        {0x7F, 0x09, 0x19, 0x29, 0x46}, // 'R'
        {0x46, 0x49, 0x49, 0x49, 0x31}, // 'S'
        {0x01, 0x01, 0x7F, 0x01, 0x01}, // 'T'
        {0x3F, 0x40, 0x40, 0x40, 0x3F}, // 'U'
        {0x1F, 0x20, 0x40, 0x20, 0x1F}, // 'V'
        {0x3F, 0x40, 0x38, 0x40, 0x3F}, // 'W'
        {0x63, 0x14, 0x08, 0x14, 0x63}, // 'X'
        {0x07, 0x08, 0x70, 0x08, 0x07}, // 'Y'
        {0x61, 0x51, 0x49, 0x45, 0x43}, // 'Z'
        {0x00, 0x7F, 0x41, 0x41, 0x00}, // '['
        {0x02, 0x04, 0x08, 0x10, 0x20}, // '\'
        {0x00, 0x41, 0x41, 0x7F, 0x00}, // ']'
        {0x04, 0x02, 0x01, 0x02, 0x04}, // '^'
        {0x40, 0x40, 0x40, 0x40, 0x40}, // '_'
        {0x00, 0x01, 0x02, 0x04, 0x00}, // '`'
        {0x20, 0x54, 0x54, 0x54, 0x78}, // 'a'
        {0x7F, 0x48, 0x44, 0x44, 0x38}, // 'b'
        {0x38, 0x44, 0x44, 0x44, 0x20}, // 'c'
        {0x38, 0x44, 0x44, 0x48, 0x7F}, // 'd'
        {0x38, 0x54, 0x54, 0x54, 0x18}, // 'e'
        {0x08, 0x7E, 0x09, 0x01, 0x02}, // 'f'
        {0x0C, 0x52, 0x52, 0x52, 0x3E}, // 'g'
        {0x7F, 0x08, 0x04, 0x04, 0x78}, // 'h'
        {0x00, 0x44, 0x7D, 0x40, 0x00}, // 'i'
        {0x20, 0x40, 0x44, 0x3D, 0x00}, // 'j'
        {0x7F, 0x10, 0x28, 0x44, 0x00}, // 'k'
        {0x00, 0x41, 0x7F, 0x40, 0x00}, // 'l'
        {0x7C, 0x04, 0x18, 0x04, 0x78}, // 'm'
        {0x7C, 0x08, 0x04, 0x04, 0x78}, // 'n'
        {0x38, 0x44, 0x44, 0x44, 0x38}, // 'o'
        {0x7C, 0x14, 0x14, 0x14, 0x08}, // 'p'
        {0x08, 0x14, 0x14, 0x18, 0x7C}, // 'q'
        {0x7C, 0x08, 0x04, 0x04, 0x08}, // 'r'
        {0x48, 0x54, 0x54, 0x54, 0x20}, // 's'
        {0x04, 0x3F, 0x44, 0x40, 0x20}, // 't'
        {0x3C, 0x40, 0x40, 0x20, 0x7C}, // 'u'
        {0x1C, 0x20, 0x40, 0x20, 0x1C}, // 'v'
        {0x3C, 0x40, 0x30, 0x40, 0x3C}, // 'w'
        {0x44, 0x28, 0x10, 0x28, 0x44}, // 'x'
        {0x0C, 0x50, 0x50, 0x50, 0x3C}, // 'y'
        {0x44, 0x64, 0x54, 0x4C, 0x44}, // 'z'
        {0x00, 0x08, 0x36, 0x41, 0x00}, // '{'
        {0x00, 0x00, 0x7F, 0x00, 0x00}, // '|'
        {0x00, 0x41, 0x36, 0x08, 0x00}, // '}'
        {0x08, 0x08, 0x2A, 0x1C, 0x08}  // '~'
};

static const uint8_t PROGMEM progressBarSet[11][6][5] =
    {
        {
            // V1
            //  empty
            {0x3E, 0x41, 0x41, 0x41, 0x41}, // start
            {0x41, 0x41, 0x41, 0x41, 0x3E}, // end
            {0x41, 0x41, 0x41, 0x41, 0x41}, // intermediate

            //  fill
            {0x3E, 0x7F, 0x7F, 0x7F, 0x7F}, // start
            {0x7F, 0x7F, 0x7F, 0x7F, 0x3E}, // end
            {0x7F, 0x7F, 0x7F, 0x7F, 0x7F}, // intermediate
        },
        {
            // V2
            //  empty
            {0x18, 0x18, 0x18, 0x18, 0x18},
            {0x18, 0x18, 0x18, 0x18, 0x18},
            {0x18, 0x18, 0x18, 0x18, 0x18},
            //  fill
            {0x3E, 0x7F, 0x7F, 0x7F, 0x7F},
            {0x7F, 0x7F, 0x7F, 0x7F, 0x3E},
            {0x7F, 0x7F, 0x7F, 0x7F, 0x7F},
        },
        {
            // V3
            //  empty
            {0x7E, 0xC3, 0xC3, 0xC3, 0xC3},
            {0xC3, 0xC3, 0xC3, 0xC3, 0x7E},
            {0xC3, 0xC3, 0xC3, 0xC3, 0xC3},
            //  fill
            {0x7E, 0xDB, 0xDB, 0xDB, 0xDB},
            {0xDB, 0xDB, 0xDB, 0xDB, 0x7E},
            {0xDB, 0xDB, 0xDB, 0xDB, 0xDB},
        },
        {
            // V4
            //  empty
            {0xFF, 0x81, 0x81, 0x81, 0x81},
            {0x81, 0x81, 0x81, 0x81, 0xFF},
            {0x81, 0x81, 0x81, 0x81, 0x81},
            //  fill
            {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
            {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
            {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        },
        {
            // V5
            //  empty
            {0x00, 0x00, 0x00, 0x00, 0x00},
            {0x00, 0x00, 0x00, 0x00, 0x00},
            {0x00, 0x00, 0x00, 0x00, 0x00},
            //  fill
            {0x1C, 0x1C, 0x1C, 0x1C, 0x1C},
            {0x1C, 0x1C, 0x1C, 0x1C, 0x1C},
            {0x1C, 0x1C, 0x1C, 0x1C, 0x1C},
        },
        {
            // V6
            //  empty
            {0x00, 0x00, 0x00, 0x00, 0x00},
            {0x00, 0x00, 0x00, 0x00, 0x00},
            {0x00, 0x00, 0x00, 0x00, 0x00},
            //  fill
            {0x10, 0x38, 0x38, 0x38, 0x38},
            {0x38, 0x38, 0x38, 0x38, 0x10},
            {0x38, 0x38, 0x38, 0x38, 0x38},
        },
        {
            // V7
            //  empty
            {0x38, 0x44, 0x44, 0x44, 0x44},
            {0x44, 0x44, 0x44, 0x44, 0x38},
            {0x44, 0x44, 0x44, 0x44, 0x44},
            //  fill
            {0x38, 0x7C, 0x7C, 0x7C, 0x7C},
            {0x7C, 0x7C, 0x7C, 0x7C, 0x38},
            {0x7C, 0x7C, 0x7C, 0x7C, 0x7C},
        },
        {
            // V8
            //  empty
            {0x00, 0x00, 0x00, 0x00, 0x00},
            {0x00, 0x00, 0x00, 0x00, 0x00},
            {0x00, 0x00, 0x00, 0x00, 0x00},
            //  fill
            {0x38, 0x7C, 0x7C, 0x7C, 0x7C},
            {0x7C, 0x7C, 0x7C, 0x7C, 0x38},
            {0x7C, 0x7C, 0x7C, 0x7C, 0x7C},
        },
        {
            // V9
            //  empty
            {0x10, 0x38, 0x38, 0x38, 0x10},
            {0x10, 0x38, 0x38, 0x38, 0x10},
            {0x10, 0x38, 0x38, 0x38, 0x10},
            //  fill
            {0x38, 0x7C, 0x7C, 0x7C, 0x38},
            {0x38, 0x7C, 0x7C, 0x7C, 0x38},
            {0x38, 0x7C, 0x7C, 0x7C, 0x38},
        },
        {
            // V10
            //  empty
            {0x38, 0x44, 0x44, 0x44, 0x38},
            {0x38, 0x44, 0x44, 0x44, 0x38},
            {0x38, 0x44, 0x44, 0x44, 0x38},
            //  fill
            {0x38, 0x7C, 0x7C, 0x7C, 0x38},
            {0x38, 0x7C, 0x7C, 0x7C, 0x38},
            {0x38, 0x7C, 0x7C, 0x7C, 0x38},
        },
        {
            // V11
            //  empty
            {0x3E, 0x7F, 0x7F, 0x7F, 0x7F},
            {0x7F, 0x7F, 0x7F, 0x7F, 0x3E},
            {0x38, 0x7C, 0x7C, 0x7C, 0x38},
            {0x3E, 0x7F, 0x7F, 0x7F, 0x3E},
            {0x7F, 0x7F, 0x7F, 0x7F, 0x7F},
            {0x7F, 0x7F, 0x7F, 0x7F, 0x3E},
        },
};

static const uint8_t PROGMEM progressBarSet1[2][20] =
    {
        {0x3E, 0x7F, 0x7F, 0x7F, 0x7F,
         0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
         0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
         0x7F, 0x7F, 0x7F, 0x7F, 0x3E},

        {0x1C, 0x3E, 0x3E, 0x3E, 0x3E,
         0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
         0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
         0x3E, 0x3E, 0x3E, 0x3E, 0x1C},
};

// static const uint8_t PROGMEM rectangleSet[][]={
//     {0xFF, 0x}
// }

OLED::OLED(uint8_t width, uint8_t height)
{
    Wire.begin();
    WIDTH = width;
    HEIGHT = height;
    autoSetup();
}

void OLED::autoSetup()
{
    uint8_t cmdList[] =
        {
            OLED_OFF, DISP_CLOCK_DIV_RATIO,
            CLK_RATIO_RST, MULTIPLEX,
            HEIGHT - 1, DISP_OFFSET,
            OFFSET_NO, START_LINE, CHRG_PUMP,
            CHRG_PUMP_75, MEM_ADDRESS_MODE,
            HORIZONTAL, SEG_REMAP_127,
            COM_OUT_SCAN_REMAP, COM_CONFIG,
            COM_ALT, CONTRAST,
            CONTRAST_MAX, PRE_CHRG,
            PRE_CHRG_RST, VCOMH_DESEL,
            VCOMH_77, TURN_ON_ALL_PIXELS,
            SET_DISP_NORMAL, OLED_ON};

    for (int i = 0; i < 25; i++)
        execute(cmdList[i]);
    IS_SETUP = true;
    setFont(fonts);
    clearScr();
}

void OLED::setFont(const uint8_t (*fontArray)[5])
{
    fontSet = fontArray;
    fontWidth = 5;
}

OLED &OLED::operator<<(const char *string)
{
    outMode = 0;
    count = 0;
    stringToPrint = string;
    return *this;
}

OLED &OLED::operator[](const uint8_t *bitmap)
{
    outMode = 1;
    count = 0;
    imgData = bitmap;
    return *this;
}

OLED &OLED::operator<<(int coordinate)
{
    if (outMode == 0)
    {
        if (count == 0)
        {
            bitmapCoords[count] = coordinate;
            count++;
        }
        else if (count == 1)
        {
            print(stringToPrint, bitmapCoords[0], coordinate);
            count = 0;
        }
    }
    else
    {
        if (count < 3)
        {
            bitmapCoords[count] = coordinate;
            count++;
        }
        else if (count == 3)
        {
            draw(imgData, bitmapCoords[0], bitmapCoords[1], bitmapCoords[2], coordinate);
            count = 0;
            outMode = 0;
        }
    }
    return *this;
}

void OLED::clearCustomFont()
{
    setFont(fonts);
    fontWidth = 5;
}

void OLED::execute(uint8_t instruction)
{
    Wire.beginTransmission(ADDR);
    Wire.write(0x00);
    Wire.write(instruction);
    Wire.endTransmission();
}

void OLED::print(const char *string, uint8_t x, uint8_t y)
{
    step = 0;
    charWidth = 0;
    if (IS_SETUP)
    {
        execute(OLED_OFF);
        setPosition(x, y);
        charWidth += x;
        while (*string)
        {
            getFont(*string++);
            if (charWidth >= 127)
                charWidth = 0;
        }
        execute(OLED_ON);
    }
}

void OLED::printAnimated(const char *string, uint8_t x, uint8_t y, int delay)
{
    step = 0;
    charWidth = 0;
    if (IS_SETUP)
    {
        execute(OLED_OFF);
        clearScr();
        setPosition(x, y);
        charWidth += x;
        while (*string)
        {
            ::delay(delay);
            getFont(*string++);
            if (charWidth >= 127)
                charWidth = 0;
        }
        execute(OLED_ON);
    }
}

char *OLED::convertString(String string)
{
    char *str = new char[string.length() + 1];
    string.toCharArray(str, string.length() + 1);
    return str;
}

void OLED::print_c(const char *string, uint8_t x, uint8_t y)
{
    step = 0;
    charWidth = 0;
    if (IS_SETUP)
    {
        execute(OLED_OFF);
        clearScr();
        setPosition(x, y);
        charWidth += x;
        while (*string)
        {
            getFont(*string++);
            if (charWidth >= 127)
                charWidth = 0;
        }
        execute(OLED_ON);
    }
}

void OLED::clearScr()
{
    if (clear == true)
        execute(OLED_OFF);

    for (uint8_t page = 0; page < HEIGHT / 8; page++)
    {
        Wire.beginTransmission(ADDR);
        Wire.write(0x00);
        Wire.write(0xB0 + page);
        Wire.write(0x00);
        Wire.write(0x10);
        Wire.endTransmission();

        for (uint8_t col = 0; col < WIDTH; col++)
            sendData(0x00);
    }
    execute(OLED_ON);
}

void OLED::turnOffOnClr(bool mode)
{
    clear = mode;
}

void OLED::getFont(char c)
{
    if (c == '\n' || WIDTH - charWidth < fontWidth)
    {
        for (uint8_t j = 0; j < WIDTH - charWidth; j++)
        {
            sendData(0x00);
        }
        if (c != '\n')
        {
            for (uint8_t i = 0; i < fontWidth; i++)
                sendData(pgm_read_byte(&fontSet[c - 32][i]));
            sendData(0x00);
            charWidth = fontWidth + 1;
            step++;
        }
        else
            charWidth = 0;
    }
    else
    {
        for (uint8_t i = 0; i < fontWidth; i++)
        {
            charWidth++;
            sendData(pgm_read_byte(&fontSet[c - 32][i]));
        }
        sendData(0x00);
        charWidth++;
    }
}

void OLED ::progressBar(uint8_t progress, uint8_t x, uint8_t y, int style)
{
    setPosition(x, y);
    progress /= 6.25;
    if (style > 15)
        style = 4;
    if (style < 11)
    {
        for (uint8_t i = 1; i <= 16; i++)
        {
            for (uint8_t j = 0; j < 5; j++)
            {
                if (i <= progress && i > 0)
                {
                    if (i == 1)
                        sendData(pgm_read_byte(&progressBarSet[style - 1][3][j]));
                    else if (i == 16)
                        sendData(pgm_read_byte(&progressBarSet[style - 1][4][j]));
                    else if (i == progress && style == 2)
                        sendData(pgm_read_byte(&progressBarSet[style - 1][4][j]));
                    else
                        sendData(pgm_read_byte(&progressBarSet[style - 1][5][j]));
                }
                else
                {
                    if (i == 1)
                        sendData(pgm_read_byte(&progressBarSet[style - 1][0][j]));
                    else if (i == 16)
                        sendData(pgm_read_byte(&progressBarSet[style - 1][1][j]));
                    else
                        sendData(pgm_read_byte(&progressBarSet[style - 1][2][j]));
                }
            }
        }
    }
    else if (style > 13)
    {
        if (progress > 12)
            progress = 12;
        for (uint8_t i = 0; i < 13; i++)
        {

            if (i == progress)
            {
                for (uint8_t j = 0; j < 20; j++)
                {
                    sendData(pgm_read_byte(&progressBarSet1[style - 14][j]));
                }
            }
            else
            {
                for (uint8_t j = 0; j < 5; j++)
                {
                    sendData(0x00);
                }
            }
        }
    }
    else
    {
        if (progress < 15)
        {
            uint8_t setVal = style - 10;
            if (style == 11)
                setVal = 0;
            for (uint8_t i = 0; i <= 16; i++)
            {
                for (uint8_t j = 0; j < 5; j++)
                {
                    if (i == progress && i < 15)
                        sendData(pgm_read_byte(&progressBarSet[10][setVal][j]));
                    else if (i == progress + 1 && i < 16 && style == 11)
                        sendData(pgm_read_byte(&progressBarSet[10][setVal + 1][j]));
                    else
                        sendData(0x00);
                }
            }
        }
    }
    delay(1);
}

void OLED::setPosition(uint8_t x, uint8_t y)
{
    execute(SET_PG_ADDR);
    execute(y < HEIGHT / 8 ? y : HEIGHT / 8 - 1);
    execute((HEIGHT / 8) - 1);
    execute(0x00 + (x % 16));
    execute(0x10 + (x / 16));
}

void OLED::sendData(uint8_t data)
{
    Wire.beginTransmission(ADDR);
    Wire.write(0x40);
    Wire.write(data);
    Wire.endTransmission();
}

void OLED::setBrightness(uint8_t brightness)
{
    execute(CONTRAST);
    execute((brightness * 255) / 100);
}

void OLED::draw(const uint8_t *dataSet, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    uint8_t vPos = y > 7 ? 7 : y;
    setPosition(x, vPos);
    for (uint8_t multiplier = 0; multiplier < height / 8; multiplier++)
    {
        charWidth = x;
        for (uint8_t row = 0; row < width / 8; row++)
        {
            for (uint8_t b = 0; b < 8; b++)
            {
                uint8_t byte = 0;
                for (uint8_t col = 0; col < 8; col++)
                    byte |= ((pgm_read_byte(&dataSet[((width / 8) * (height / 8) * multiplier) + (col * (width / 8) + row)]) & (0x80 >> b)) >> 7 - b) << col;
                sendData(byte);
                charWidth++;
                if (charWidth > 127)
                    break;
            }
            if (charWidth > 127)
                break;
        }
        vPos++;
        if (vPos > (HEIGHT / 8) - 1)
            break;
        setPosition(x, vPos);
    }
}

void OLED::setPowerMode(uint8_t mode)
{
    if (mode > 0x00 && mode < 0x04)
    {
        currentPowerMode = mode;
        switch (mode)
        {
        case PERFORMANCE_MODE:
            performancePowerMode();
            break;
        case BALANCED_MODE:
            balancedPowerMode();
            break;
        case LOW_POWER_MODE:
            lowPowerMode();
            break;
        }
    }
}

void OLED::performancePowerMode()
{
    execute(DISP_CLOCK_DIV_RATIO);
    execute(CLK_RATIO_HIGH);
    execute(CHRG_PUMP);
    execute(CHRG_PUMP_75);
    execute(PRE_CHRG);
    execute(0xF1);
    execute(VCOMH_DESEL);
    execute(VCOMH_83);
}

void OLED::balancedPowerMode()
{
    execute(DISP_CLOCK_DIV_RATIO);
    execute(CLK_RATIO_MED);
    execute(CHRG_PUMP);
    execute(CHRG_PUMP_75);
    execute(PRE_CHRG);
    execute(PRE_CHRG_RST);
    execute(VCOMH_DESEL);
    execute(VCOMH_77);
}

void OLED::lowPowerMode()
{
    execute(DISP_CLOCK_DIV_RATIO);
    execute(CLK_RATIO_LOW);
    execute(CHRG_PUMP);
    execute(CHRG_PUMP_85);
    execute(PRE_CHRG);
    execute(PRE_CHRG_RST);
    execute(VCOMH_DESEL);
    execute(VCOMH_65);
}

void OLED::superBrightness(bool mode)
{
    if (mode)
    {
        setBrightness(100);
        execute(DISP_CLOCK_DIV_RATIO);
        execute(0xF4);
        execute(CHRG_PUMP);
        execute(CHRG_PUMP_75);
        execute(PRE_CHRG);
        execute(PRE_CHRG_MAX);
        execute(VCOMH_DESEL);
        execute(VCOMH_83);
    }
    else
        setPowerMode(currentPowerMode);
}

void OLED::invertDisplay()
{
    if (!invert)
    {
        execute(INVERT);
        invert = 1;
    }
    else
    {
        execute(REVERT);
        invert = 0;
    }
}

void OLED::entireDisplayON()
{
    execute(ENTIRE_DISP_ON);
}

void OLED::entireDisplayOFF()
{
    execute(RESUME_FROM_VRAM);
}

void OLED::drawCircleQuarter(uint8_t centerX, uint8_t centerY, uint8_t radius, uint8_t corner)
{
    int x = radius, y = 0;
    int decisionOver2 = 1 - x;

    while (y <= x)
    {
        switch (corner)
        {
        case 1:
            drawPixel(centerX - x, centerY - y);
            drawPixel(centerX - y, centerY - x);
            break;
        case 2:
            drawPixel(centerX + x, centerY - y);
            drawPixel(centerX + y, centerY - x);
            break;
        case 3:
            drawPixel(centerX - x, centerY + y);
            drawPixel(centerX - y, centerY + x);
            break;
        case 4:
            drawPixel(centerX + x, centerY + y);
            drawPixel(centerX + y, centerY + x);
            break;
        }
        y++;
        if (decisionOver2 <= 0)
        {
            decisionOver2 += 2 * y + 1;
        }
        else
        {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

void OLED::rectangle(uint8_t startX, uint8_t startY, uint8_t width, uint8_t height, uint8_t cornerRadius)
{
    line(startX + cornerRadius, startY + height, startX + width - cornerRadius, startY + height);
    line(startX + cornerRadius, startY, startX + width - cornerRadius, startY);

    drawCircleQuarter(startX + cornerRadius, startY + cornerRadius, cornerRadius, 1);
    drawCircleQuarter(startX + width - cornerRadius, startY + cornerRadius, cornerRadius, 2);
    drawCircleQuarter(startX + cornerRadius, startY + height - cornerRadius, cornerRadius, 3);
    drawCircleQuarter(startX + width - cornerRadius, startY + height - cornerRadius, cornerRadius, 4);

    verticalLine(startX, startY + cornerRadius, startX, startY + height - cornerRadius);
    verticalLine(startX + width, startY + cornerRadius, startX + width, startY + height - cornerRadius);
}

void OLED::verticalLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
    if (startX > WIDTH | startY > HEIGHT)
        return;
    setPosition(startX, startY / 8);
    sendData(0xFF << startY % 8);
    for (int i = (startY / 8) + 1; i <= endY / 8; i++)
    {
        if (i > 7)
            break;
        setPosition(startX, i);
        sendData(0xFF);
    }
    if (endY < 8)
    {
        setPosition(startX, endY / 8);
        sendData(0xFF >> (7 - (endY % 8)));
    }
}

uint8_t OLED::checkXBounds(uint8_t x)
{
    uint8_t r = x < 0 ? 0 : x;
    return r >= WIDTH ? WIDTH - 1 : r;
}

uint8_t OLED::checkYBounds(uint8_t y)
{
    uint8_t r = y < 0 ? 0 : y;
    return r >= HEIGHT ? HEIGHT - 1 : r;
}

void OLED::drawPixel(uint8_t x, uint8_t y)
{
    if (x > WIDTH_128 || y > HEIGHT)
        return;
    execute(0xB0 + (y / 8));
    execute(0x00 + (x % 16));
    execute(0x10 + (x / 16));
    uint8_t pixelData = 1 << (y % 8);
    sendData(pixelData);
}

void OLED::line(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
    checkXBounds(startX);
    checkYBounds(startY);
    checkXBounds(endX);
    checkYBounds(endY);

    int dx = abs(endX - startX), sx = startX < endX ? 1 : -1;
    int dy = -abs(endY - startY), sy = startY < endY ? 1 : -1;
    int err = dx + dy, e2;

    while (true)
    {
        drawPixel(startX, startY);
        if (startX == endX && startY == endY)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            startX += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            startY += sy;
        }
    }
}

void OLED::circle(uint8_t centerX, uint8_t centerY, uint8_t radius)
{
    execute(MEM_ADDRESS_MODE);
    execute(PAGE);
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        drawPixel(centerX + x, centerY + y);
        drawPixel(centerX + y, centerY + x);
        drawPixel(centerX - y, centerY + x);
        drawPixel(centerX - x, centerY + y);
        drawPixel(centerX - x, centerY - y);
        drawPixel(centerX - y, centerY - x);
        drawPixel(centerX + y, centerY - x);
        drawPixel(centerX + x, centerY - y);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
    execute(MEM_ADDRESS_MODE);
    execute(HORIZONTAL);
}
