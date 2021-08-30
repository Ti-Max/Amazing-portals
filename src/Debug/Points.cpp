#include "Points.h"

Points::Points()
{
}

void Points::draw(){
	GL::VAO vao;
	vao.addBufferData(points);
	vao.drawPoints(points.size());
}

void Points::addPoint(glm::vec3 point)
{
	points.push_back(point);
}
