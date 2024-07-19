#include "Geo.h"

bool IsOverlapping(Rectangle r1, Rectangle r2) {
	if (r1.lowerLeft.x == r1.upperRight.x || r1.lowerLeft.y == r1.upperRight.y || r2.lowerLeft.x == r2.upperRight.x || r2.lowerLeft.y == r2.upperRight.y) {
		return false;
	}
	if (r1.lowerLeft.x > r2.upperRight.x || r2.lowerLeft.x > r1.upperRight.x) {
		return false;
	}
	if (r1.lowerLeft.y > r2.upperRight.y || r2.lowerLeft.y > r1.upperRight.y) {
		return false;
	}
	return true;
}
Rectangle FlipRectangle(Rectangle r)
{
	Rectangle tmp;
	tmp.lowerLeft.x = r.upperRight.x * (-1);
	tmp.upperRight.x = r.lowerLeft.x * (-1);
	tmp.lowerLeft.y = r.lowerLeft.y;
	tmp.upperRight.y = r.upperRight.y;
	return tmp;
}
/*
Rectangle::Rectangle(glm::vec2 p1, glm::vec2 p2) {
	if (p2.x < p1.x || p2.y < p1.y) {
		lowerLeft = p2;
		upperRight = p1;
	}
	else {
		lowerLeft = p1;
		upperRight = p2;
	}
}

Rectangle::~Rectangle() {

}
*/