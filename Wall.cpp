#include <GL/gl.h>
#include "Wall.h"

Wall::Wall() {
}
Wall::~Wall(){
}

void Wall::drawWall(float x1, float y1, float x2, float y2){
	this->setPoint1x(x1);
	this->setPoint1y(y1);
	this->setPoint2x(x2);
	this->setPoint2y(y2);
}

float Wall::getPoint1x(){
	return this->point1x;
}
void Wall::setPoint1x(float point1x){
	this->point1x = point1x;
}
float Wall::getPoint1y(){
	return this->point1y;
}
void Wall::setPoint1y(float point1y){
	this->point1y = point1y;
}
float Wall::getPoint2x(){
	return this->point2x;
}
void Wall::setPoint2x(float point2x){
	this->point2x = point2x;
}
float Wall::getPoint2y(){
	return this->point2y;
}
void Wall::setPoint2y(float point2y){
	this->point2y = point2y;
}
