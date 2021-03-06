#include <GL/gl.h>
#include "GameField.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

GameField::GameField() {
	this->fieldSize = 0;
}
GameField::~GameField(){
}
//zeichnet das grundlegende Spielfeld
void GameField::drawPlaine(float fieldSize) {
	this->fieldSize = fieldSize;
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(fieldSize, fieldSize, 0);
	glVertex3f(fieldSize, -fieldSize, 0);
	glVertex3f(-fieldSize, -fieldSize, 0);
	glVertex3f(-fieldSize, fieldSize, 0);
	glEnd();
}

void GameField::setFieldSize(float fieldSize) {
	this->fieldSize = fieldSize;
}

float GameField::getFieldSize() {
	return this->fieldSize;
}

