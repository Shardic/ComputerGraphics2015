//hallo Olli
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <windows.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include "ObjectManager.h"
using namespace std;

//Manager for all Objects in the Game
static ObjectManager objectManager;

static bool playerSetsObjects = true;
static bool playerSetsWall = false;
static bool playerSetsCylinder = false;
static int wallClickCounter = 0;

float x1Wall;
float y1Wall;
float x2Wall;
float y2Wall;

static double xCord = 0;
static double yCord = 0;
static double zCord = -13;

static double rotateRightLeft = 0;
static double rotateUpDown = 0;
static double rotateZ = 0;

static double xMouse = 0;
static double yMouse = 0;

static double window_width_ = 700;
static double window_height_ = 700;

static void key_firstCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	 glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
    	 playerSetsObjects = false;
    }

    //Tasten um zwischen Mauern und Zylindern umzuschalten:
    //Mauer
    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
    	playerSetsWall = true;
    }
    //Zylinder
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        playerSetsCylinder = true;
    }

}
//mausklicks werden hier abgefangen
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    	cout << "click" << endl;

    	if (playerSetsCylinder) {
    		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    			float x1 = (float)xMouse;
    			float y1 = (float)yMouse;

    			playerSetsCylinder = false;
    		}
    	}
    	if (playerSetsWall && wallClickCounter == 0) {
    			wallClickCounter++;
    			x1Wall = (float)xMouse;
    			y1Wall = (float)yMouse;
    	} else if (playerSetsWall && wallClickCounter == 1) {
    			x2Wall = (float)xMouse;
    		    y2Wall = (float)yMouse;
    		    objectManager.drawUsersWall(x1Wall, y1Wall, x2Wall, y2Wall);
        		playerSetsWall = false;
        		wallClickCounter = 0;
   		}
   	}
}

// Die Funktion die beim durchlaufen des Spiels fuer die Tasteneingabe gebraucht wird
//Dadurch wird die Rotation usw. umgesetzt
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
	yMouse = (zCord*-1) - ypos/window_width_ * (zCord*-1*2);
	xMouse = -(zCord*-1) + xpos/window_height_ * (zCord*-1*2);
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
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0f, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// draw the entire scene
void Preview(GLFWwindow* window) {
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_NORMALIZE);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	//die Rotationen der gezeigten Objekte im Spiel werden im Manager durchgeführt
	objectManager.transRotateAllObjekts(xCord,yCord,zCord,
			rotateRightLeft,rotateUpDown,rotateZ);
	//das Spielfeld wird erstellt und alle Objekte die darauf existieren gezeichnet
	objectManager.initGameField(10.0f);
	//Es wird geprüft welche Aktion grade ausgeführt wird:
	//ob der Spieler Gegenstände setzt oder das Spiel läuft und
	// die Kugel sich bewegt
	if (playerSetsObjects) {
		//In diesem Teil der Schleife kann der Nutzer von der Draufsicht
		// die Objekte setzen in der Schleife wird nur abgefragt wo diese hin sollen
		// also eine bestimmte Anzahl an Mauern un Zylindern
		// mit Y kann dieser Teil beendet werden
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetKeyCallback(window, key_firstCallback);
	} else {
		//Wenn das Spiel gestartet wurde wird die sich
		//bewegende Kugel versetzt und deren Kollision berechnet
		//währenddessen kann man das gesamte Feld drehen wie man möchte
		glfwSetKeyCallback(window, key_callbackBox);
	}
	//Der Ball wird immer gezeichnet, aber seperat, da er beweglich ist
	//Die Objekte werden sobald der Spieler diese platziert hat gezeichnet
	objectManager.drawPlacedObjects();
	objectManager.drawGameBalls();
}

int main() {
  GLFWwindow* window = NULL;

  cout << "Here we go!" << endl ;

  //printf("Here we go!\n");

  if(!glfwInit()){
    return -1;
  }

  window = glfwCreateWindow(window_width_, window_height_,
                            "Be the Pinball table", NULL, NULL);

  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  InitLighting();
  double lastTime, nowTime, delta, ms;
  double timer = glfwGetTime();
  int fps = 0;
  ms = 37.03703;
  lastTime = glfwGetTime() * 1000; //time in ms
  while(!glfwWindowShouldClose(window)) {
	nowTime = glfwGetTime() * 1000;
	delta += (nowTime - lastTime) / ms;
	lastTime = nowTime;
	if (delta >= 1) {
		fps++;
	    // sets the Background Color // TODO: maybe we want a Texture
	    glClearColor(0.8, 0.8, 0.8, 1.0);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    // draw the scene
	    Preview(window);
	    // make it appear (before this, it's hidden in the rear buffer)
	    glfwSwapBuffers(window);
	    glfwPollEvents();
	    delta = 0;
	    if ((glfwGetTime()-timer)>=1) {
	    	cout <<  "fps: " << fps << endl;
	    	timer = glfwGetTime();
	    	fps = 0;
	    }
	}
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
