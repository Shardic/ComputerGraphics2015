//hallo Olli
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <windows.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include "ObjectForProgramm.h"
using namespace std;


static ObjectForProgramm objects;
static float edgeLength = 2.0f;

static double xCord = 0;
static double yCord = 0;
static double zCord = -10;

static double rotateRightLeft = 0;
static double rotateUpDown = 0;
static double rotateZ = 0;

static boolean closeNormal = true;

static double xMouse = 0;
static double yMouse = 0;

static double window_width_ = 700;
static double window_height_ = 700;


void SetMaterialColor(int side, double r, double g, double b) {
  float	amb[4], dif[4], spe[4];
  int mat;

  dif[0] = r;
  dif[1] = g;
  dif[2] = b;

  for(int i = 0; i < 3; i++) {
    amb[i] = .1 * dif[i];
    spe[i] = .5;
  }
  amb[3] = dif[3] = spe[3] = 1.0;

  switch(side){
    case 1:	mat = GL_FRONT;
      break;
    case 2:	mat = GL_BACK;
      break;
    default: mat = GL_FRONT_AND_BACK;
  }

  glMaterialfv(mat, GL_AMBIENT, amb);
  glMaterialfv(mat, GL_DIFFUSE, dif);
  glMaterialfv(mat, GL_SPECULAR, spe);
  glMaterialf( mat, GL_SHININESS, 20);
}


static void key_callbackBox(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	 glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
    	rotateUpDown += 1;
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
    	rotateUpDown -= 1;
    }
    if (key == GLFW_KEY_A && action == GLFW_REPEAT){
    	rotateRightLeft -= 1;
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
    	rotateRightLeft += 1;
    }
    if (key == GLFW_KEY_E && action == GLFW_REPEAT) {
    	rotateZ -= 1;
    }
    if (key == GLFW_KEY_Q && action == GLFW_REPEAT) {
    	rotateZ += 1;
    }

    //movement up down left right
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
    	yCord += 0.5;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
    	 xCord -= 0.5;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    	yCord -= 0.5;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    	xCord += 0.5;
    }
    if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
    	yCord += 0.5;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT){
    	 xCord -= 0.5;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
    	yCord -= 0.5;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
    	xCord += 0.5;
    }

    //Zoom in or out
    if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
    	zCord -= 1;
    }
    if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
    	zCord += 1;
    }
    if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_REPEAT) {
    	zCord -= 1;
    }
    if (key == GLFW_KEY_KP_ADD && action == GLFW_REPEAT) {
    	zCord += 1;
    }
}
// The mouse Position gets asked and translated to world coordinates
// TODO: gehört hier die Abfrage ob er klickt auch dazu?)
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos){
	yMouse = 5 - ypos/window_width_ * 10;
	xMouse = -5 + xpos/window_height_ * 10;
}

// set viewport transformations and draw objects
void InitLighting() {
  GLfloat lp1[4]  = { 10,  5,  10,  0};
  GLfloat lp2[4]  = { -5,  5, -10,  0};
  GLfloat lp3[4] = {0,10,-10,0};
  GLfloat white[4] = {1.0,1.0,1.0,1};
  GLfloat red[4]  = {1.0, .8,  .8,  1};
  GLfloat blue[4] = { .8, .8, 1.0,  1};
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT1, GL_POSITION, lp1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  red);
  glLightfv(GL_LIGHT1, GL_SPECULAR, red);
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT2, GL_POSITION, lp2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE,  blue);
  glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
  glEnable(GL_LIGHT2);
  glLightfv(GL_LIGHT3, GL_POSITION, lp3);
  glLightfv(GL_LIGHT3, GL_DIFFUSE,  white);
  glLightfv(GL_LIGHT3, GL_SPECULAR, white);
  glEnable(GL_LIGHT3);
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // init viewport to canvassize
  glViewport(0, 0, window_width_, window_height_);
  // init coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, edgeLength, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// draw the entire scene
void Preview(GLFWwindow* window) {
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_NORMALIZE);
}

int main() {
  GLFWwindow* window = NULL;
  printf("Here we go!\n");
  if(!glfwInit()){
    return -1;
  }
  window = glfwCreateWindow(window_width_, window_height_,
                            "Open The Box", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  InitLighting();
  while(!glfwWindowShouldClose(window)) {
    // sets the Background Color // TODO: maybe we want a Texture
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw the scene
    Preview(window);
    // make it appear (before this, it's hidden in the rear buffer)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  printf("Goodbye!\n");

  return 0;
}






//Das war in der Preview:
/*

// der Code für den Ball und die Kollisionserkennung
glLoadIdentity();
glfwSetCursorPosCallback(window, cursor_pos_callback);
glTranslated(xMouse,yMouse,-10);
SetMaterialColor(1, 1, 1, 0);
SetMaterialColor(2, 0, 0, 1);

//MaterialColors for the cube
SetMaterialColor(1, 1, 0, 0);
SetMaterialColor(2, 0, 0, 1);
glLoadIdentity();

glfwSetKeyCallback(window, key_callbackBox);
glTranslated(xCord, yCord, zCord);
glRotated(rotateUpDown, 1, 0, 0);
glRotated(rotateRightLeft, 0, 1, 0);
glRotated(rotateZ,0,0,1);

objects.drawCubeWithoutTop(edgeLength);

if(closeNormal) {
	  glTranslated(0, edgeLength/2, -edgeLength/2);
	  objects.openCloseNormal();
	  objects.drawTopOfCube(edgeLength);
} else {
	  //Wegen der komplexität des Mechanismuss wird die Zeichnung während des schließens vorgenommen
	  glTranslated(0, edgeLength/2, -edgeLength/2);
	  objects.openCloseAccordion(edgeLength);
}
*/
