#include <GL/gl.h>
#include "ObjectManager.h"
#include <stdlib.h>
#include <stdio.h>

ObjectManager::ObjectManager() {
}
ObjectManager::~ObjectManager(){
}
void ObjectManager::transRotateAllObjekts(double xCord, double yCord, double zCord,
		double rotateRightLeft, double rotateUpDown, double rotateZ) {
	glLoadIdentity();
	glTranslated(xCord, yCord, zCord);
	glRotated(rotateUpDown, 1, 0, 0);
	glRotated(rotateRightLeft, 0, 1, 0);
	glRotated(rotateZ,0,0,1);
}
void ObjectManager::initGameField(float fieldSize) {
	//die Farbe des Feldes auf ein Gr�n setzen
	colorSetter->SetMaterialColor(2,0.2196,0.949,0.5843);
	//das Feld zeichnen
	gameField->drawPlaine(fieldSize);
	//Punkte f�r die Mauern errechnen und speichern
	//Zwischen den Eckpunkten Mauern erstellen
	//Kugel erstellen (20/20 muss noch mal geschaut werden ob wir eine AUfloesung implementieren usw....
	//Vorher muss die Kugel noch zu einer Bestimmten Position gebracht werden
	glTranslated(9,9,0.5);
	gameBall->drawSphere(0.5,20,50);
	//Ziel erstellen
}
