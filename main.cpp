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
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#define _USE_MATH_DEFINES
#include "ObjectManager.h"
using namespace std;

//Manager for all Objects in the Game
static ObjectManager objectManager;

static bool playerSetsObjects = true;
static bool playerSetsSmallBall = false;
static bool playerSetsWall = false;
static bool playerSetsCylinder = false;

static bool gameIsFinished = false;
static bool endScreenWasShown = false;

static int wallClickCounter = 0;

float x1Wall;
float y1Wall;
float x2Wall;
float y2Wall;
float x1Ball;
float y1Ball;

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
    //Kleinere Bälle
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {
    	playerSetsSmallBall = true;
    }

}
//mausklicks werden hier abgefangen
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

    	if (playerSetsCylinder) {
			float x1 = (float)xMouse;
			float y1 = (float)yMouse;
			playerSetsCylinder = false;
			objectManager.setUserCylinder(x1, y1);
    	} else if (playerSetsWall && wallClickCounter == 0) {
    			wallClickCounter++;
    			x1Wall = (float)xMouse;
    			y1Wall = (float)yMouse;
    	} else if (playerSetsWall && wallClickCounter == 1) {
    			x2Wall = (float)xMouse;
    		    y2Wall = (float)yMouse;
    		    objectManager.setUsersWall(x1Wall, y1Wall, x2Wall, y2Wall);
        		playerSetsWall = false;
        		wallClickCounter = 0;
   		} else if (playerSetsSmallBall) {
   			//kleinere Bälle setzen
			x1Ball = (float)xMouse;
			y1Ball = (float)yMouse;
			objectManager.setUserSmallBall(x1Ball,y1Ball);
			playerSetsSmallBall = false;
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
		objectManager.drawDirectionPointer();
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetKeyCallback(window, key_firstCallback);
	} else if(!playerSetsObjects && !gameIsFinished) {
		//Wenn das Spiel gestartet wurde wird die sich
		//bewegende Kugel versetzt und deren Kollision berechnet
		//währenddessen kann man das gesamte Feld drehen wie man möchte
		gameIsFinished = objectManager.checkVictoryCondition();
		objectManager.checkCollision();
		glfwSetKeyCallback(window, key_callbackBox);
		objectManager.moveMovables();
	} else if (gameIsFinished && endScreenWasShown){
		objectManager.drawEndScreen();
	} else {
	}
	//Der Ball wird immer gezeichnet, aber seperat, da er beweglich ist
	//Die Objekte werden sobald der Spieler diese platziert hat gezeichnet
	objectManager.drawPlacedObjects();
	objectManager.drawGameBalls();
}

int main() {
  GLFWwindow* window = NULL;

  cout << "Here we go!" << endl ;

  if(!glfwInit()){
    return -1;
  }

  window = glfwCreateWindow(window_width_, window_height_,
                            "The Pinball", NULL, NULL);

  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  InitLighting();

  double lastTime, nowTime, delta, ms;
  double timer = glfwGetTime();
  int fps = 0;
  ms = 16.66666;

  lastTime = glfwGetTime() * 1000; //time in ms

  while(!glfwWindowShouldClose(window)) {

	nowTime = glfwGetTime() * 1000;
	delta += (nowTime - lastTime) / ms;
	lastTime = nowTime;

	if (delta >= 1) {

	    // sets the Background Color
	    glClearColor(0.8, 0.8, 0.8, 1.0);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    // draw the scene
	    Preview(window);
	    // make it appear (before this, it's hidden in the rear buffer)
	    glfwSwapBuffers(window);
	    glfwPollEvents();

	    fps++;
	    delta = 0;

	    if ((glfwGetTime()-timer)>=1) {
	    	stringstream fpsStream;
	    	fpsStream << fps;
	    	string temp_str = "The Pinball, FPS is " + fpsStream.str();
	    	char const* pchar = temp_str.c_str();
	    	glfwSetWindowTitle(window,pchar);
	    	timer = glfwGetTime();
	    	fps = 0;
	    }
	}
  }

  glfwTerminate();

  cout << "Good Bye!" << endl;

  return 0;
}
