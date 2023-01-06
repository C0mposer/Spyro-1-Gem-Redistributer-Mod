#include <cd.h>

CdlCB callback;
CdlLOC loc;
int mode = 0xC8; //this translates to Double Transfer Speed (0x80) + ADPCM On (0x40) + and Subheader Filter On (0x08).
char isInitialised = 0;
char CDIsLoading = 0;


void read_cb(unsigned char status, unsigned char *result){
    CdReadCallback(callback); //for some reason this keeps the read_cb function from happening a second time
    CdIntToPos(*(&_musicSectors + 3), &loc); //takes the abslute sector numbers of the music from ram, and adds the song offset. Then, converts them into the CdlLOC format
    CdControlB(CdlReadS, (void *)&loc, 0); //Starts reading from the disk at the specified location. Must typecase void* onto CdlLOC struct pointer.
    CdControlB(CdlSetmode, &mode, 0); //puts the Cd subsystem in the right mode to play music
    // CdControlB(CdlSetmode, (void*)&(const int){0xC8}, 0); //Potential alternative to creating the variable mode and pointing to it
    isInitialised = 1; //anything in this function will only runs one time after CdRead has finished
}


void init(){
	if (!CDIsLoading && _mainMenuState == 2)
    {
        callback = CdReadCallback(read_cb); //Defines read_cb as the function to run after CdRead is completed
        CdIntToPos(265759, &loc); //Converts the absolute sector number into the CdlLOC format
        CdControlB(CdlSeekL, (void *)&loc, 0);
        CdControlB(CdlSetloc, (void *)&loc, 0); //Uses CdSetloc (0x02) to prepare for CdRead. This is required
        CdRead(4, 0x8000C000, 0x80); //Read 4 Sectors to the address 0x8000C000. 0x80 is the mode.

        CDIsLoading = 1;
    }
}

void CdMain(){
	if (!isInitialised)
        init(); //Begin the code loading process
	else
        mainFunc(); //Run the main Loop of the loaded code
}



