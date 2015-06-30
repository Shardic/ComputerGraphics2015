#include <GL/gl.h>

class Wall{
private:
	float point1x=0;
	float point1y=0;
	float point2x=0;
	float point2y=0;
	float width = 1;
	float height = 2;
public:
	Wall();
	~Wall();
	void setWall(float x1, float y1, float x2, float y2);
	void drawWall();
	void drawWallPart();
	float getPoint1x();
	void setPoint1x(float point1x);
	float getPoint1y();
	void setPoint1y(float point1y);
	float getPoint2x();
	void setPoint2x(float point2x);
	float getPoint2y();
	void setPoint2y(float point2y);
};
