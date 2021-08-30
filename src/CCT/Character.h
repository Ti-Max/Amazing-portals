#pragma once
#include"../Object/Object.h"

struct CtrlDesc
{
	CtrlDesc(vec3 position, float height, float radius, float slopeLimit, float stepOffset = 0.02f, float contactOffset = 0.1f) :
		position(position),
		height(height),
		radius(radius),
		slopeLimit(slopeLimit),
		contactOffset(contactOffset),
		stepOffset(stepOffset)
	{}

	vec3 position;
	float height;
	float radius;
	float slopeLimit;
	float contactOffset = 0.1f;
	float stepOffset = 0.02f;

};

class Character : public Object
{
public:
	//Controller();
	void createController(PxControllerManager* manager, const CtrlDesc& desc);
	void setPxController(PxController* ctrl);

	void move(const vec3& move, float dt);

	void syncPhysics(const Transform& t) override;
private:
	PxController* ctrl;
	const PxControllerFilters filters;
};