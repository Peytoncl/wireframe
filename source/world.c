#include <math.h>

#include "../headers/world.h"

Object objects[MAX_OBJECTS] = 
{
    {

        {

            {-50, 50, 50},
            {50, 50, 50},
            {50, 50, -50},
            {-50, 50, -50},
            {-50, -50, 50},
            {50, -50, 50},
            {50, -50, -50},
            {-50, -50, -50}

        },

        8,

        {
          {0, 1}, {1, 2}, {2, 3}, {3, 0},
          {4, 5}, {5, 6}, {6, 7}, {7, 4},
          {0, 4}, {1, 5}, {2, 6}, {3, 7}
        },

        12,

        {0, 0, 0},

        {0.5, 0.5, 1},

        1

    }
};

Vector3 Add(Vector3 v1, Vector3 v2)
{
    double pX = v1.x + v2.x;
    double pY = v1.y + v2.y;
    double pZ = v1.z + v2.z;

    return (Vector3){pX, pY, pZ};
}

Vector3 Subtract(Vector3 v1, Vector3 v2)
{
    double pX = v1.x - v2.x;
    double pY = v1.y - v2.y;
    double pZ = v1.z - v2.z;

    return (Vector3){pX, pY, pZ};
}

double Distance(Vector3 v1, Vector3 v2)
{
    double dx = v1.x - v2.x;
    double dy = v1.y - v2.y;
    double dz = v1.z = v2.z;

    return dx * dx + dy * dy + dz * dz;
}

Vector2 WorldToScreen(Vector3 pWorld, Vector3 cameraPos, Angle angle)
{
    
    Vector3 pCamera = (Vector3){pWorld.x - cameraPos.x, pWorld.y - cameraPos.y, pWorld.z - cameraPos.z};

    double cosYaw = cos(angle.y);
    double sinYaw = sin(angle.y);

    double tempX = pCamera.x * cosYaw + pCamera.z * sinYaw;
    double tempZ = -pCamera.x * sinYaw + pCamera.z * cosYaw;

    pCamera.x = tempX;
    pCamera.z = tempZ;

    double cosPitch = cos(angle.x);
    double sinPitch = sin(angle.x);

    double tempY = pCamera.y * cosPitch - pCamera.z * sinPitch;
    tempZ = pCamera.y * sinPitch + pCamera.z * cosPitch;

    pCamera.y = tempY;
    pCamera.z = tempZ;

    double xProj = pCamera.x / pCamera.z;
    double yProj = pCamera.y / pCamera.z;

    double screenX = (xProj + 1) * 0.5;
    double screenY = (yProj + 1) * 0.5;

    return (Vector2){screenX, screenY};

}