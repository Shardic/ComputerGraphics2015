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
	// Bewegung muss irgendwie mit richtungsvektoren implementiert werden
public:
	GameBall();
	~GameBall();
	void drawSphere();
	double getRadius();
	void setRadius(double r);
	double getXPos();
	void setXPos(double x);
	double getYPos();
	void setYPos(double y);
	double getZPos();
	//Zur sicherheit, da man den Radius geaendert hat
	void rearangeZPos();
};
