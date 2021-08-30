#pragma once
#include<GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "VAO/VAO.h"

class Points
{
public:
	Points();
	void draw();
	void addPoint(glm::vec3 point);
private:

	std::vector<glm::vec3> points;
};

