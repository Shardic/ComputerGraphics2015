/*
 * box.cpp
 *
 *  Created on: 21.04.2015
 *      Author: Marco
 */
#include <GL/gl.h>

class ObjectForProgramm {
private:
	bool open = true;
	double openAngle = 0.0;
	double accAngleBot = 0.0;
	double accAngleTop = 0.0;
public:
	ObjectForProgramm();
	~ObjectForProgramm();
	void setOpen(bool);
	void openCloseNormal();
	void openCloseAccordion(float kantenlaenge);
	void drawCubeWithoutTop(float kantenlaenge);
	void drawTopOfCube(float kantenlaenge);
	void drawTopAsAccordion(float kantenlaenge);
};


