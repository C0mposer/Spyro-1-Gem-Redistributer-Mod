#include <custom_types.h>
#include <common.h>
#include <spyro.h>
#include <moby.h>
#include <my_math.h>
#include <sound.h>
#include <filters.h>
#include <custom_text.h>


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

char amountOfRedGems = 0;               //? This is the amount of red gems found in a level. This will be used for the redistribution.
char amountOfGreenGems = 0;             //? This is the amount of green gems found in a level. This will be used for the redistribution.
char amountOfBlueGems = 0;              //? This is the amount of blue gems found in a level. This will be used for the redistribution.
char amountOfYellowGems = 0;            //? This is the amount of yellow gems found in a level. This will be used for the redistribution.
char amountOfPinkGems = 0;              //? This is the amount of pink gems found in a level. This will be used for the redistribution.

int totalAmountOfPhysicalGems = 0;      //? This is the total amount of physical gems found in a level. This includes gems on the ground and in enemies/boxes.
int amountOfGemMobys = 0;               //? This is the total amount of gem mobys. This is only gems on the ground.
int amountOfHeldGems = 0;               //? This is the totla amount of moby's that hold gems.

//* ~~~ Functions ~~~

//* Function for menu to select/randomize seed
void SelectSeed()
{
        static int customMenuTimer = 0;                                                                         //? This is my custom timer for the seeding menu. Used for seeing how long you have held buttons for for quick incrementing/decrementing

        _spyro.canInput = SPYRO_CANT_INPUT;                                                                     //? Set's spyro to not be allowed to move while the seed menu is up

        DrawTextBox(0x4c, 0x1a9, 0x40, 0xA8);                                                                   //? Draw the Textbox

        char buffer[10] = {0};                                                                                  //? Buffer for sprintf
        sprintf(buffer, "SEED %d", chosenSeed);                                                                 //? Storing your seed into buffer for use in the next function
        CustomDrawText(buffer, TOP, DEFAULT_SPACING, DEFAULT_SIZE, 5, MOBY_GOLD);                               //? Draw gold text that says: "SEED" with the chosen seed after it at the top of the text box

        CustomDrawText("SQUARE TO RANDOMIZE", TOP, DEFAULT_SPACING, DEFAULT_SIZE, 7, MOBY_PURPLE);              //? Draw purple text that says "SQUARE TO RANDOMIZE" in the middle of the text box

        CustomDrawText("X TO SELECT", MIDDLE, DEFAULT_SPACING, DEFAULT_SIZE, 3, MOBY_BLUE);                     //? Draw blue text that says "X TO SELECT" at the bottom of the text box

        //* Decrement One Option
        if(_currentButtonOneFrame == LEFT_BUTTON && chosenSeed > 0)                                             //? If the player pressed left, and the seed greater than 0, the minimum
        {
            chosenSeed--;                                                                                       //? Decrement the seed by 1, once (since it checked currentButtonOneFrame)
            PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);                      //? Play a sound effect for the selection             
            customMenuTimer = 0;                                                                                //? Reset the timer for the increment/decrement speed up later
        }

        //* Decrement fast after 1 second, then faster after 3 seconds
        if(_currentButton == LEFT_BUTTON && chosenSeed > 0)                                                     //? If the player is holding left, and the seed is not 0
        {
            //* Slower Setting
            if(customMenuTimer > 1*SECONDS)                                                                     //? If the player is holding left for 1 second
            {
                chosenSeed--;                                                                                   //? Decrement the seed by 1 every frame
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);                  //? Play sound effect for each decrement
            }

            //* Faster Setting
            else if(customMenuTimer > 3*SECONDS)                                                                //? If the player is holding left for 3 seconds
            {
                chosenSeed = chosenSeed - 61;                                                                   //? Decrement the seed by 61 every frame. 61 because even numbers look too uniform lol
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);                  //? Play sound effect for each decrement
            }
        }

        //* Increment One Option
        if(_currentButtonOneFrame == RIGHT_BUTTON && chosenSeed < 0x7FFF)                                       //? If the player pressed right, and the seed is not 32727, the maximum
        {
            chosenSeed++;                                                                                       //? Increment the seed by 1, once (since it checked currentButtonOneFrame)
            PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);                      //? Play a sound effect for the selection             
            customMenuTimer = 0;                                                                                //? Reset the timer for the increment/decrement speed up later
        }

        //* Increment fast after 1 second, then faster after 3 seconds
        if(_currentButton == RIGHT_BUTTON)                                                                      //? If the player is holding right
        {
            //* Slower Setting
            if(customMenuTimer > 1*SECONDS)                                                                     //? If the player is holding right for 1 second
            {
                chosenSeed++;                                                                                   //? Incriment the seed by 1 every frame
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);                  //? Play sound effect for each incriment
            }
                
            //* Faster Setting
            else if(customMenuTimer > 5*SECONDS)
            {
                chosenSeed = chosenSeed + 61;                                                                   //? Incriment the seed by 61 every frame. 61 because even numbers look too uniform lol
                PlaySoundEffect(SOUND_EFFECT_GEM_HIT_FLOOR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);                  //? Play sound effect for each incriment
            }
        }

        //* Randomize Seed
        if(_currentButton == SQUARE_BUTTON)                                                                     //? If the player is holding square
        {
            chosenSeed = rand() % 0xFFFF;                                                                       //? Set the seed to a random number between 0-32727 every frame    
            PlaySoundEffect(SOUND_EFFECT_LIFE_CHEST_BLINK, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);                   //? Play a sound effect for every randomization
        }

        //* Check if seed needs to be changed
        if(_currentButton == LEFT_BUTTON || _currentButton == RIGHT_BUTTON || _currentButton == SQUARE_BUTTON)  //? If the player has changed the seed be incrimenting, decrimenting, or randomizing
        {
            hasSeedChanged = TRUE;                                                                              //? Set the hasSeedChanged flag to TRUE, for later use in re-running the redistributer
        }
        else if(_currentButton == 0)                                                                            //? If current button is no inputs
        {
            hasSeedChanged = FALSE;                                                                             //? Set the hasSeedChanged flag to FALSE, to stop the redistributer
        }

        //Close menu and set selected seed
        if(_currentButtonOneFrame == X_BUTTON)                                                                  //? If the player pressed X
        {
            hasSelectedSeed = TRUE;                                                                             //? Set the hasSelectedSeed flag to TRUE, to close the menu, and stop calling this function every frame in main
            PlaySoundEffect(SOUND_EFFECT_DRAGON_DISAPEAR, 0, SOUND_PLAYBACK_MODE_NORMAL, 0);                    //? Play a sound effect when the player closes the menu
            shouldPlayCutscene = TRUE;                                                                          //? Set the shouldPlayCutscene flag to true to play the custom cutscene
        }

        MobyRender();                                                                                           //? Call MobyRender() every frame the function is running, to allow 

        customMenuTimer++;
}

//* Function used to parse the gem data from all the relavent moby's in the level
void ParseGemData(void)
{
        int amountOfMobysInLevel = (*(_ptr_levelMobys - 2) / MOBY_SIZE);                //?? ptr_levelMobys - 2 representing the address for number of bytes that the moby region for the level is taking up.

        //*Itterate through all the mobys in a level
        for (int i = 1; i <= amountOfMobysInLevel; i++)                                 //?? Starting at one to avoid multiplying by 0. This is also why we have to do <= instead of just < like normal
        {
            MobyStruct* currentStruct = _ptr_levelMobys + (MOBY_SIZE/sizeof(int) * i);


            //*Check if the current moby's type is any gem value (0x53-0x57). If it is, add to the total for that specific gem type.
            if(currentStruct->type >=ONE_GEM_MOBY_ID && currentStruct->type <=TWENTYFIVE_GEM_MOBY_ID)
            {
                totalAmountOfPhysicalGems++;
                amountOfGemMobys++;

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
        //printf("Amount of Total Physical Gems: %D\n\nAmount of Gem Mobys: %D\n\nAmount of Held Gems: %D\n\nAmount of One Gems: %D\nAmount of Two Gems: %D\nAmount of Five Gems: %D\nAmount of Ten Gems: %D\nAmount of Twenty Five Gems: %D\n\n", totalAmountOfPhysicalGems, amountOfGemMobys, amountOfHeldGems, amountOfRedGems, amountOfGreenGems, amountOfBlueGems, amountOfYellowGems, amountOfPinkGems); 
        //amountOfGemMobys = 0;
        //amountOfHeldGems = 0;
        //totalAmountOfPhysicalGems = 0; 

        hasParsedLevelGemData = TRUE;                                   //? When finished parsing, set hasParsedLevelGemData to true so it doesn't run again
}

//* Function used to replace the gem data in all the relavent moby's with the redistributed values
void ReplaceGemData(void)
{
        int amountOfMobysInLevel = (*(_ptr_levelMobys - 2) / MOBY_SIZE); //?? ptr_levelMobys - 2 representing the address for number of bytes that the moby region for the level is taking up.

        srand(chosenSeed);
 
        for (int i = 1; i < amountOfMobysInLevel; i++)
        {
            MobyStruct* currentStruct = _ptr_levelMobys + (MOBY_SIZE/sizeof(int) * i);
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
        //printf("~~~ TEST TO SEE IF REPLACED ALL ~~~\nOne Gems Left to Replace: %D\nTwo Gems Left to Replace: %D\nFive Gems Left to Replace: %D\nTen Gems Left to Replace: %D\nTwenty Five Gems Left to Replace: %D\n", amountOfRedGems, amountOfGreenGems, amountOfBlueGems, amountOfYellowGems, amountOfPinkGems); 
        hasReplacedLevelGems = TRUE;
}

//* Returns a random gem offset between 0-4 to add to the default gem value red (0x53), and then applys to a gem. 
//* Takes into consideration the previously parsed data to ensure the same amount of each type of gem exists in each level.
int ReturnRandomGemOffset(void) 
{
    bool hasFoundAvailbleGem = FALSE;
    char gemValueOffset;                    //?Value to add to the initial gem value.
    while(!hasFoundAvailbleGem)
    {
        char fiveSidedDice = rand() % 5;    //?Set random number between 0-4. This represets each possible gem type. Red-Pink.

        //? This code below checks the value of the fiveSidedDice, and also checks if its equivilent "amountOf____Gems" value has any gems left to redistrubute. 
        //? If not, it re-rolls. If it does, it decreases the amount of specific gem type left to distrubted, and returns the offset from the dice.
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

        if(hasFoundAvailbleGem)                                                     //? If a gem to be redistributed has been found
        {
            gemValueOffset = fiveSidedDice;
            return gemValueOffset;                                                  //? Return the required offset to add to the default red gem (0x53)
        }
    }
}

//* Function used to update the required booleans when need be
void UpdateFlags(void)
{
    //* ~~Main Resets~~:

    //* This is the main statement that checks if it needs to do another run through of checking/setting gems 
    if(hasSeedChanged)                                                                                      
    {
        hasParsedLevelGemData = FALSE;                                          //? Allow ParseGemData to run again once
        hasReplacedLevelGems = FALSE;                                           //? Allow ReplaceGemData to run again once
    }

    //* If its the first seed, allow the first pass through of checking/setting gems.
    if(!hasRanFirstSeed)
    {
        hasParsedLevelGemData = FALSE;                                          //? Allow ParseGemData to run once
        hasReplacedLevelGems = FALSE;                                           //? Allow ParseGemData to run once

        hasRanFirstSeed = TRUE;                                                 //? Never run this again
    }

    //* ~~Level Entry/Exit/Balloonist/Death Resets~~:

    //* This is the code that checks if you have died/re-entered a level, so that we can redistribute again once
    if(!hasReplacedAfterEntry && (_glideSubState == 0x9 || _glideSubState == 0xA || _glideSubState == 0xB || _ballonistState == 0x6 || (_spyro.canInput != 0 && _effect_ScreenFadeIn != 0)))
    {
        hasParsedLevelGemData = FALSE;
        hasReplacedLevelGems = FALSE;

        hasReplacedAfterEntry = TRUE;
    }

    //* This checks if you have fully re-entered the level, so that next time we have to redistribute we can
    else if(_glideSubState != 0x9 && _glideSubState != 0xA && _glideSubState != 0xB && _gameState != GAMESTATE_BALLOONIST && (_spyro.canInput == 0 && _effect_ScreenFadeIn == 0))
    {
        hasReplacedAfterEntry = FALSE;
    }

}

//* ~~Main Hook~~
void mainFunc()
{
    //*If hasn't selected seed yet, and is in artisans
    if(_gameState == GAMESTATE_GAMEPLAY && _levelID == ARTISANS_ID && !hasSelectedSeed)
        SelectSeed();  
    
    if(shouldPlayCutscene)
    {
        bool hasFinished = PlayCustomCutscene();

        if(hasFinished)
        {
            shouldPlayCutscene = FALSE;
        }
    }

    if(!hasParsedLevelGemData)
        ParseGemData();     

    if(hasParsedLevelGemData && !hasReplacedLevelGems)
        ReplaceGemData();   

    //*Button combo for easy reset
    if(_currentButton == L1_BUTTON + L2_BUTTON + R1_BUTTON + R2_BUTTON + TRIANGLE_BUTTON)
    {
        hasSelectedSeed = FALSE;
        chosenSeed = 0;
        TheAdventureBegins();
    }
    
    //*~~~ UPDATES ~~~
    UpdateFlags();
}
