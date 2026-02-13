#ifndef WORLD

#define WORLD

#include "colors.h"

#define MAX_VERTICES 1000
#define MAX_OBJECTS 1000

typedef struct
{
    double x;
    double y;
    double z;
} Vector3;

typedef struct
{
    double x;
    double y;
    double z;
    double w;
} Vector4;

typedef struct
{
    double x;
    double y;
} Vector2;

typedef struct
{
    double x;
    double y;
} Angle;

typedef struct
{
    Vector3 vertices[MAX_VERTICES];
    int verticeAmount;
    Vector2 edges[MAX_VERTICES];
    int edgeAmount;
    Vector4 faces[MAX_VERTICES];
    int faceAmount;
    Vector3 position;
    Color color;
    int active;
} Object;

extern Object objects[MAX_OBJECTS];

Vector3 Add(Vector3 v1, Vector3 v2);
Vector3 Subtract(Vector3 v1, Vector3 v2);

double Distance(Vector3 v1, Vector3 v2);

int ClipLine(Vector3 *p0, Vector3 *p1, double nearPlane);
Vector2 WorldToScreen(Vector3 pWorld, Vector3 cameraPos, Angle angle);

#endif