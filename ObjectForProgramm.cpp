/*
 * box.cpp
 *
 *  Created on: 21.04.2015
 *      Author: Marco
 */
#include <GL/gl.h>
#include "ObjectForProgramm.h"

ObjectForProgramm::ObjectForProgramm() {
}
ObjectForProgramm::~ObjectForProgramm(){
}

void ObjectForProgramm::drawCubeWithoutTop(float kantenlaenge)
{
	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
	// front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(kantenlaenge/2.0f, -kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(kantenlaenge/2.0f, kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, -kantenlaenge/2.0f, kantenlaenge/2.0f);

	glEnd();

	glBegin(GL_QUADS);
	// right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(kantenlaenge/2.0f, kantenlaenge/2.0f, -kantenlaenge/2.0f);
	glVertex3f(kantenlaenge/2.0f, kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(kantenlaenge/2.0f, -kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(kantenlaenge/2.0f, -kantenlaenge/2.0f, -kantenlaenge/2.0f);

	glEnd();

	glBegin(GL_QUADS);
	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-kantenlaenge/2.0f, -kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, kantenlaenge/2.0f, -kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, -kantenlaenge/2.0f, -kantenlaenge/2.0f);

	glEnd();

	glBegin(GL_QUADS);
	// bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(kantenlaenge/2.0f, -kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, -kantenlaenge/2.0f, kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, -kantenlaenge/2.0f, -kantenlaenge/2.0f);
	glVertex3f(kantenlaenge/2.0f, -kantenlaenge/2.0f, -kantenlaenge/2.0f);

	glEnd();

	glBegin(GL_QUADS);
	// back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(kantenlaenge/2.0f, kantenlaenge/2.0f, -kantenlaenge/2.0f);
	glVertex3f(kantenlaenge/2.0f, -kantenlaenge/2.0f, -kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, -kantenlaenge/2.0f, -kantenlaenge/2.0f);
	glVertex3f(-kantenlaenge/2.0f, kantenlaenge/2.0f, -kantenlaenge/2.0f);

	glEnd();
}

void ObjectForProgramm::drawTopOfCube(float kantenlaenge) {
	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
	// top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-kantenlaenge/2.0f, 0, 0.0f);
	glVertex3f(-kantenlaenge/2.0f, kantenlaenge, 0);
	glVertex3f(kantenlaenge/2.0f, kantenlaenge, 0);
	glVertex3f(kantenlaenge/2.0f, 0, 0.0f);
	glEnd();
}

void ObjectForProgramm::drawTopAsAccordion(float kantenlaenge) {
	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
	// top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-kantenlaenge/2.0f, 0, 0.0f);
	glVertex3f(-kantenlaenge/2.0f, kantenlaenge/2, 0);
	glVertex3f(kantenlaenge/2.0f, kantenlaenge/2, 0);
	glVertex3f(kantenlaenge/2.0f, 0, 0.0f);
	glEnd();
}

void ObjectForProgramm::setOpen(bool isOpen) {
	open = isOpen;
}

void ObjectForProgramm::openCloseNormal() {
	if (open == true) {
		if (openAngle > 0.0) {
			openAngle -= 0.1;
		}
		glRotated(openAngle, 1,0,0);
	} else if (open == false) {
		if (openAngle < 90.0) {
			openAngle += 0.1;
		}
		glRotated(openAngle, 1,0,0);
	}
}

void ObjectForProgramm::openCloseAccordion(float kantenlaenge) {
	if (open == true) {
		if ((accAngleBot > 0.0)) {
			if (accAngleTop < 179.9) {
				accAngleTop += 0.1;
			} else {
				accAngleBot -= 0.1;
			}
		} else {
			if (accAngleTop > 0.0) {
				accAngleTop -= 0.1;
			}
		}
	} else if (open == false) {
		if ((accAngleBot < 90.0)) {
			if (accAngleTop < 179.9) {
				accAngleTop += 0.1;
			} else {
				accAngleBot += 0.1;
			}
		} else {
			if (accAngleTop > 0.0) {
				accAngleTop -= 0.1;
			}
		}
	}
	glRotated(accAngleBot,1,0,0);
	drawTopAsAccordion(kantenlaenge);
	glTranslated(0,kantenlaenge/2, 0);
	glRotated(accAngleTop,1,0,0);
	drawTopAsAccordion(kantenlaenge);
}
