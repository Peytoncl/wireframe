#include <GL/glut.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 

#include <math.h>

#include <windows.h>

#include "../headers/graphics.h"
#include "../headers/game.h"

#define KEY_COUNT 256 

bool keys[KEY_COUNT];

int CENTER_X = (int)(WINDOW_W / 2);
int CENTER_Y = (int)(WINDOW_H / 2);

Player player = { {0, 0, 0}, {0, 0} };

Vector2 lastMouse;

double sensitivity = 0.01;

void init()
{
  glClearColor(0, 0, 0, 0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 1, 1, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPointSize(3.0f);
  glDisable(GL_DEPTH_TEST);

  glViewport(0, 0, WINDOW_W, WINDOW_H);

  lastMouse.x = CENTER_X;
  lastMouse.y = CENTER_Y;

  SetCursorPos(CENTER_X, CENTER_Y);
}

void display() 
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_LINES);

  for (int i = 0; i < MAX_OBJECTS; i++)
  {
    if (objects[i].active == 0) break;

    glColor3f(objects[i].color.r, objects[i].color.g, objects[i].color.b);

    for (int e = 0; e < objects[i].edgeAmount; e++)
    {

      Vector3 pWorld = Add(objects[i].position, objects[i].vertices[(int)objects[i].edges[e].x]);
      Vector3 pWorld1 = Add(objects[i].position, objects[i].vertices[(int)objects[i].edges[e].y]);

      Vector2 screenPoint = WorldToScreen(pWorld, player.position, player.angle);
      Vector2 screenPoint1 = WorldToScreen(pWorld1, player.position, player.angle);

      glVertex2d(screenPoint.x, screenPoint.y);
      glVertex2d(screenPoint1.x, screenPoint1.y);

    }

  }

  glEnd();

  glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) 
{
  keys[key] = true; 
}

void keyUp(unsigned char key, int x, int y) 
{
  keys[key] = false; 
}

double speed = 0.025;

void update()
{
  double forwardX = sin(player.angle.y);
  double forwardZ = -cos(player.angle.y);

  double rightX = cos(player.angle.y);
  double rightZ = sin(player.angle.y);

  double moveX = 0.0;
  double moveZ = 0.0;

  if (keys['w']) { moveX += forwardX; moveZ += forwardZ; }
  if (keys['s']) { moveX -= forwardX; moveZ -= forwardZ; }

  if (keys['a']) { moveX += rightX; moveZ += rightZ; }
  if (keys['d']) { moveX -= rightX; moveZ -= rightZ; }

  player.position.x += moveX * speed;
  player.position.z += moveZ * speed;

  glutPostRedisplay();
}

void mouseMove(int x, int y)
{
  int deltaX = x - lastMouse.x;
  int deltaY = y - lastMouse.y;

  player.angle.y -= deltaX * sensitivity;
  player.angle.x += deltaY * sensitivity;

  lastMouse.x = x;
  lastMouse.y = y;

  //SetCursorPos(CENTER_X, CENTER_Y);
}

void windowResize(int width, int height)
{
  //glutReshapeWindow(WINDOW_W, WINDOW_H);
}

int main(int argc, char** argv) 
{
  glutInit(&argc, argv);    

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);        
  glutInitWindowSize(WINDOW_W, WINDOW_H);        
  
  glutCreateWindow("wireframe");  

  init();

  for (int i = 0; i < KEY_COUNT; i++) 
  {
    keys[i] = false;
  }

  glutDisplayFunc(display); 
  glutIdleFunc(update);      

  glutKeyboardFunc(keyDown);  
  glutKeyboardUpFunc(keyUp);  

  glutPassiveMotionFunc(mouseMove);
  glutMotionFunc(mouseMove);

  glutReshapeFunc(windowResize);

  glutMainLoop();      
  return 0;   
}