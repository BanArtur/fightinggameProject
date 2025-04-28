#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct BoundingBox {
	glm::vec2 lowerLeft = glm::vec2(0,0);
	glm::vec2 upperRight = glm::vec2(0,0);
};

bool IsOverlapping(BoundingBox, BoundingBox);

BoundingBox FlipRectangle(BoundingBox);
