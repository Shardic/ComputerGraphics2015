#include <GL/gl.h>
#include "Goal.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define PI 3.14159265

Goal::Goal() {
}
Goal::~Goal(){
}

void Goal::drawGoal() {
	   glBegin(GL_POLYGON);
	   for (int i = 0; i < 360; i++)
	   {
	      float degInRad = i*PI/180;
	      glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
	   }

	   glEnd();
}
