#include <GL/gl.h>
#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

ObjectManager::ObjectManager() {
}
ObjectManager::~ObjectManager(){
}

void ObjectManager::transRotateAllObjekts(double xCord, double yCord, double zCord,
		double rotateRightLeft, double rotateUpDown, double rotateZ) {
	this->xCord = xCord;
	this->yCord = yCord;
	this->zCord = zCord;
	this->rotateRightLeft = rotateRightLeft;
	this->rotateUpDown = rotateUpDown;
	this->rotateZ = rotateZ;
	glLoadIdentity();
	glTranslated(xCord, yCord, zCord);
	glRotated(rotateUpDown, 1, 0, 0);
	glRotated(rotateRightLeft, 0, 1, 0);
	glRotated(rotateZ,0,0,1);
}

//zeichnet nur das wirkliche GameField und deren Mauern
void ObjectManager::initGameField(float fieldSize) {
	//die Farbe des Feldes auf ein Gr�n setzen
	colorSetter->SetMaterialColor(2,0.2196,0.949,0.5843);
	//das Feld im GameUrsprung zeichnen
	gameField->drawPlaine(fieldSize);
	//Punkte und Speicher f�r die Mauern nur ein mal belegen:
	//Die Mauern werden in der Objekte zeichnen Funktion gezeichnet
	//, sonst w�re alles doppelt zu sehen.
	if(!fieldWallsCreated) {
		//Punkte f�r die Mauern erstellen
			float topRightX = fieldSize;	float topRightY = fieldSize;
			float bottomRightX = fieldSize;	float bottomRightY = fieldSize*-1;
			float bottomLeftX = fieldSize*-1; float bottomLeftY = fieldSize*-1;
			float topLeftX = fieldSize*-1; float topLeftY = fieldSize;
			//Die Mauern erstellen
			Wall *wallTop = new Wall();
			Wall *wallBottom = new Wall();
			Wall *wallLeft = new Wall();
			Wall *wallRight = new Wall();
			wallTop->setWall(topLeftX,topLeftY,topRightX, topRightY);
			wallRight->setWall(topRightX, topRightY, bottomRightX, bottomRightY);
			wallBottom->setWall(bottomRightX, bottomRightY, bottomLeftX, bottomLeftY);
			wallLeft->setWall(bottomLeftX, bottomLeftY, topLeftX,topLeftY);
			//die Mauern in den Vector pushen
			wallVectorBorders.push_back(*wallTop);		//Vectorstelle 3
			wallVectorBorders.push_back(*wallBottom);	//Vectorstelle 2
			wallVectorBorders.push_back(*wallLeft);	//Vectorstelle 1
			wallVectorBorders.push_back(*wallRight); //VectorStelle 0
			fieldWallsCreated = true;
	}
	//Danach jedes mal die Mauern zeichnen
	glPushMatrix();
	colorSetter->SetMaterialColor(2,1,0,0);
	colorSetter->SetMaterialColor(1,1,0,0);
	for (int i = 0; i < wallVectorBorders.size(); i++) {
		wallVectorBorders[i].drawWall();
	}
	glPopMatrix();
}

void ObjectManager::drawGameBalls() {
	//SpielKugel erstellen
	glPushMatrix(); // bei anderen Objekten an anderen Stellen immer pushen und poppen damit die Ursprungsposition des Fields bestehen bleibt
	colorSetter->SetMaterialColor(2,0.0,0.0,1.0);
	gameBall->drawSphere(); //TODO Bewegung der Kugel hier regeln und mit den Positionseigenschaten oder in der Kugel selbst ?
	glPopMatrix();
}

void ObjectManager::drawPlacedObjects() {
	//Alle W�nder vom Nutzer zeichnen
	glPushMatrix();
	// Ein etwas anderes Rot f�r die gesetzten Walls
	colorSetter->SetMaterialColor(2,0.5,0.1,0);
	colorSetter->SetMaterialColor(1,0.5,0.1,0);
	for (int i = 0; i < wallVector.size(); i++) {
		wallVector[i].drawWall();
	}
	glPopMatrix();
	//Alle Zylinder vom Nutzer zeichnen
	//Alle kleinen B�lle zeichnen
	glPushMatrix();
	//Die Zylinder sind gr�n
	colorSetter->SetMaterialColor(2,0,1,0);
	colorSetter->SetMaterialColor(1,0,1,0);
	for (int k = 0; k < cylinderVector.size(); k++) {
			cylinderVector[k].drawCylinder();
			//FUNKTIONIERT SOWEIT!
			//Zur�cksetzen der Game Welt, da die Zylinder die Welt beim zeichnen versetzen
			glLoadIdentity();
			this->transRotateAllObjekts(xCord,yCord,zCord,
				 rotateRightLeft, rotateUpDown, rotateZ);
		}
	glPopMatrix();
	glPushMatrix();
	//Die kleineren B�lle sind gelb
	colorSetter->SetMaterialColor(2,1,1,0);
	colorSetter->SetMaterialColor(1,1,1,0);
	for (int j = 0; j < ballsVector.size(); j++) {
		ballsVector[j].drawSphere();
		//Zur�cksetzen der Game Welt, da die B�lle die Welt beim zeichnen versetzen
		glLoadIdentity();
		this->transRotateAllObjekts(xCord,yCord,zCord,
			 rotateRightLeft, rotateUpDown, rotateZ);
	}
	glPopMatrix();
}

void ObjectManager::setUsersWall(float x1, float y1, float x2, float y2) {
	Wall *wall = new Wall();
	wall->setWall(x1, y1, x2, y2);
	wallVector.push_back(*wall);
}

void ObjectManager::setUserCylinder(double xPos, double yPos) {
	Cylinder *cylinder = new Cylinder();
	cylinderVector.push_back(*cylinder);
}

void ObjectManager::setUserSmallBall(double xPos, double yPos) {
	GameBall *smallBall = new GameBall();
	smallBall->setRadius(0.4);
	smallBall->setXPos(xPos);
	smallBall->setYPos(yPos);
	smallBall->rearangeZPos();
	ballsVector.push_back(*smallBall);
}

void ObjectManager::checkColision() {

}

void ObjectManager::moveMovables() {

}

