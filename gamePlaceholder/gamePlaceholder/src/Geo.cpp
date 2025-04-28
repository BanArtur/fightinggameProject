#include "Geo.h"

bool IsOverlapping(BoundingBox r1, BoundingBox r2) {
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
BoundingBox FlipRectangle(BoundingBox r)
{
	BoundingBox tmp;
	tmp.lowerLeft.x = r.upperRight.x * (-1);
	tmp.upperRight.x = r.lowerLeft.x * (-1);
	tmp.lowerLeft.y = r.lowerLeft.y;
	tmp.upperRight.y = r.upperRight.y;
	return tmp;
}