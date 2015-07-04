#include <GL/gl.h>
#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
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
	double randomX;
	double randomY;
	//die Farbe des Feldes auf ein Grün setzen
	colorSetter->SetMaterialColor(2,0.2196,0.949,0.5843);
	//das Feld im GameUrsprung zeichnen
	gameField->drawPlaine(fieldSize);
	//Punkte und Speicher für die Mauern nur ein mal belegen:
	//Die Mauern werden in der Objekte zeichnen Funktion gezeichnet
	//, sonst wäre alles doppelt zu sehen.
	if(!fieldWallsCreated) {
		//Punkte für die Mauern erstellen
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

			endCylinder->setRadius(0.4);
			endCylinder->setXPos(-9);
			endCylinder->setYPos(9);
			endCylinder->setHeight(0.1);
			endCylinder->rearangeZPos();

			Cylinder *cylinder = new Cylinder();
			cylinder->setRadius(0.4);
			cylinder->setXPos(0);
			cylinder->setYPos(0);
			cylinder->rearangeZPos();
			cylinderVector.push_back(*cylinder);

			srand(time(NULL));
			for (int i = 0; i < 5; i++) {
				cout << "Ball: " << i ;
			    do  {
			        randomX = doubleRand(1, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
					randomY = doubleRand(1, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
			    } while (!positionIsOkay(randomX, randomY, 5));

			    cout << " at: " << randomX << " " << randomY << endl;
				GameBall *smallBall = new GameBall();
			    smallBall->setRadius(0.4);
			    smallBall->setXPos(randomX);
			    smallBall->setYPos(randomY);
			    smallBall->rearangeZPos();
			    ballsVector.push_back(*smallBall);

			}for (int i = 0; i < 5; i++) {
				cout << "Cylinder: " << i ;
			    do  {
			        randomX = doubleRand(1, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
					randomY = doubleRand(1, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
			    } while (!positionIsOkay(randomX, randomY, 3));

			    cout << " at: " << randomX << " " << randomY << endl;
				Cylinder *cylinder = new Cylinder();
				cylinder->setRadius(0.4);
				cylinder->setXPos(randomX);
				cylinder->setYPos(randomY);
				cylinder->rearangeZPos();
				cylinderVector.push_back(*cylinder);

			}

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
	//Alle Wänder vom Nutzer zeichnen
	glPushMatrix();
	// Ein etwas anderes Rot für die gesetzten Walls
	colorSetter->SetMaterialColor(2,0.5,0.1,0);
	colorSetter->SetMaterialColor(1,0.5,0.1,0);
	for (int i = 0; i < wallVector.size(); i++) {
		wallVector[i].drawWall();
	}
	glPopMatrix();
	//Alle Zylinder vom Nutzer zeichnen
	//Alle kleinen Bälle zeichnen
	glPushMatrix();
	//Die Zylinder sind grün
	colorSetter->SetMaterialColor(2,1,1,1);
	colorSetter->SetMaterialColor(1,1,1,1);
	endCylinder->drawCylinder();
	for (int k = 0; k < cylinderVector.size(); k++) {
			cylinderVector[k].drawCylinder();
			//FUNKTIONIERT SOWEIT!
			//Zurücksetzen der Game Welt, da die Zylinder die Welt beim zeichnen versetzen
			glLoadIdentity();
			this->transRotateAllObjekts(xCord,yCord,zCord,
				 rotateRightLeft, rotateUpDown, rotateZ);
		}
	glPopMatrix();
	glPushMatrix();
	//Die kleineren Bälle sind gelb
	colorSetter->SetMaterialColor(2,1,1,0);
	colorSetter->SetMaterialColor(1,1,1,0);
	for (int j = 0; j < ballsVector.size(); j++) {
		ballsVector[j].drawSphere();
		//Zurücksetzen der Game Welt, da die Bälle die Welt beim zeichnen versetzen
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
	cylinder->setRadius(0.4);
	cylinder->setXPos(xPos);
	cylinder->setYPos(yPos);
	cylinder->rearangeZPos();
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

double ObjectManager::doubleRand(double fMin, double fMax)  {
	double nmr = fmod((double)rand(), fMax) + fMin;
	//cout << nmr << endl;
	return nmr;

}

bool ObjectManager::positionIsOkay(double x, double y, double radius) {
	bool isOkay = true;
	for (int i = 0; i < ballsVector.size() ; i++) {
		if (ballsVector[i].getXPos()-x >= radius || ballsVector[i].getXPos()-x <= radius*(-1)
				|| ballsVector[i].getYPos()-y >= radius || ballsVector[i].getYPos()-y <= radius*(-1)) {
			if (x >= 6 && y <= -6) {
				isOkay = false;
			}
			if (x <= -6 && y >= 6) {
				isOkay = false;
			}
		}else {
			isOkay = false;
		}
	}
	for (int j = 0; j < cylinderVector.size(); j++) {
		if (cylinderVector[j].getXPos()-x >= radius || cylinderVector[j].getXPos()-x <= radius*(-1)
				|| cylinderVector[j].getYPos()-y >= radius || cylinderVector[j].getYPos()-y <= radius*(-1)) {
			if (x >= 6 && y <= -6) {
				isOkay = false;
			}
			if (x <= -6 && y >= 6) {
				isOkay = false;
			}
		}else {
			isOkay = false;
		}
	}
	return isOkay;
}


