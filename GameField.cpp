#include <GL/gl.h>
#include "GameField.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

GameField::GameField() {
}
GameField::~GameField(){
}
//zeichnet das Grundlegende Spielfeld
void GameField::drawPlaine(float fieldSize) {
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(fieldSize, fieldSize, -fieldSize);
	glVertex3f(fieldSize, -fieldSize, -fieldSize);
	glVertex3f(-fieldSize, -fieldSize, -fieldSize);
	glVertex3f(-fieldSize, fieldSize, -fieldSize);
	glEnd();
}

