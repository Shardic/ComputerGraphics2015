#include <GL/gl.h>
#include "Cylinder.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

Cylinder::Cylinder() {
}
Cylinder::~Cylinder(){
}

void Cylinder::drawCylinder() {
	int numMajor = 60;
	int numMinor = 60;
	float height = 2;
	float radius = 1;
	double majorStep = height / numMajor;
	double minorStep = 2.0 * M_PI / numMinor;
	int i, j;

	for (i = 0; i < numMajor; ++i) {
	GLfloat z0 = 0.5 * height - i * majorStep;
	GLfloat z1 = z0 - majorStep;

	glBegin(GL_TRIANGLE_FAN);
	for (j = 0; j <= numMinor; ++j) {
	double a = j * minorStep;
	GLfloat x = radius * cos(a);
	GLfloat y = radius * sin(a);
	glVertex3f(x, y, z0);
	glVertex3f(x, y, z1);
	}
	glEnd();
	}
}
