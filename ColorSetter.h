#include <GL/gl.h>

class ColorSetter{
private:
public:
	ColorSetter();
	~ColorSetter();
	void SetMaterialColor(int side, double r, double g, double b);
};
