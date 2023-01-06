#ifndef CUSTOMTEXT_H
#define CUSTOMTEXT_H


//~~~~~~~~~
//Functions
//~~~~~~~~~
int TextLengthInUnits(char* str, char spacing);
void EasyDrawText(char *text, char* position, char color);
void CustomDrawText(char *text, char* position, char spacing, int size, char row, char color);


//~~~~~~~~~
//Constants
//~~~~~~~~~
#define TEXT_SCREEN_LEFT_EDGE 0xA
#define TEXT_SCREEN_RIGHT_EDGE 0x207
#define TEXT_SCREEN_TOP_EDGE 0x11
#define TEXT_SCREEN_BOTTOM_EDGE 0xE0

#define DEFAULT_SPACING 0x12
#define DEFAULT_SIZE 0x1100
#define DEFAULT_ROW 0x0

#define MIN_TEXTBOX_WIDTH 0x0
#define MIN_TEXTBOX_HEIGHT 0x08

#define MAX_TEXTBOX_WIDTH 0x200
#define MAX_TEXTBOX_HEIGHT 0xE0

#define fixedLastCharacterOffset 0x10;

enum CustomTextPositionFlags
{
    TOP_LEFT = 0x00,
    TOP_MIDDLE = 0x01,
    MIDDLE_TOP = 0x01,
    TOP = 0x01,
    TOP_RIGHT = 0x02,
    MIDDLE_LEFT = 0x03,
    MIDDLE = 0x04,
    MIDDLE_RIGHT = 0x05,
    BOTTOM_LEFT = 0x06,
    BOTTOM_MIDDLE = 0x07,
    MIDDLE_BOTTOM = 0x07,
    BOTTOM = 0x07,
    BOTTOM_RIGHT = 0x08,
};

enum Rows
{
    ROW1 = 0x1,
    ROW2 = 0x2,
    ROW3 = 0x3,
    ROW4 = 0x4,
    ROW5 = 0x5,
    ROW6 = 0x6,
    ROW7 = 0x7,
    ROW8 = 0x8,
    ROW9 = 0x9,
    ROW10 = 0xA,
    ROW11 = 0xB,
    ROW12 = 0xC,
    ROW13 = 0xD,
    ROW14 = 0xE,
    ROW15 = 0xF,
    ROW16 = 0x10
};


//~~~~~~~
//Structs
//~~~~~~~
struct CapitalTextInfo
{
    int x;                                  
    int y;                                  
    int size;                                        //Higher number, smaller size

};


struct LowercaseTextInfo
{
    int spacing;
    int yOffset;
    int size;                                        //Higher number, smaller size
};

#endif // CUSTOMTEXT_H