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

#define PI 3.14159265
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
	//Das Ziel wird gezeichnet
	glTranslated(-9,9,0.1);
	colorSetter->SetMaterialColor(1,0.1,0.5,0.2);
	colorSetter->SetMaterialColor(2,0.1,0.5,0.2);
	goal->drawGoal();
	glLoadIdentity();
	this->transRotateAllObjekts(xCord, yCord, zCord, rotateRightLeft,
			rotateUpDown, rotateZ);
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

			Cylinder *cylinder = new Cylinder();
			cylinder->setRadius(0.4);
			cylinder->setXPos(0);
			cylinder->setYPos(0);
			cylinder->rearangeZPos();
			cylinderVector.push_back(*cylinder);

			srand(time(NULL));
			for (int i = 0; i < 5; i++) {
				// cout << "Ball: " << i ;
			    do  {
			        randomX = doubleRand(1, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
					randomY = doubleRand(1, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
			    } while (!positionIsOkay(randomX, randomY, 5));

			    //cout << " at: " << randomX << " " << randomY << endl;
				GameBall *smallBall = new GameBall();
			    smallBall->setRadius(0.4);
			    smallBall->setXPos(randomX);
			    smallBall->setYPos(randomY);
			    smallBall->rearangeZPos();
				smallBall->setMoveVector(0.0, 0.0);
			    ballsVector.push_back(*smallBall);

			}for (int i = 0; i < 5; i++) {
				//cout << "Cylinder: " << i ;
			    do  {
			        randomX = doubleRand(1, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
					randomY = doubleRand(1, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
			    } while (!positionIsOkay(randomX, randomY, 3));

			   // cout << " at: " << randomX << " " << randomY << endl;
				Cylinder *cylinder = new Cylinder();
				cylinder->setRadius(0.4);
				cylinder->setXPos(randomX);
				cylinder->setYPos(randomY);
				cylinder->rearangeZPos();
				cylinderVector.push_back(*cylinder);

			}
			this->randomizeStartVec();

			fieldWallsCreated = true;
	}

	//Danach jedes mal die Mauern zeichnen
	glPushMatrix();
	colorSetter->SetMaterialColor(2,1,0,0);
	colorSetter->SetMaterialColor(1,1,0,0);
	for (unsigned int i = 0; i < wallVectorBorders.size(); i++) {
		wallVectorBorders[i].drawWall();
	}
	glPopMatrix();



}

void ObjectManager::drawGameBalls() {
	//SpielKugel erstellen
	glPushMatrix(); // bei anderen Objekten an anderen Stellen immer pushen und poppen damit die Ursprungsposition des Fields bestehen bleibt
	colorSetter->SetMaterialColor(2,0.0,0.0,1.0);
	gameBall->drawSphere();
	glPopMatrix();
}

void ObjectManager::drawPlacedObjects() {
	//Alle Wänder vom Nutzer zeichnen
	glPushMatrix();
	// Ein etwas anderes Rot für die gesetzten Walls
	colorSetter->SetMaterialColor(2,0.5,0.1,0);
	colorSetter->SetMaterialColor(1,0.5,0.1,0);
	for (unsigned int i = 0; i < wallVector.size(); i++) {
		wallVector[i].drawWall();
	}
	glPopMatrix();
	//Alle Zylinder vom Nutzer zeichnen
	//Alle kleinen Bälle zeichnen
	glPushMatrix();
	//Die Zylinder sind grün
	colorSetter->SetMaterialColor(2,1,1,1);
	colorSetter->SetMaterialColor(1,1,1,1);
	for (unsigned int k = 0; k < cylinderVector.size(); k++) {
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
	for (unsigned int j = 0; j < ballsVector.size(); j++) {
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

	// GameBall kollidiert mit den Zylindern
	for(unsigned int i = 0; i < cylinderVector.size(); i++) {
		double cX = cylinderVector[i].getXPos();
		double cY =	cylinderVector[i].getYPos();
		double cR =	cylinderVector[i].getRadius();
		//Abstand zwischen Cylindermittelpunkt und Spielballmittelpunkt
		collisionDistance = sqrt(((gBX - cX) * (gBX - cX)) + ((gBY - cY) * (gBY - cY)));
		if (collisionDistance <= gBR + cR) {
			//double vp = gameBall->getMoveVector()[0]*dX/collisionDistance + gameBall->getMoveVector()[1]*dY/collisionDistance;
			//gameBall->setMoveVector(gameBall->getMoveVector()[0]*-2, gameBall->getMoveVector()[1]*-2);
			vector<double> actualMovevector (2);
			actualMovevector = gameBall->getMoveVector();

			gameBall->setMoveVector(-actualMovevector[0],-actualMovevector[1]);
			/*vector<double> moveVectorGB (2);
						moveVectorGB = gameBall->getMoveVector();
						vector<double> moveVectorB (2);
						moveVectorB = ballsVector[j].getMoveVector();

						//Velocity Gameball
						double newVelXGB = (moveVectorGB[0] * (gBR - cR) + (2 * cR * moveVectorB[0])) / (gBR + cR);
						double newVelYGB = (moveVectorGB[1] * (gBR - cR) + (2 * cR * moveVectorB[1])) / (gBR + cR);

						//Velocity Ball
						double newVelXB = (moveVectorB[0] * (cR - gBR) + (2 * gBR * moveVectorGB[0])) / (gBR + cR);
						double newVelYB = (moveVectorB[1] * (cR - gBR) + (2 * gBR * moveVectorGB[1])) / (gBR + cR);

						gameBall->setMoveVector(newVelXGB, newVelYGB);
						ballsVector[j].setMoveVector(newVelXB, newVelYB);*/
			}
		//kleiner Bälle mit den zylindern kollidieren lassen
		for (unsigned int p = 0; p < ballsVector.size(); p++) {
			double collisionDistanceToZylinder = sqrt(((ballsVector[p].getXPos() - cX) *
					(ballsVector[p].getXPos() - cX)) +
					((ballsVector[p].getYPos() - cY) *
							(ballsVector[p].getYPos() - cY)));
			if (collisionDistanceToZylinder <= (ballsVector[p].getRadius() + cR)) {
				vector<double> moveVec (2);
				moveVec = ballsVector[p].getMoveVector();

				ballsVector[p].setMoveVector(-moveVec[0],-moveVec[1]);
			}
		}
	}


	//Game Ball mit den Außenmauern kollidieren lassen
	for (unsigned int k = 0; k < wallVectorBorders.size(); k++) {
		double wX1 = wallVectorBorders[k].getPoint1x();
		double wY1 = wallVectorBorders[k].getPoint1y();
		double wX2 = wallVectorBorders[k].getPoint2x();
		double wY2 = wallVectorBorders[k].getPoint2y();
		//Distanz zwischen Mauer und SpielBall
		double dist = this->getDistToWall(gBX, gBY, wX1, wY1, wX2, wY2);
		if (dist <= gBR) {
			vector<double> actualMovevector (2);
			actualMovevector = gameBall->getMoveVector();
			if (wX1 == wX2) {
				gameBall->setMoveVector(-actualMovevector[0],actualMovevector[1]);
			}
			if (wY1 == wY2) {
				gameBall->setMoveVector(actualMovevector[0],-actualMovevector[1]);
			}

		}
		//Kleine Bälle mit den Außenmauern kollidieren lassen
		for(unsigned int m = 0; m < ballsVector.size(); m++) {
			double bX = ballsVector[m].getXPos();
			double bY =	ballsVector[m].getYPos();
			double bR =	ballsVector[m].getRadius();
			//Distanz zwischen Mauer und Ball
			double distToWall = this->getDistToWall(bX, bY, wX1, wY1, wX2, wY2);
			if (distToWall <= bR) {
				//Movevector ball
				vector<double> actualMovevector (2);
				actualMovevector = ballsVector[m].getMoveVector();
				//Abfrage ob Außenmauern Waagerecht oder Senkrecht sind
				if (wX1 == wX2) {
					ballsVector[m].setMoveVector(-actualMovevector[0],actualMovevector[1]);
				}
				if (wY1 == wY2) {
					ballsVector[m].setMoveVector(actualMovevector[0],-actualMovevector[1]);
				}
			}
		}
	}

	//Game Ball mit den gesetzten Mauern kollidieren lassen
	for (unsigned int l = 0; l < wallVector.size(); l++) {
		double wX1 = wallVector[l].getPoint1x();
		double wY1 = wallVector[l].getPoint1y();
		double wX2 = wallVector[l].getPoint2x();
		double wY2 = wallVector[l].getPoint2y();
		double dist = this->getDistToWall(gBX, gBY, wX1, wY1, wX2, wY2);
		//Prüft ob Distanz größer kleiner gleich Radius des Spielballes
		if (dist <= gBR) {
			//Movevector gameball
			vector<double> actualMovevector (2);
			actualMovevector = gameBall->getMoveVector();

			//Schnittpunkt auf der Mauer wenn Ball mit Mauer kollidiert
			vector<double> closestPointOnLine (2);
			closestPointOnLine = this->closestPointOnLine(wX1, wY1, wX2, wY2, gBX, gBY);


			vector<double> n (2);
			n[0] = closestPointOnLine[0] - gBX;
			n[1] = closestPointOnLine[1] - gBY;

			double nDotProduct = (n[0] * n[0]) + (n[1] * n[1]);
			//Länge des Vektors
			double distance = sqrt(nDotProduct);
			n[0] = n[0]/distance;
			n[1] = n[1]/distance;

			double vn = (n[0] * n[0]) + (n[1] * n[1]);

			vector<double> newMovevector (2);
			newMovevector[0] = actualMovevector[0] - ((2 * vn) * n[0]);
			newMovevector[1] = actualMovevector[1] - ((2 * vn) * n[1]);

			gameBall->setMoveVector(newMovevector[0],newMovevector[1]);
		}

		//Kleine Bälle mit den gesetzten Mauern Kollidieren lassen
		for(unsigned int p = 0; p < ballsVector.size(); p++) {
				double cX = ballsVector[p].getXPos();
				double cY =	ballsVector[p].getYPos();
				double cR =	ballsVector[p].getRadius();
				double distance = this->getDistToWall(cX, cY, wX1, wY1, wX2, wY2);
				if (distance <= cR) {

					vector<double> moveVectorB (2);
					moveVectorB = ballsVector[p].getMoveVector();

					//Schnittpunkt auf der Mauer wenn Ball mit Mauer kollidiert
								vector<double> closestPointOnLine1 (2);
								closestPointOnLine1 = this->closestPointOnLine(wX1, wY1, wX2, wY2, cX, cY);


								vector<double> n (2);
								n[0] = closestPointOnLine1[0] - gBX;
								n[1] = closestPointOnLine1[1] - gBY;

								double nDotProduct = (n[0] * n[0]) + (n[1] * n[1]);
								//Länge des Vektors
								double distance = sqrt(nDotProduct);
								n[0] = n[0]/distance;
								n[1] = n[1]/distance;

								double vn = (n[0] * n[0]) + (n[1] * n[1]);

								vector<double> newMovevector (2);
								newMovevector[0] = moveVectorB[0] - ((2 * vn) * n[0]);
								newMovevector[1] = moveVectorB[1] - ((2 * vn) * n[1]);

								ballsVector[p].setMoveVector(newMovevector[0],newMovevector[1]);
				}
		}
	}

	//Game Ball mit anderen Bällen kollidieren lassen
	for(unsigned int j = 0; j < ballsVector.size(); j++) {
		double cX = ballsVector[j].getXPos();
		double cY =	ballsVector[j].getYPos();
		double cR =	ballsVector[j].getRadius();
		collisionDistance = sqrt(((gBX - cX) * (gBX - cX)) + ((gBY - cY) * (gBY - cY)));
		if (collisionDistance <= gBR + cR) {

			vector<double> moveVectorGB (2);
			moveVectorGB = gameBall->getMoveVector();
			vector<double> moveVectorB (2);
			moveVectorB = ballsVector[j].getMoveVector();

			//Velocity Gameball
			double newVelXGB = (moveVectorGB[0] * (gBR - cR) + (2 * cR * moveVectorB[0])) / (gBR + cR);
			double newVelYGB = (moveVectorGB[1] * (gBR - cR) + (2 * cR * moveVectorB[1])) / (gBR + cR);

			//Velocity Ball
			double newVelXB = (moveVectorB[0] * (cR - gBR) + (2 * gBR * moveVectorGB[0])) / (gBR + cR);
			double newVelYB = (moveVectorB[1] * (cR - gBR) + (2 * gBR * moveVectorGB[1])) / (gBR + cR);

			gameBall->setMoveVector(newVelXGB, newVelYGB);
			ballsVector[j].setMoveVector(newVelXB, newVelYB);

		}

		for(unsigned int o = 0; o < ballsVector.size(); o++) {
				double bX = ballsVector[o].getXPos();
				double bY =	ballsVector[o].getYPos();
				double bR =	ballsVector[o].getRadius();
				collisionDistance = sqrt(((cX - bX) * (cX - bX)) + ((cY - bY) * (cY - bY)));
				if ((collisionDistance <= bR + cR) && (o != j)) {

					vector<double> actualMovevectorBB (2);
					actualMovevectorBB = ballsVector[j].getMoveVector();
					vector<double> actualMovevectorB (2);
					actualMovevectorB = ballsVector[o].getMoveVector();

					//Velocity Gameball
					double newVelXB1 = (actualMovevectorBB[0] - (actualMovevectorBB[0] * 1/2));
					double newVelYB1 = (actualMovevectorBB[1] - (actualMovevectorBB[1] * 1/2));

					//Velocity Ball
					double newVelXB2 = (actualMovevectorB[0] + (actualMovevectorBB[0] * 1/2));
					double newVelYB2 = (actualMovevectorB[1] + (actualMovevectorBB[1] * 1/2));

					//cout << newVelXB1 << " " << newVelYB1 << "Ursprungsball neue Vel" << endl;
					//cout << newVelXB2 << " " << newVelYB2 << "neuer Ball neue Vel" << endl;
					ballsVector[j].setMoveVector(-newVelXB1, -newVelYB1);
					ballsVector[o].setMoveVector(newVelXB2, newVelYB2);
					//cout << ballsVector[j].getMoveVector()[0] << ballsVector[j].getMoveVector()[1] << "gespeicherter Vector Ursprungsball" << endl;

					}
		}
	}

	// Kleinere Bälle mit den zylindern
}

void ObjectManager::moveMovables() {
	gameBall->setXPos(gameBall->getXPos()+(gameBall->getMoveVector()[0]/gameBall->getMoveDelta()));
	gameBall->setYPos(gameBall->getYPos()+(gameBall->getMoveVector()[1]/gameBall->getMoveDelta()));
	for (unsigned int i = 0; i < ballsVector.size(); i++) {
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
	for (unsigned int i = 0; i < ballsVector.size() ; i++) {
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
	for (unsigned int j = 0; j < cylinderVector.size(); j++) {
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
	b[1] = point[1] - linestart[1];

	double c1 = a[0] * b[0] + a[1] * b[1];

	if (c1<=0) {
		return sqrt(((point[0] - linestart[0]) * (point[0] - linestart[0])) + ((point[1] - linestart[1]) * (point[1] - linestart[1])));
	}

	double c2 = a[0] * a[0] + a[1] * a[1];
	if (c2<=c1) {
		return sqrt(((point[0] - lineend[0]) * (point[0] - lineend[0])) + ((point[1] - lineend[1]) * (point[1] - lineend[1])));
	}

	double be = c1/c2;

	vector<double> pb (2);
	pb [0] = linestart[0] + (be * a[0]);
	pb [1] = linestart[1] + (be * a[1]);

	return sqrt(((point[0] - pb[0]) * (point[0] - pb[0])) + ((point[1] - pb[1]) * (point[1] - pb[1])));

}

std::vector<double> ObjectManager::closestPointOnLine(double lx1, double ly1, double lx2, double ly2, double x0, double y0){
      double A1 = ly2 - ly1;
      double B1 = lx1 - lx2;
      double C1 = (ly2 - ly1)*lx1 + (lx1 - lx2)*ly1;
      double C2 = (-B1*x0) + (A1*y0);
      double det = (A1*A1) - (-B1*B1);
      double cx = 0;
      double cy = 0;
      if(det != 0){
            cx = (((A1*C1) - (B1*C2))/det);
            cy = (((A1*C2) - (-B1*C1))/det);
      }else{
            cx = x0;
            cy = y0;
      }
      vector<double> closestPoint (2);
      closestPoint[0] = cx;
      closestPoint[1] = cy;
      return closestPoint;
}

void ObjectManager::drawEndScreen() {
	cout << "Spiel ist gewonnen worden!" << endl;
}

void ObjectManager::randomizeStartVec() {
	srand(time(NULL));
	bool directionUpToLeft = false;
	double xDirection = 0;
	double yDirection = 0;
	do {
		xDirection = doubleRand(0, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
		if (xDirection <= 0) {
			directionUpToLeft = true;
		}
	} while (!directionUpToLeft);
	directionUpToLeft = false;
	do {
		yDirection = doubleRand(0, gameField->getFieldSize()*2-1) -gameField->getFieldSize();
		if (yDirection >= 0) {
			directionUpToLeft = true;
		}
	} while (!directionUpToLeft);
	this->gameBall->setMoveVector(xDirection, yDirection);
//	this->gameBall->setMoveVector(-9, 9);
}

void ObjectManager::drawDirectionPointer() {
	glTranslated(this->gameBall->getXPos(),this->gameBall->getYPos(),0.1);
	vector<double> direction = gameBall->getMoveVector();
	double pointToX = direction[0] / 5;
	double pointToY = direction[1] / 5;
	colorSetter->SetMaterialColor(1,0.1,0.5,0.2);
	colorSetter->SetMaterialColor(2,0.1,0.5,0.2);
	glBegin(GL_TRIANGLES);
	glVertex3f(pointToX, pointToY, 0);
	glVertex3f(-1,-1, 0);
	glVertex3f(1,1, 0);
	glEnd();
	glLoadIdentity();
	this->transRotateAllObjekts(xCord, yCord, zCord, rotateRightLeft,
			rotateUpDown, rotateZ);
}

bool ObjectManager::checkVictoryCondition() {
	vector<double> pos (2);
	pos[0] = gameBall->getXPos();
	pos[1] = gameBall->getYPos();
	double distanceToGoal = sqrt(((pos[0] - (-9)) * (pos[0] - (-9))) + ((pos[1] - 9) * (pos[1] - 9)));
	if (distanceToGoal <= (gameBall->getRadius()*1.2)) {
		return true;
	}
	return false;
}

