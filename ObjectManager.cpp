#include <GL/gl.h>
#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
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
				smallBall->setMoveVector(0.0, 0.0);
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
	smallBall->setMoveVector(0.0, 0.0);
	ballsVector.push_back(*smallBall);
}

void ObjectManager::checkCollision() {
/*
 * Distanz zwischen zwei Objekten berechnen
 * 	Dazu: die Movables einzelnd durchgehen
 * 		In dem durchgehen
 */
	//Game Ball mit den Zylindern kollidieren lassen
	double gBX = gameBall->getXPos();
	double gBY = gameBall->getYPos();
	double gBR = gameBall->getRadius();
	double collisionDistance = 0;
	for(int i = 0; i < cylinderVector.size(); i++) {
		double cX = cylinderVector[i].getXPos();
		double cY =	cylinderVector[i].getYPos();
		double cR =	cylinderVector[i].getRadius();
		double dX = gBX - cX;
		double dY = gBY - cY;
		collisionDistance = sqrt(((gBX - cX) * (gBX - cX)) + ((gBY - cY) * (gBY - cY)));
		if (collisionDistance <= gBR + cR) {
			//double vp = gameBall->getMoveVector()[0]*dX/collisionDistance + gameBall->getMoveVector()[1]*dY/collisionDistance;
			gameBall->setMoveVector(gameBall->getMoveVector()[0]*-2, gameBall->getMoveVector()[1]*-2);
			//TODO richtige Reflektion eingeben
		}
	}
	//Game Ball mit den Mauern kollidieren lassen
	for (int k = 0; k < wallVectorBorders.size(); k++) {
		double wX1 = wallVectorBorders[k].getPoint1x();
		double wY1 = wallVectorBorders[k].getPoint1y();
		double wX2 = wallVectorBorders[k].getPoint2x();
		double wY2 = wallVectorBorders[k].getPoint2y();
		double dist = this->getDistToWall(gBX, gBY, wX1, wY1, wX2, wY2);
		//cout << dist << endl;
		if (dist <= gBR) {
			//TODO Alle Ballvectoren ändern
			//double vp = gameBall->getMoveVector()[0]*dX/collisionDistance + gameBall->getMoveVector()[1]*dY/collisionDistance;
			gameBall->setMoveVector(0,0);
		}
	}

	for (int l = 0; l < wallVector.size(); l++) {

	}

	//Game Ball mit anderen Bällen kollidieren lassen
	for(int j = 0; j < ballsVector.size(); j++) {
		double cX = ballsVector[j].getXPos();
		double cY =	ballsVector[j].getYPos();
		double cR =	ballsVector[j].getRadius();
		double dX = gBX - cX;
		double dY = gBY - cY;
		collisionDistance = sqrt(((gBX - cX) * (gBX - cX)) + ((gBY - cY) * (gBY - cY)));
		if (collisionDistance <= gBR + cR) {
			//TODO Alle Ballvectoren ändern
			//double vp = gameBall->getMoveVector()[0]*dX/collisionDistance + gameBall->getMoveVector()[1]*dY/collisionDistance;
			gameBall->setMoveVector(gameBall->getMoveVector()[0]*dX/collisionDistance,gameBall->getMoveVector()[1]*dY/collisionDistance);
		}
	}
	//Alle anderen Bälle die gleiche Kolision durchlaufen
}

void ObjectManager::moveMovables() {
	gameBall->setXPos(gameBall->getXPos()+(gameBall->getMoveVector()[0]/gameBall->getMoveDelta()));
	gameBall->setYPos(gameBall->getYPos()+(gameBall->getMoveVector()[1]/gameBall->getMoveDelta()));
	for (int i = 0; i < ballsVector.size(); i++) {
		ballsVector[i].setXPos(ballsVector[i].getXPos()+(ballsVector[i].getMoveVector()[0]/ballsVector[i].getMoveDelta()));
		ballsVector[i].setYPos(ballsVector[i].getYPos()+(ballsVector[i].getMoveVector()[1]/ballsVector[i].getMoveDelta()));
	}
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



double ObjectManager::getDistToWall(double cObjX, double cObjY, double wX1, double wY1, double wX2, double wY2)
{
	vector<double> point (2);
	vector<double> linestart (2);
	//vector<double> tr = 1;
	//vector<double> dad = 2;
	//vector<double> xxx = dot(tr,dad);
	vector<double> lineend (2);

	point[0] = cObjX;
	point[1] = cObjY;

	linestart[0] = wX1;
	linestart[1] = wY1;

	lineend[0] = wX2;
	lineend[1] = wY2;


	vector<double > a (2);
	a[0] = lineend[0] - linestart[0];
	a[1] = lineend[1] - linestart[1];
	vector<double> b (2);
	b[0] = point[0] - linestart[0];
	b[0] = point[1] - linestart[1];
	double t = (a[0] * b[0] + a[1] * b[1]) /(a[0] * a[0] + a[1] * a[1]);

	cout << t << endl;
	if (t < 0) t = 0;
	if (t > 1) t = 1;

	vector<double> base (2);
	base [0] = linestart[0] + a[0] * t;
	base [1] = linestart[1] + a[1] * t;
	//cout << base[0] << endl;
	//cout << base[1] << endl;
	vector<double> diffVec (2);
	diffVec[0] = point[0] - base[0];
	diffVec[1] = point[1] - base[1];

	double dist = sqrt(diffVec[0]*diffVec[0] + diffVec[1] * diffVec[1]);

	return dist;
}

