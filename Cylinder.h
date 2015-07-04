#include <GL/gl.h>

class Cylinder{
private:
	int numMajor = 150;
	int numMinor = 150;
	float height = 2;
	double radius = 0.5;
	double xPos = 0;
	double yPos = 0;
	double zPos = 1;
public:
	Cylinder();
	~Cylinder();
	void drawCylinder();
	double getXPos();
	void setXPos(double x);
	double getYPos();
	void setYPos(double y);
	double getRadius();
	void setRadius(double r);
	void rearangeZPos();
	void setHeight(double h);

};
