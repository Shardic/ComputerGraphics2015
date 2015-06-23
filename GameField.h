#include <GL/gl.h>

class GameField{
private:
	float fieldSize;
public:
	GameField();
	~GameField();
	void drawPlaine(float fieldSize);
	void setFieldSize(float fieldSize);
	float getFieldSize();
};
