#include <moby.h>
#include <common.h>




void CustomDrawMoby(short type, struct HudMobyInfo* info, char color)

{
  
    _ptr_HudMobyData = _ptr_HudMobyData - MOBY_SIZE;                          //set moby ptr to next moby space
    memset(_ptr_HudMobyData, 0, MOBY_SIZE);                               //clear a space of memory for the moby
    struct MobyStruct* ptr_current_moby = _ptr_HudMobyData;


    ptr_current_moby->type = type;                          //setting the moby type.

    ptr_current_moby->position.x = info->x;                 //setting the moby x position.
    ptr_current_moby->position.y = info->y;                 //setting the moby y position.
    ptr_current_moby->position.z = info->z;                 //setting the moby size 

    ptr_current_moby->color = color;                        //setting the moby's color

    ptr_current_moby->rotation.z = info->zRotation;         //setting the moby's Z Rotation
    ptr_current_moby->rotation.y += info->xRotation;        //setting the moby's X Rotation
    ptr_current_moby->rotation.x += info->yRotation;        //setting the moby's Y Rotation

    ptr_current_moby->requiredHUD1 = 0x7f;                  //UNK, required for moby
    ptr_current_moby->requiredHUD2 = 0xff;                  //UNK, required for moby

}


void MobyRender()
{
    memset(0x8006fcf4, 0, 0x900);
	_ptrTextUnk = 0;
	CopyHudToShaded();
	DrawShadedMobys();
}


