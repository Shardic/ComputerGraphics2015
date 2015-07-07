#include <GL/gl.h>
#include <vector>
using namespace std;

class Goal{
private:
	double radius = 0.5;
public:
	Goal();
	~Goal();
	void drawGoal();
};
