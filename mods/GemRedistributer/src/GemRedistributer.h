#ifndef GEMREDISTRIBUTER_H
#define GEMREDISTRIBUTER_H

#include <custom_types.h>

//* ~~~ Structs ~~~

typedef struct AmountOfGems
{
    int redGems;
    int greenGems;
    int blueGems;
    int yellowGems;
    int pinkGems;
}AmountOfGems;

//* ~~~ Global Flags ~~~

bool hasParsedLevelGemData = FALSE;     //? This is the flag that determines if ParseLevelGemData can run.
bool hasReplacedLevelGems = FALSE;      //? This is the flag that determines if ReplaceLevelGemData can run.
bool hasSelectedSeed = FALSE;           //? This is the flag that determines if SelectSeed can run.
bool hasSeedChanged = FALSE;            //? This flag determines if the seed has changed or not. If it has, it sets the main 2 function flags to be false to allow them to run again.
bool hasRanFirstSeed = FALSE;           //? This flag determines if used to run the code once when you load in with seed 0, since it will have never been "changed"
bool shouldPlayCutscene = FALSE;        //? This flag determines if PlayCustomCutscene can run.
bool hasReplacedAfterEntry = FALSE;     //? This flag determines if the required flags have been set after dying/re-entering a level. Is used to make sure the code runs once afterwards.

//* ~~~ Global Variables ~~~

short chosenSeed = 0;                   //? This is the players chosen seed.

AmountOfGems amountOfGems = {0};

//int totalAmountOfPhysicalGems = 0;    //? This is the total amount of physical gems found in a level. This includes gems on the ground and in enemies/boxes.
//int amountOfGemMobys = 0;             //? This is the total amount of gem mobys. This is only gems on the ground.
//int amountOfHeldGems = 0;             //? This is the totla amount of moby's that hold gems.

#endif /* GEMREDISTRIBUTER_H */
