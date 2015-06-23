#include <GL/gl.h>
#include "GameField.h"

GameField::GameField() {
}
GameField::~GameField(){
}
//zeichnet das Grundlegende Spielfeld
void drawPlaine(float fieldSize) {
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(fieldSize/2.0f, fieldSize/2.0f, -fieldSize/2.0f);
	glVertex3f(fieldSize/2.0f, -fieldSize/2.0f, -fieldSize/2.0f);
	glVertex3f(-fieldSize/2.0f, -fieldSize/2.0f, -fieldSize/2.0f);
	glVertex3f(-fieldSize/2.0f, fieldSize/2.0f, -fieldSize/2.0f);
	glEnd();
}

