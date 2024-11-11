#include "oled.h"

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
            MULTIPLEX_RATIO_RST, DISP_OFFSET,
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

void OLED::print(char *string, uint8_t x, uint8_t y)
{
    step = 0;
    charWidth = 0;
    if (IS_SETUP)
    {
        execute(OLED_OFF);
        setPosition(x, y);
        offset(x);
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

void OLED::printAnimated(char *string, uint8_t x, uint8_t y, int delay)
{
    step = 0;
    charWidth = 0;
    if (IS_SETUP)
    {
        execute(OLED_OFF);
        clearScr();
        setPosition(x, y);
        offset(x);
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

void OLED::print_c(char *string, uint8_t x, uint8_t y)
{
    step = 0;
    charWidth = 0;
    if (IS_SETUP)
    {
        execute(OLED_OFF);
        clearScr();
        setPosition(x, y);
        offset(x);
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

    for (uint8_t page = 0; page < 8; page++)
    {
        Wire.beginTransmission(ADDR);
        Wire.write(0x00);
        Wire.write(0xB0 + page);
        Wire.write(0x00);
        Wire.write(0x10);
        Wire.endTransmission();

        for (uint8_t col = 0; col < 128; col++)
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
    if (c == '\n' || 128 - charWidth < fontWidth)
    {
        for (uint8_t j = 0; j < 128 - charWidth; j++)
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

void OLED::offset(uint8_t dist)
{
    for (uint8_t i = 0; i < dist; i++)
    {
        sendData(0x00);
    }
}

void OLED ::progressBar(uint8_t progress, uint8_t x, uint8_t y, int style)
{
    setPosition(x, y);
    offset(x);
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
    execute(SET_COL_ADDR);
    execute(0);
    execute(WIDTH - 1);
    execute(SET_PG_ADDR);
    execute(y < 8 ? y : 7);
    execute((HEIGHT / 8) - 1);
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