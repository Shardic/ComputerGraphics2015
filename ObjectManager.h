#include <GL/gl.h>
#include "GameField.h"
#include "ColorSetter.h"
#include "Cylinder.h"
#include "Wall.h"
#include "GameBall.h"
#include <vector>

class ObjectManager{
private:
	ColorSetter *colorSetter  = new ColorSetter();
	GameField *gameField = new GameField();
	bool fieldWallsCreated = false;
	GameBall *gameBall = new GameBall();
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
	void drawPlacedObjects();
	void drawGameBalls();
	void checkColision();
};
