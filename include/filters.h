#ifndef FILTERS_H
#define FILTERS_H

#include <common.h>

//~~~~~~~~~
//Constants
//~~~~~~~~~
enum DrawOpaqueShapeColorSpaces
{
    RGB_DARK = 0x00,
    RGB = 0x20,
    CMY = 0x40
};




//~~~~~~~
//Structs
//~~~~~~~
struct OpaqueShapeInfo

{
    int PADDING1;
    int PADDING2;
    int PADDING3;
    
    int required1;

    char red;
    char green;
    char blue;

    char required2;

    struct u16Vec2 point1Pos;
    struct u16Vec2 point2Pos;
    struct u16Vec2 point3Pos;
    struct u16Vec2 point4Pos;


};

void CustomDrawOpaqueShape(struct OpaqueShapeInfo customInfo);

#endif //FILTERS_H