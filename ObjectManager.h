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
	GameBall *gameBall = new GameBall();
	std::vector<Cylinder> cylinderVector;
	std::vector<Wall> wallVector;
public:
	ObjectManager();
	~ObjectManager();
	void transRotateAllObjekts(double xcord, double ycord, double zcoord,
			double rotateRightLeft, double rotateUpDown, double rotateZ);
	void initGameField(float fieldSize);
};
