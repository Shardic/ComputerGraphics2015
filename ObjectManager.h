#include <GL/gl.h>
#include "GameField.h"
#include "ColorSetter.h"
#include "Cylinder.h"
#include "Wall.h"
#include "GameBall.h"
#include <vector>

class ObjectManager{
private:
	double xCord =0;
	double yCord =0;
	double zCord =0;
	double rotateRightLeft =0;
	double rotateUpDown =0;
	double rotateZ =0;
	ColorSetter *colorSetter  = new ColorSetter();
	GameField *gameField = new GameField();
	bool fieldWallsCreated = false;
	GameBall *gameBall = new GameBall();
	std::vector<Cylinder> cylinderVector;
	std::vector<Wall> wallVector;
	std::vector<Wall> wallVectorBorders;
	std::vector<GameBall> ballsVector;
	Cylinder *endCylinder = new Cylinder();;
public:
	ObjectManager();
	~ObjectManager();
	void transRotateAllObjekts(double xcord, double ycord, double zcoord,
			double rotateRightLeft, double rotateUpDown, double rotateZ);
	void initGameField(float fieldSize);
	void drawGameBalls();
	void drawPlacedObjects();
	void setUsersWall(float x1, float y1, float x2, float y2);
	void setUserCylinder(double xPos, double yPos);
	void setUserSmallBall(double xPos, double yPos);
	void checkColision(); // evtl. gehört die kollisionserkennung in die move Methode
	void moveMovables(); //Soll den GameBall und die kleinen Bälle bewegen
	double doubleRand(double fMin, double fMax);
	bool positionIsOkay(double x, double y, double radius);
};
