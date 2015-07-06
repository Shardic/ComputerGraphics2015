#include <GL/gl.h>
#include "GameField.h"
#include "ColorSetter.h"
#include "Cylinder.h"
#include "Wall.h"
#include "GameBall.h"
#include "Goal.h"
#include <vector>

class ObjectManager{
private:
	double xCord =0;
	double yCord =0;
	double zCord =0;
	double rotateRightLeft =0;
	double rotateUpDown =0;
	double rotateZ =0;
	double extraBallPosX;
	double extraBallPosY;
	ColorSetter *colorSetter  = new ColorSetter();
	GameField *gameField = new GameField();
	bool fieldWallsCreated = false;
	GameBall *gameBall = new GameBall();
	Goal *goal = new Goal();
	std::vector<Cylinder> cylinderVector;
	std::vector<Wall> wallVector;
	std::vector<Wall> wallVectorBorders;
	std::vector<GameBall> ballsVector;
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
	void checkCollision(); // evtl. gehört die kollisionserkennung in die move Methode
	void moveMovables(); //Soll den GameBall und die kleinen Bälle bewegen
	double doubleRand(double fMin, double fMax);
	bool positionIsOkay(double x, double y, double radius);
	double getDistToWall(double cObjX, double cObjY, double wX1, double wY1, double wX2, double wY2);
	std::vector<double> closestPointOnLine(double lx1, double ly1, double lx2, double ly2, double x0, double y0);
	bool checkVictoryCondition();
	void drawEndScreen();
	void randomizeStartVec();
	void drawDirectionPointer();
};
