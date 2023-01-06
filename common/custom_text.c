#include <custom_text.h>
#include <custom_types.h>
#include <common.h>
#include <moby.h>


void ConvertToUpperCase(char* s) 
{ 
    int i = 0; 
  
    while (s[i] != '\0') { 
        if (s[i] >= 'a' && s[i] <= 'z') { 
            s[i] = s[i] - 'a' + 'A'; 
        } 
        i++; 
    } 
}

int TextLengthInUnits(char* str, char spacing)
{
	short lengthInUnits = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		lengthInUnits += spacing;
	}

	return lengthInUnits - spacing + fixedLastCharacterOffset;              //Subtract the last character's spacing from the total length
                                                                            //So that the last character is not drawn too far to the left
}                                                                           //then add the fixed last character offset to make it draw 
                                                                            //in the right place                           


void EasyDrawText(char *text, char* position, char color)
{
    return CustomDrawText(text, position, DEFAULT_SPACING, DEFAULT_SIZE, DEFAULT_ROW, color);
}

void CustomDrawText(char *text, char* position, char spacing, int size, char row, char color)
{

	char textX = 0xa;
	char textY = 0x11;
	char textSpacing = spacing;
    int textLength = TextLengthInUnits(text, spacing);

    if(row)
    {
        row = row * 0x10 - 0x10;
    }
    else
    {
        row = 0;
    }

    struct CapitalTextInfo textDefault =
    {
        .x = 0xA,
        .y = 0x11,
        .size = size
    };

    if (position == TOP_LEFT) {
        
        textDefault.x = TEXT_SCREEN_LEFT_EDGE;
        textDefault.y = TEXT_SCREEN_TOP_EDGE + row;
        
    }
    
    else if (position == TOP_RIGHT) {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE - textLength;
        textDefault.y = TEXT_SCREEN_TOP_EDGE + row;
        
    }
    
    else if (position == BOTTOM_LEFT) {
        
        textDefault.x = TEXT_SCREEN_LEFT_EDGE;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE;
        
    }
    
    else if (position == BOTTOM_RIGHT) {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE - textLength;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE;
        
    }
    
    else if (position == MIDDLE_LEFT) {
        
        textDefault.x = TEXT_SCREEN_LEFT_EDGE;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE/2 + row;
        
    }
    
    else if (position == MIDDLE_RIGHT) {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE - textLength;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE/2 + row;
        
    }
    
    else if (position == MIDDLE) {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE/2 - textLength/2;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE/2 + row;
        
    }

    else if (position == MIDDLE_TOP)
    {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE/2 - textLength/2;
        textDefault.y = TEXT_SCREEN_TOP_EDGE + row;
        
    }

    else if (position == MIDDLE_BOTTOM)
    {  
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE/2 - textLength/2;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE;
      
    }
    
    else 
    {       
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE/2 - textLength/2;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE/2;
    }
	
    ConvertToUpperCase(text);
    DrawTextCapitals(text, &textDefault, spacing, color);
}











//DrawTextAll Equivalent for CustomDrawText


/*

void CustomDrawTextAll(char *text, char* position, char spacing, int size, char row, char color)
{
    char textX = 0xa;
    char textY = 0x11;
    char textSpacing = spacing;
    int textLength = TextLengthInUnits(text, spacing);

    if(row)
    {
        row = row * 0x10 - 0x10;
    }
    else
    {
        row = 0;
    }

    struct CapitalTextInfo textDefault =
    {
        .x = 0xA,
        .y = 0x11,
        .capitalSize = size
    };

    struct LowercaseTextInfo lowercaseTextDefault =
    {
        .spacing = spacing,
        .yOffset = 0x1,
        .size = 0x1400
    };


    if (position == "TOP LEFT") {
        
        textDefault.x = TEXT_SCREEN_LEFT_EDGE;
        textDefault.y = TEXT_SCREEN_TOP_EDGE + row;
        
    }
    
    else if (position == "TOP RIGHT") {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE - textLength;
        textDefault.y = TEXT_SCREEN_TOP_EDGE + row;
        
    }
    
    else if (position == "BOTTOM LEFT") {
        
        textDefault.x = TEXT_SCREEN_LEFT_EDGE;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE;
        
    }
    
    else if (position == "BOTTOM RIGHT") {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE - textLength;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE;
        
    }
    
    else if (position == "MIDDLE LEFT") {
        
        textDefault.x = TEXT_SCREEN_LEFT_EDGE;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE/2 + row;
        
    }
    
    else if (position == "MIDDLE RIGHT") {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE - textLength;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE/2 + row;
        
    }
    
    else if (position == "MIDDLE") {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE/2 - textLength/2;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE/2 + row;
        
    }

    else if (position == "MIDDLE TOP" || position == "TOP MIDDLE" || position == "TOP")
     {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE/2 - textLength/2;
        textDefault.y = TEXT_SCREEN_TOP_EDGE + row;
        
    }

    else if (position == "MIDDLE BOTTOM" || position == "BOTTOM MIDDLE" || position == "BOTTOM")
     {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE/2 - textLength/2;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE;
        
    }
    
    else {
        
        textDefault.x = TEXT_SCREEN_RIGHT_EDGE/2 - textLength/2;
        textDefault.y = TEXT_SCREEN_BOTTOM_EDGE/2;
        
    }

    

    
    ConvertToUpperCase(text);
    DrawTextAll(text, &textDefault, &lowercaseTextDefault, spacing, color);

}


*/



    //check if the text is too long to fit on the screen

    /*
    if(textLength > (TEXT_SCREEN_RIGHT_EDGE - TEXT_SCREEN_LEFT_EDGE))
    {
        printf("Text is too long to fit on the screen\n");
        return;
    }
    */







