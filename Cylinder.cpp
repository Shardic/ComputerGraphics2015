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
	glTranslated(xPos,yPos,zPos);
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

double Cylinder::getRadius() {
	return radius;
}
void Cylinder::setRadius(double r) {
	this->radius = r;
}

double Cylinder::getXPos() {
	return xPos;
}

void Cylinder::setXPos(double x) {
	this->xPos = x;
}

double Cylinder::getYPos() {
	return yPos;
}

void Cylinder::setYPos(double y) {
	this->yPos = y;
}

void Cylinder::rearangeZPos() {
	this->zPos = radius;
}
