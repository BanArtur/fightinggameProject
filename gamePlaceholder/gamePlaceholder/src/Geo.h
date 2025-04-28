#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Rectangle {
public:
	glm::vec2 lowerLeft;
	glm::vec2 upperRight;
};

bool IsOverlapping(Rectangle r1, Rectangle r2);

Rectangle FlipRectangle(Rectangle r);
