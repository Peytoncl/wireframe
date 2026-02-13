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

float CENTER_X = (WINDOW_W / 2);
float CENTER_Y = (WINDOW_H / 2);

Player player = { {0, 0, 0}, {0, 0} };

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

      Vector2 screenPoint = WorldToScreen(pWorld, player.position);
      Vector2 screenPoint1 = WorldToScreen(pWorld1, player.position);

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

void update()
{
  
  if (keys['a'])
  {
    player.position.x += 0.025;
  }

  if (keys['d'])
  {
    player.position.x -= 0.025;
  }

  if (keys['w'])
  {
    player.position.z -= 0.025;
  }
  
  if (keys['s'])
  {
    player.position.z += 0.025;
  }

  glutPostRedisplay();
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

  glutReshapeFunc(windowResize);

  glutMainLoop();      
  return 0;   
}