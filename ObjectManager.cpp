#include <GL/gl.h>
#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>

ObjectManager::ObjectManager() {
}
ObjectManager::~ObjectManager(){
}
void ObjectManager::initGameField(float fieldSize) {
	colorSetter->SetMaterialColor(1,1.0,0.0,0.0);
	gameField->drawPlaine(fieldSize);
//	this->colorSetter.SetMaterialColor(1,1,1,1);
//	this->gameField.drawPlaine(fieldSize);
}
