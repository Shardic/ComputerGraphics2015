#include <GL/gl.h>
#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>

ObjectManager::ObjectManager() {
}
ObjectManager::~ObjectManager(){
}
void ObjectManager::initGameField(float fieldSize) {
	glLoadIdentity();
	glTranslated(0, 0, -25);
	colorSetter->SetMaterialColor(2,0.2196,0.949,0.5843);
	gameField->drawPlaine(fieldSize);
}
