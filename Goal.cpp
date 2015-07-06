#include <GL/gl.h>
#include "Goal.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

const float DEG2RAD = 3.14159/180;
double radius = 0.5;

Goal::Goal() {
}
Goal::~Goal(){
}

void Goal::drawGoal() {
	   glBegin(GL_POLYGON);
	   for (int i = 0; i < 360; i++)
	   {
	      float degInRad = i*DEG2RAD;
	      glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
	   }

	   glEnd();
}
