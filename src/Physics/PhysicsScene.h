#pragma once
#include "PxPhysicsAPI.h"
#include <iostream>
#include <vector>

#include "Object/PhysicsObject.h"
#include "Physics/Physics.h"

class Physics;
class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene(Physics* physics, float gravity = -9.81f);
	~PhysicsScene();

	void addObject(PhysicsObject* obj);
	void Simulate(float dt);

	PxScene* getPxScene() { return scene; }
private:

	std::vector<PhysicsObject*> objects;
	PxScene* scene = NULL;
};

