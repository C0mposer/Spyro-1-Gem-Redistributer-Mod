#include <customtypes.h>
#include <common.h>
#include <spyro.h>
#include <moby.h>
#include <my_math.h>
#include <sound.h>
#include <filters.h>
#include <custom_text.h>


//* ~~~ Global Flags ~~~

bool hasParsedLevelGemData = FALSE;
bool hasReplacedLevelGems = FALSE;
bool hasReplacedLevelGemsAfterDeathAndEntry = TRUE;
bool hasSelectedSeed = FALSE;
bool hasSeedChanged = FALSE;
bool hasRanFirstSeed = FALSE;
bool shouldPlayCutscene = FALSE;
bool canReplaceAfterEntry = TRUE;


//* ~~~ Global Variables ~~~

int customTimer = 0;
unsigned short chosenSeed = 0;

char amountOfRedGems = 0;
char amountOfGreenGems = 0;
char amountOfBlueGems = 0;
char amountOfYellowGems = 0;
char amountOfPinkGems = 0;
int totalAmountOfPhysicalGems = 0;
int amountOfGemMobys = 0;
int amountOfHeldGems = 0;

int amountOfMobysInLevel;

struct MobyStruct* currentStruct;

Spyro* spyro = &spyroX;

char valuesForAfterDeathAndEntry[600] = {0};
int counterForThis;

//* ~~~ Functions ~~~

//* Function for menu to select/randomize seed
void SelectSeed()
{
    //*If hasn't selected seed yet, and is in artisans
    if(gameState == GAMESTATE_GAMEPLAY && levelID == ARTISANS_ID && !hasSelectedSeed)
    {
        spyro->canInput = 30;

        DrawTextBox(0x4c, 0x1a9, 0x40, 0xA8);

        char buffer[10] = {0};

        sprintf(buffer, "SEED %d", chosenSeed);

        CustomDrawText(buffer, TOP, DEFAULT_SPACING, DEFAULT_SIZE, 5, MOBY_GOLD);

        CustomDrawText("SQUARE TO RANDOMIZE", TOP, DEFAULT_SPACING, DEFAULT_SIZE, 7, MOBY_PURPLE);

        CustomDrawText("X TO SELECT", MIDDLE, DEFAULT_SPACING, DEFAULT_SIZE, 3, MOBY_BLUE);


        //Decrement One Option
        if(currentButtonOneFrame == LEFT_BUTTON && chosenSeed != 0)
        {
            chosenSeed--;
        }

        //Decrement fast after 1 and a half second, then faster after 5 seconds
        if(currentButton == LEFT_BUTTON && chosenSeed > 0)
        {
            //Reset timer
            if(currentButtonOneFrame == LEFT_BUTTON)
            {
                customTimer = 0;
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);
            }

            //Faster Setting
            if(customTimer > 3*SECONDS)
            {
                chosenSeed = chosenSeed - 61;
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);
            }

            //Slower Setting
            else if(customTimer > 1*SECONDS)
            {
                chosenSeed--;
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);
            }
                
        }

        //Increment One Option
        if(currentButtonOneFrame == RIGHT_BUTTON && chosenSeed < 0xFFFF)
        {
            chosenSeed++;
        }

        //Increment fast after 1 and a half second, then faster after 5 seconds
        if(currentButton == RIGHT_BUTTON)
        {
            //Reset timer
            if(currentButtonOneFrame == RIGHT_BUTTON)
            {
                customTimer = 0;
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);
            }
            
            //Faster Setting
            if(customTimer > 5*SECONDS)
            {
                chosenSeed = chosenSeed + 61;
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);
            }

            //Slower Setting
            else if(customTimer > 1*SECONDS)
            {
                chosenSeed++;
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);
            }
                
        }

        if(currentButton == LEFT_BUTTON || currentButton == RIGHT_BUTTON || currentButton == SQUARE_BUTTON)
        {
            hasSeedChanged = TRUE;
        }
        else if(currentButton == 0)
        {
            hasSeedChanged = FALSE;
        }

        //Randomize Seed
        if(currentButton == SQUARE_BUTTON)
        {
            chosenSeed = rand() % 0xFFFF;
            PlaySoundEffect(SOUND_EFFECT_LIFE_CHEST_BLINK, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);
        }

        //Close menu and set selected seed
        if(currentButton == X_BUTTON)
        {
            hasSelectedSeed = TRUE;
            PlaySoundEffect(SOUND_EFFECT_DRAGON_DISAPEAR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);
            
            shouldPlayCutscene = TRUE;

            //spyro->canInput = 0;
        }

        MobyRender();
    }
}

//*Returns a random gem offset between 0-4 to add to the default gem value red (0x53), and then applys to a gem. 
//*Takes into consideration the previously parsed data to ensure the same amount of each type of gem exists in each level.
char ReturnRandomGemOffset() 
{
    bool hasFoundAvailbleGem = FALSE;
    char gemValueOffset;            //Value to add to the initial gem value.
    while(!hasFoundAvailbleGem)
    {
        char fiveSidedDice = rand() % 5; //Set random number between 0-4. This represets each possible gem type. Red-Pink.

        //This code below checks the value of the fiveSidedDice, and also checks of its equivilent "amountOf____Gems" value  has any gems left to redistrubute. 
        //If not, it re-rolls. If it does, it decreases the amount of specific gem type left to distrubted, and returns the offset from the dice.
        if(amountOfRedGems && fiveSidedDice == 0)
        {
            amountOfRedGems--;
            hasFoundAvailbleGem = TRUE;
        }

        if(amountOfGreenGems && fiveSidedDice == 1)
        {
            amountOfGreenGems--;
            hasFoundAvailbleGem = TRUE;
        }

        if(amountOfBlueGems && fiveSidedDice == 2)
        {
            amountOfBlueGems--;
            hasFoundAvailbleGem = TRUE;
        }

        if(amountOfYellowGems && fiveSidedDice == 3)
        {
            amountOfYellowGems--;
            hasFoundAvailbleGem = TRUE;
        }

        if(amountOfPinkGems && fiveSidedDice == 4)
        {
            amountOfPinkGems--;
            hasFoundAvailbleGem = TRUE;

        }

        if(hasFoundAvailbleGem)
        {
            gemValueOffset = fiveSidedDice;
            return gemValueOffset;
        }
    }
}

void ParseGemData(void)
{
    //* ~~~ PARSE GEM DATA ~~~
    if(!hasParsedLevelGemData)
    {
        amountOfMobysInLevel = (*(ptr_levelMobys - 2) / MOBY_SIZE); //?? ptr_levelMobys - 2 representing the address for number of bytes that the moby region for the level is taking up.

        //*Itterate through all the mobys in a level
        for (int i = 1; i <= amountOfMobysInLevel; i++) //?? Starting at one to avoid multiplying by 0. This is also why we have to do <= instead of just < like normal
        {
            currentStruct = ptr_levelMobys + (MOBY_SIZE/sizeof(int) * i);


            //*Check if the current moby's type is any gem value (0x53-0x57). If it is, add to the total for that specific gem type.
            if(currentStruct->type >=ONE_GEM_MOBY_ID && currentStruct->type <=TWENTYFIVE_GEM_MOBY_ID)
            {
                totalAmountOfPhysicalGems++;
                amountOfGemMobys++;

                valuesForAfterDeathAndEntry[counterForThis] = currentStruct->type;
                counterForThis++;

                if(currentStruct->type == ONE_GEM_MOBY_ID)
                {
                    amountOfRedGems++;
                }
      
                if(currentStruct->type == TWO_GEM_MOBY_ID)
                {
                    amountOfGreenGems++;
                }
               
                if(currentStruct->type == FIVE_GEM_MOBY_ID)
                {
                    amountOfBlueGems++;
                }
               
                if(currentStruct->type == TEN_GEM_MOBY_ID)
                {
                    amountOfYellowGems++;
                }

                if(currentStruct->type == TWENTYFIVE_GEM_MOBY_ID)
                {
                    amountOfPinkGems++;
                }
            }
            
            //*Check if the current moby's held value is any gem value (0x53-0x57). If it is, add to the total for that specific gem type.
            if(currentStruct->heldValue >= ONE_GEM_HELD_ID && currentStruct->heldValue <= TWENTYFIVE_GEM_HELD_ID)
            {
                totalAmountOfPhysicalGems++;
                amountOfHeldGems++;

                valuesForAfterDeathAndEntry[counterForThis] = currentStruct->heldValue;
                counterForThis++;

               if(currentStruct->heldValue == ONE_GEM_HELD_ID)
                {
                    amountOfRedGems++;
                }

                if(currentStruct->heldValue == TWO_GEM_HELD_ID)
                {
                    amountOfGreenGems++;
                }
  
                if(currentStruct->heldValue == FIVE_GEM_HELD_ID)
                {
                    amountOfBlueGems++;
                }
                
                if(currentStruct->heldValue == TEN_GEM_HELD_ID)
                {
                    amountOfYellowGems++;
                }

                if(currentStruct->heldValue == TWENTYFIVE_GEM_HELD_ID)
                {
                    amountOfPinkGems++;
                }
            }
        }
        printf("Amount of Total Physical Gems: %D\n\nAmount of Gem Mobys: %D\n\nAmount of Held Gems: %D\n\nAmount of One Gems: %D\nAmount of Two Gems: %D\nAmount of Five Gems: %D\nAmount of Ten Gems: %D\nAmount of Twenty Five Gems: %D\n\n", totalAmountOfPhysicalGems, amountOfGemMobys, amountOfHeldGems, amountOfRedGems, amountOfGreenGems, amountOfBlueGems, amountOfYellowGems, amountOfPinkGems); 
        amountOfGemMobys = 0;
        amountOfHeldGems = 0;
        totalAmountOfPhysicalGems = 0; //?? Pretty sure all of these are used for the printf and nothing else?

        hasParsedLevelGemData = TRUE;
    }

}

void ReplaceGemData(void)
{
    // ~~~ REPLACE GEM DATA ~~~
    if(hasParsedLevelGemData && !hasReplacedLevelGems && hasReplacedLevelGemsAfterDeathAndEntry)
    {
        amountOfMobysInLevel = (*(ptr_levelMobys - 2) / MOBY_SIZE); //?? ptr_levelMobys - 2 representing the address for number of bytes that the moby region for the level is taking up.

            srand(chosenSeed);
 


        for (int i = 1; i < amountOfMobysInLevel; i++)
        {
            currentStruct = ptr_levelMobys + (MOBY_SIZE/sizeof(int) * i);
            //printf("Current Moby: %X\n", currentStruct);
   
            if(currentStruct->type >=ONE_GEM_MOBY_ID && currentStruct->type <=TWENTYFIVE_GEM_MOBY_ID)
            {
                char gemOffest = ReturnRandomGemOffset();
                currentStruct->type = ONE_GEM_HELD_ID + gemOffest;
                currentStruct->color = GEM_RED + gemOffest;
            }

            if(currentStruct->heldValue >=ONE_GEM_MOBY_ID && currentStruct->heldValue <=TWENTYFIVE_GEM_MOBY_ID)
            {
                char gemOffest = ReturnRandomGemOffset();
                currentStruct->heldValue = ONE_GEM_HELD_ID + gemOffest;
            }
        }
        printf("~~~ TEST TO SEE IF REPLACED ALL ~~~\nOne Gems Left to Replace: %D\nTwo Gems Left to Replace: %D\nFive Gems Left to Replace: %D\nTen Gems Left to Replace: %D\nTwenty Five Gems Left to Replace: %D\n", amountOfRedGems, amountOfGreenGems, amountOfBlueGems, amountOfYellowGems, amountOfPinkGems); 

        counterForThis = 0;
        hasReplacedLevelGems = TRUE;
    }
}


void ReplaceGemDataAfterDeathAndEntry(void)
{
    // ~~~ REPLACE GEM DATA ~~~
    if(hasParsedLevelGemData && !hasReplacedLevelGemsAfterDeathAndEntry && hasReplacedLevelGems)
    {
        amountOfMobysInLevel = (*(ptr_levelMobys - 2) / MOBY_SIZE); //?? ptr_levelMobys - 2 representing the address for number of bytes that the moby region for the level is taking up.

        counterForThis = 0;

        for (int i = 1; i < amountOfMobysInLevel; i++)
        {
            currentStruct = ptr_levelMobys + (MOBY_SIZE/sizeof(int) * i);
            //printf("Current Moby: %X\n", currentStruct);
   
            if(currentStruct->type >=ONE_GEM_MOBY_ID && currentStruct->type <=TWENTYFIVE_GEM_MOBY_ID)
            {
                currentStruct->type = valuesForAfterDeathAndEntry[counterForThis];
                //currentStruct->color = valuesForAfterDeathAndEntry[counterForThis] -0x52;
                counterForThis++;
            }

            if((currentStruct->heldValue >=ONE_GEM_MOBY_ID && currentStruct->heldValue <=TWENTYFIVE_GEM_MOBY_ID) || currentStruct->heldValue == ORB_HELD_ID)
            {
                currentStruct->heldValue = valuesForAfterDeathAndEntry[counterForThis];
                counterForThis++;
            }
        }
        printf("~~~ TEST TO SEE IF REPLACED ALL AFTER DEATH ~~~"); 

        counterForThis = 0;
        hasReplacedLevelGemsAfterDeathAndEntry = TRUE;
    }
}



void mainFunc()
{
    SelectSeed();  
    if(shouldPlayCutscene)
        PlayCustomCutscene();
    ParseGemData();     
    ReplaceGemData();   
    ReplaceGemDataAfterDeathAndEntry();   

    //*Button combo for easy reset
    if(currentButton == L1_BUTTON + L2_BUTTON + R1_BUTTON + R2_BUTTON + TRIANGLE_BUTTON)
    {
        hasSelectedSeed = FALSE;
        chosenSeed = 0;
        TheAdventureBegins();
    }
    
    //*~~~ UPDATES ~~~

    customTimer++;

    //*If its the first seed, allow the first pass through of checking/setting gems.
    if(!hasRanFirstSeed)
    {
        hasParsedLevelGemData = FALSE;
        hasReplacedLevelGems = FALSE;

        hasRanFirstSeed = TRUE;
    }
    //!This is the main flag that checks when to do another run through of checking/setting gems
    //*If seed has changed, allow another pass through of checking/setting gems. 
    if(hasSeedChanged)
    {
        hasParsedLevelGemData = FALSE;
        hasReplacedLevelGems = FALSE;
    }

    //*Level Entry/Exit/Balloonist/Death Resets:

    //?? This code allows the main code to run once again by setting the 2 main flags to false in the next if below.
    if(canReplaceAfterEntry && (glideSubState == 0x9 || glideSubState == 0xA || glideSubState == 0xB || ballonistState == 0x6 || (spyro->canInput != 0 && screenFadeIn != 0)))
    {
        hasParsedLevelGemData = FALSE;
        hasReplacedLevelGemsAfterDeathAndEntry = FALSE;

        canReplaceAfterEntry = FALSE;
    }
    //If has landed from fly in/exit, allow reset to happen again next fly in/exit
    else if(glideSubState != 0x9 && glideSubState != 0xA && glideSubState != 0xB && gameState != GAMESTATE_BALLOONIST && (spyro->canInput == 0 && screenFadeIn == 0))
    {
        canReplaceAfterEntry = TRUE;
    }

}
