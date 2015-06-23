#include <GL/gl.h>
#include "GameField.h"
#include "ColorSetter.h"

class ObjectManager{
private:
	ColorSetter *colorSetter  = new ColorSetter();
	GameField *gameField = new GameField();
public:
	ObjectManager();
	~ObjectManager();
	void initGameField(float fieldSize);
};
