#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Rectangle {
public:
	glm::vec2 lowerLeft;
	glm::vec2 upperRight;
	//Rectangle(glm::vec2 p1, glm::vec2 p2);
	//~Rectangle();
};

bool IsOverlapping(Rectangle r1, Rectangle r2);

Rectangle FlipRectangle(Rectangle r);
