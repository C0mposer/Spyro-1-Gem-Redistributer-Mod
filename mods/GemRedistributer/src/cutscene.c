#include "cutscene.h"
#include <common.h>
#include <custom_types.h>
#include <my_math.h>
#include <spyro.h>
#include <custom_text.h>
#include <moby.h>
#include <sound.h>



//* Globals from GemRedistributer.h
extern short chosenSeed;
extern bool hasSeedChanged;


bool PlayCustomCutscene(void)
{
    static bool hasFinished = FALSE;                                                                                            //? Will be used to determine if the cutscene has completed
    static bool hasSavedCameraData = FALSE;                                                                                     //? Will be used to determine if the camera data has been saved
    static bool shouldMoveCamera = FALSE;                                                                                       //? Will be used to determine if the camera cutscene should start

    static char customDirection = 0;                                                                                            //? Will be used to determine the direction of the cutscene.
    static int customCameraTimer = 0;                                                                                           //? Timer to be used for animating the cutscene
    static int randomGemSlowdownTimer = 0;                                                                                      //? Timer to be used for slowing down the gem randomization

    static unsigned short seedBackup = 0;                                                                                       //? Will be used to restore the chosed seed after the gem randomization part of the cutscene

    static Vec3 animatedPosition = {0};                                                                                         //? Will be used to store the lerped position vector
    static CameraAngle animatedAngle = {0};                                                                                     //? Will be used to store the lerped angle vector

    static Vec3 originalPosition = {0};                                                                                         //? Will be used to store the original camera position
    static CameraAngle orignalAngle = {0};                                                                                      //? Will be used to store the original camera angle

    const Vec3 customPosition = {0x000138ED, 0x0000B860, 0x000020D0};                                                           //? Custom position near the 4 reds to the left of nestor
    const CameraAngle customAngle = {0x0000, 0x009F, 0x06F1};                                                                   //? Custom Angle looking at the 4 reds to the left of nestor

    if (!hasSavedCameraData)                                                                                                    //? If has not saved the camera data
    {
        originalPosition.x = _cameraPosition.x;                                                                                 //? Save the camera position info into orignalPosition for later
        originalPosition.y = _cameraPosition.y;
        originalPosition.z = _cameraPosition.z;

        orignalAngle.roll = _cameraAngle.roll;                                                                                  //? Save the camera angle info into orignalAngle for later
        orignalAngle.pitch = _cameraAngle.pitch;
        orignalAngle.yaw = _cameraAngle.yaw;

        seedBackup = chosenSeed;                                                                                                //? Save a backup of the seed for after the visual randomization

        hasSavedCameraData = TRUE;                                                                                              //? Sets the hasSavedCameraData flag to TRUE, so it doesn't save anymore.
        shouldMoveCamera = TRUE;                                                                                                //? Sets the shouldMoveCamera flag to TRUE, so the main cutscene animation loop can run
        customCameraTimer = 0;                                                                                                  //? Resets the camera timer
    }

    //* Cutscene Animation Loop
    if (shouldMoveCamera)
    {       
        _spyro.isMovementLocked = TRUE;                                                                                         //? Forces the player to not be able to move spyro

        _shouldCameraFollowSpyro = DONT_FOLLOW_SPYRO;                                                                           //? NOP's the call to SpyroCamera() to allow the camera to be free

        //*First Half of Camera Animation
        if (customCameraTimer < 4 * SECONDS && customDirection == 0)                                                            //? If the timer is less than 4 seconds, and is the first direction
        {

            //*Animate to the custom camera position
            if (customCameraTimer <= 50)                                                                                        //? If timer is less than 1.5 seconds
            {
                animatedPosition = Vector3Lerp(originalPosition, customPosition, customCameraTimer*2);                          //? Set the animated position to the lerp of the 2 position vectors
                animatedAngle = CameraAngleLerp(orignalAngle, customAngle, customCameraTimer*2);                                //? Set the animated angle to the lerp of the 2 angle vectors

                if((randomGemSlowdownTimer % 2) == 1)                                                                           //? If every other frame
                {
                    chosenSeed = (unsigned short)rand();                                                                        //? Set the seed to a random value
                    PlaySoundEffect(SOUND_EFFECT_LIFE_CHEST_BLINK, 0x8016D808, SOUND_PLAYBACK_MODE_CONNECTED_TO_MOBY, 0);       //? Play sound effect for every randomization
                    hasSeedChanged = TRUE;                                                                                      //? Set hasSeedChanged flag to true so it can run the redistribution
                }
            }

            //*Stay at the custom camera position
            if (customCameraTimer > 50)                                                                                         //? If the timer is over 1.5 seconds
            {
                animatedPosition = Vector3Lerp(originalPosition, customPosition, 100);                                          //? Set the animated position to the custom position vector
                animatedAngle = CameraAngleLerp(orignalAngle, customAngle, 100);                                                //? Set the animated angle to the custom angle vector

                if((randomGemSlowdownTimer % 2) == 1)                                                                           //? If every other frame
                {                               
                    chosenSeed = (unsigned short)rand();                                                                        //? Set the seed to a random value
                    PlaySoundEffect(SOUND_EFFECT_LIFE_CHEST_BLINK, 0x8016D808, SOUND_PLAYBACK_MODE_CONNECTED_TO_MOBY, 0);       //? Play sound effect for every randomization
                    hasSeedChanged = TRUE;                                                                                      //? Set hasSeedChanged flag to true so it can run the redistribution
                }
            }

            //*Setting the Required Values
            _cameraPosition = animatedPosition;                 //? Setting Camera position to custom position
            _cameraAngle = animatedAngle;                       //? Setting Camera position to custom position
            
        }

        //*Prepare for second half of animation
        else if (customCameraTimer >= 4 * SECONDS)              
        {
            customCameraTimer = 0;                              //? Reset the camera timer for the next half
            customDirection = 1;                                //? Set the direction to 1, which means go back towards the player
            chosenSeed = seedBackup;                            //? Set the seed back to its original value after the randomization animation
        }

        //*Second half of camera animation
        else if (customCameraTimer < 4 * SECONDS && customDirection == 1)                                           //? If the timer is less than 4 seconds, and is the 2nd direction back towards spyro
        {

            if (customCameraTimer > 1)
            {
                hasSeedChanged = FALSE;                                                                             //? Stops visually randomizing the gems once the amimation back has started
            }

            //*Animate back to orignal camera position
            if (customCameraTimer <= 50)                                                                            //? If the camera timer is less than 1.5 seconds
            {
                animatedPosition = Vector3Lerp(customPosition, originalPosition, customCameraTimer*2);              //? Set the animated position to the custom position vector
                animatedAngle = CameraAngleLerp(customAngle, orignalAngle, customCameraTimer*2);                    //? Set the animated angle to the custom angle vector

                CustomDrawText("GLHF", MIDDLE, DEFAULT_SPACING, DEFAULT_SIZE, ROW1, MOBY_GOLD);                     //? Draw gold text that says "GLHF"
                MobyRender();                                                                                       //? Call MobyRender for the pre-req's for DrawText
                
            }

            //*Setting the Required Values
            _cameraPosition = animatedPosition;                                                                     //? Setting Camera position to custom position
            _cameraAngle = animatedAngle;                                                                           //? Setting Camera position to custom position

            //*Return control back to player, return camera to lock onto spyro, and end this function.
            if (customCameraTimer > 50)                                                                             //? If the camera timer is over 1.5 seconds
            {
                animatedPosition = Vector3Lerp(customPosition, originalPosition, 100);                              //? Set the animated position to the custom position vector
                animatedAngle = CameraAngleLerp(customAngle, orignalAngle, 100);                                    //? Set the animated angle to the custom angle vector

                customDirection = 0;                                                                                //? Resets Direction. Shouldn't matter since it only runs once though
                shouldMoveCamera = FALSE;                                                                           //? Sets the shouldMoveCamera flag to FALSE to stop the animation loop from running
                hasSavedCameraData = FALSE;                                                                         //? Sets the hasSavedCameraData flag to FALSE. Shouldn't matter since it only runs once
                _spyro.isMovementLocked = FALSE;                                                                  //? Allows the player to input again
                _shouldCameraFollowSpyro = FOLLOW_SPYRO;                                                            //? UN-NOP's the call to SpyroCamera() to allow the camera to follow spyro again
                hasFinished = TRUE;
            }

        }
    }

    customCameraTimer++;                                                                                            //? Updating the camera timer every frame for the animation.
    randomGemSlowdownTimer++;                                                                                       //? Updating the timer that is used to run the visual randomization every OTHER frame. This gets % 2.

    bool hasFinishedTemp = hasFinished;                                                                             //? 1-5-23 11:30PM = Created a temp variable to return the result of hasFinished
    hasFinished = FALSE;                                                                                            //? 1-5-23 11:30PM = Because hasFinished needs to get set to FALSE so it can run again if the player resets.

    return hasFinishedTemp;                                                                                         //? Returns true when it is done

}