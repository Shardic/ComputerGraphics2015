#include <GL/gl.h>
#include "GameBall.h"
#define _USE_MATH_DEFINES
#include <cmath>

GameBall::GameBall() {
}
GameBall::~GameBall(){
}
void GameBall::drawSphere() {
	glTranslated(xPos,yPos,zPos);
	int i, j;
	 for(i = 1; i <= lats; i++) {
		 double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
		 double z0  = sin(lat0);
		 double zr0 =  cos(lat0);

		 double lat1 = M_PI * (-0.5 + (double) i / lats);
		 double z1 = sin(lat1);
		 double zr1 = cos(lat1);

		 glBegin(GL_QUAD_STRIP);
		 for(j = 0; j <= longs; j++) {
		 double lng = 2 * M_PI * (double) (j - 1) / longs;
		 double x = cos(lng);
		 double y = sin(lng);

	 	 glNormal3f(x * zr0*radius, y * zr0*radius, z0 *radius);
	 	 glVertex3f(x * zr0*radius, y * zr0*radius, z0* radius);
	 	 glNormal3f(x * zr1*radius, y * zr1*radius, z1*radius);
	 	 glVertex3f(x * zr1*radius, y * zr1*radius, z1*radius);
	 	 }
	 glEnd();
	 }
}

double GameBall::getRadius() {
	return radius;
}

double GameBall::getXPos() {
	return xPos;
}

double GameBall::getYPos() {
	return yPos;
}

double GameBall::getZPos() {
	return zPos;
}
