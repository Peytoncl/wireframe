#ifndef WORLD

#define WORLD

#include "colors.h"

#define MAX_VERTICES 64
#define MAX_OBJECTS 64

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
    Vector3 position;
    Color color;
    int active;
} Object;

extern Object objects[MAX_OBJECTS];

Vector3 Add(Vector3 v1, Vector3 v2);
Vector3 Subtract(Vector3 v1, Vector3 v2);

double Distance(Vector3 v1, Vector3 v2);

Vector2 WorldToScreen(Vector3 pWorld, Vector3 cameraPos);

#endif