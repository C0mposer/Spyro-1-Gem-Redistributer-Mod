#include <my_math.h>
#include <common.h>

#define CAMERA_ROTATION_RANGE 0x1000

struct Vec3 Vector3Lerp(struct Vec3 v1, struct Vec3 v2, int percentage)
{
    struct Vec3 result = { 0 };

    result.x = v1.x + percentage*(v2.x - v1.x)/100;     //? Dividing by 100 because of lack of floating point. Equivalent to having percentage be a number between 0.00 and 1.00
    result.y = v1.y + percentage*(v2.y - v1.y)/100;
    result.z = v1.z + percentage*(v2.z - v1.z)/100;

    return result;
}

struct CameraAngle CameraAngleLerp(struct CameraAngle v1, struct CameraAngle v2, int percentage)
{
    struct CameraAngle result = { 0 };

    struct CameraAngle adjustedv1 = { v1.roll % CAMERA_ROTATION_RANGE, v1.pitch % CAMERA_ROTATION_RANGE, v1.yaw % CAMERA_ROTATION_RANGE };     //? Is adjusting to be by % 1000 because the range of the rotation is between 0 and 0FFF.
    struct CameraAngle adjustedv2 = { v2.roll % CAMERA_ROTATION_RANGE, v2.pitch % CAMERA_ROTATION_RANGE, v2.yaw % CAMERA_ROTATION_RANGE };     //? The first number is the percentage of rotations it has done. I.E 0FFF, 1FFF, 2FFF, are the same.

    result.roll = adjustedv1.roll + (percentage*(adjustedv2.roll - adjustedv1.roll)/100);       //? Dividing by 100 because of lack of floating point. Equivalent to having percentage be a number between 0.00 and 1.00
    result.pitch = adjustedv1.pitch + (percentage*(adjustedv2.pitch - adjustedv1.pitch)/100);
    result.yaw = adjustedv1.yaw + (percentage*(adjustedv2.yaw - adjustedv1.yaw)/100);

    return result;
}