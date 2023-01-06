#ifndef MOBY_H
#define MOBY_H

#include <common.h>

//~~~~~~~~~
//Constants
//~~~~~~~~~
#define MOBY_SIZE 0x58

#define ARROW_RIGHT 0
#define ARROW_LEFT 1

enum HudMobyTypes
{
    WATERFALL_PARTICLE_SPAWNER_MOBY_ID = 0xB,
    LIFE_FIGURINE_MOBY_ID = 0xE,
    EGG_MOBY_ID = 0x22,
    SPYRO_HEAD_MOBY_ID = 0x3A,
    EXCAILMATION_MOBY_ID = 0x4B,
    COMMA_MOBY_ID = 0x4C,
    KEY_MOBY_ID = 0xAD,
    DRAGON_FIGURINE_MOBY_ID = 0x1FA,
    GEM_CHEST_MOBY_ID = 0x1D7,
    GEM_CHEST_2_MOBY_ID = 0x1D9,
    VOLUME_BAR_MOBY_ID = 0x1B2,

    ONE_GEM_MOBY_ID = 0x53,
    TWO_GEM_MOBY_ID = 0x54,
    FIVE_GEM_MOBY_ID = 0x55,
    TEN_GEM_MOBY_ID = 0x56,
    TWENTYFIVE_GEM_MOBY_ID = 0x57


};

enum FullMobyTypes
{
    DRAGON_MOBY_ID = 0xFA,
    CHEST_MOBY_ID = 0xC2,

    ARTISANS_GNORC = 0x72


};

enum MobyHeldValues
{
    ORB_HELD_ID = 0xFF,
    LIFE_HELD_ID = 0xE,
    BUTTERFLY_HELD_ID = 0x10,
    ONE_GEM_HELD_ID = 0x53,
    TWO_GEM_HELD_ID = 0x54,
    FIVE_GEM_HELD_ID = 0x55,
    TEN_GEM_HELD_ID = 0x56,
    TWENTYFIVE_GEM_HELD_ID = 0x57

};

enum MobyColors
{
    MOBY_TRANSPARENT = 0x00,
    MOBY_WHITE = 0x01,
    MOBY_BLACK = 0x06,
    MOBY_MATTE_GREY = 0x07,
    MOBY_EMERALD_GREEN = 0x09,
    MOBY_BLUE = 0x0A,
    MOBY_GOLD = 0x0B,
    MOBY_GREY = 0x0C,
    MOBY_RED = 0x0D,
    MOBY_GREEN = 0x0E,
    MOBY_PURPLE = 0x17,
    MOBY_NEON_YELLOW = 0x18,
    MOBY_CHEESE_YELLOW = 0x19,
    MOBY_DARK_RED = 0x1F,
    MOBY_NEON_RED = 0x20,
    MOBY_DARK_GREEN = 0x21,
    MOBY_NEON_GREEN = 0x22,
    MOBY_NEON_BLUE = 0x24,
    MOBY_DARK_GOLD = 0x25,
    MOBY_DARK_PURPLE = 0x27,
    MOBY_NEON_PURPLE = 0x28,
    MOBY_SHINY_RED = 0x29,
    MOBY_SHINY_GREEN = 0x2A,
    MOBY_SHINY_BLUE = 0x2B,
    MOBY_SHINY_GOLD = 0x2C,
    MOBY_SHINY_PURPLE = 0x2D,
    MOBY_SILVER = 0x2E,
    MOBY_MATTE_RED = 0x30,
    MOBY_SKY_BLUE = 0x39,
    MOBY_CYAN = 0x7E,
    MOBY_PINK = 0xA5,
    MOBY_INDIGO = 0xA6,
    MOBY_MATTE_GREEN = 0xAC,
    MOBY_NEON_LIME = 0xAD,
    MOBY_BRIGHT_BLUE = 0xB1,
    MOBY_VIOLET = 0xB2,
    MOBY_BRIGHT_RED = 0xB3

};

enum GemColors
{
    GEM_RED = 0x01,
    GEM_GREEN = 0x02,
    GEM_BLUE = 0x03,
    GEM_YELLOW = 0x04,
    GEM_PINK = 0x05,

    GEM_BLACK = 0x00,
    GEM_WHITE = 0x7c,
    GEM_BROWN = 0x31,
    GEM_ORANGE = 0x76,
    GEM_PURPLE = 0x36,
    GEM_MAGENTA = 0xA4,
    GEM_VIOLET = 0x8D,
    GEM_TURQUOISE = 0x3C,
    GEM_SUNSET = 0x35,
    GEM_BRONZE = 0x3B,
    GEM_SILVER = 0x13,
    GEM_GOLD = 0x78,
    GEM_BLUE_PURPLE = 0x36,
    GEM_DARK_PURPLE = 0x3A,
    GEM_SKY_BLUE = 0x37,
    GEM_LIGHT_PINK = 0xAE,
    GEM_NEON_PINK = 0x40,
    GEM_NEON_GREEN = 0x42,
    GEM_WINE_RED = 0x0B,
    GEM_CAMO_GREEN = 0x70,
    GEM_LIME_GREEN = 0x74,
    GEM_EMERALD_GREEN = 0xF6,
    GEM_TAN_YELLOW = 0xAC,
    GEM_BRIGHT_YELLOW = 0xFE
};


//~~~~~~~
//Structs
//~~~~~~~
struct HudMobyInfo
{
    int x;                                  
    int y;                                  
    int z;                                         //Effective size in HUD.

    unsigned char zRotation;                                  
    unsigned char xRotation;                                  
    unsigned char yRotation;                               

};


// ~~~ FULL MOBY STRUCT ~~~

//Struct for all Moby's
typedef struct MobyStruct
{
    struct ArtisansGnorc *ptr_mobyData;

    int empty1;
    int empty2;

    struct Vec3 position;

    short UNK1;
    short interactState;                          //0 for alive, 1 for flamed, 2 for charged. 

    int UNK2;
    int UNK3;
    int UNK4;
    int UNK5;
    int UNK6;
    int UNK7;

    short subType;                                  // Research this more
    short type;                                     // Determines what type of moby it is

    short UNK10;
    char canDropObject;                             //7D and lower yes, 80 and higher no
    char UNK21;


    char currentAnimation;                          //Should use next animation for setting animations.
    char nextAnimation;                             
    char currentKeyFrame;
    char nextKeyFrame;

    char speedRelated;
    char animationSpeed;


    char UNK13;
    char active;                                    //FF for yes, 0 for no

    struct u8Vec3 rotation;

    char requiredHUD1;

    unsigned char state;                            // 00 still active, FD picked up. Had to make unsinged because, apparently its negative, so I have to force it to be positive.

    union
    {
        char howPickedUp;                               // 01 picked up by spyro, 03 picked up by sparx
        char subState;                             
    };

    char visable;                                   // FF visable, any other value not

    char UNK_shadowRelated;                         // 1-10 only shadow appears?

    struct MobyRGB RGB;

    char color;                                      // Determines the color of the moby. (01 red, 02 green, etc.) This can be poked outside of its normal range to get some awesome colors.

    short requiredHUD2;

    char UNK19;

    char heldValue;

    short UNK20;

    short scale;                                    // Determines the scale of the gem. Range from 0x0000 - 0xFFFF. (0 normal sized, 0xFFFF smallest size)

}MobyStruct;




#endif // MOBY_H