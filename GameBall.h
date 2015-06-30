#include <GL/gl.h>

class GameBall{
private:
	//Die Positionen beziehen sich hierbei auf den Urpsurng des GameFields!
	double radius = 0.5;
	int lats = 20;
	int longs = 20;
	double xPos = 9;
	double yPos = -9;
	double zPos = radius;
	//Gradzahl in die der Ball rollt,
	//0 Grad ist dabei in Richtung y+1 und x+-0
	//90 Grad ist y+-0 und x+1, 180 Grad y-1 und x+-0 etc. etc.
	int directionDegree = 0;
	double speed = 0;
public:
	GameBall();
	~GameBall();
	void drawSphere();
	double getRadius();
	double getXPos();
	double getYPos();
	double getZPos();
};
