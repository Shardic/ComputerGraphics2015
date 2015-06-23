#include <GL/gl.h>
#include "GameField.h"
#include "ColorSetter.h"
#include "Cylinder.h"
#include "Wall.h"
#include <vector>

class ObjectManager{
private:
	ColorSetter *colorSetter  = new ColorSetter();
	GameField *gameField = new GameField();
	//std::Vector<Cylinder> cylinderVector;
	//std::Vector<Wall> wallVector;
public:
	ObjectManager();
	~ObjectManager();
	void initGameField(float fieldSize);
};
