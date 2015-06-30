#include <GL/gl.h>
#include "GameBall.h"
#define _USE_MATH_DEFINES
#include <cmath>

GameBall::GameBall() {
}
GameBall::~GameBall(){
}
void GameBall::drawSphere(double r, int lats, int longs) {
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

	 	 glNormal3f(x * zr0*r, y * zr0*r, z0 *r);
	 	 glVertex3f(x * zr0*r, y * zr0*r, z0* r);
	 	 glNormal3f(x * zr1*r, y * zr1*r, z1*r);
	 	 glVertex3f(x * zr1*r, y * zr1*r, z1*r);
	 	 }
	 glEnd();
	 }
}
