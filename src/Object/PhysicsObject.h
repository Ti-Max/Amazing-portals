#pragma once
#include "PxPhysicsAPI.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Object/Object.h"

#include "Physics/PhysicsScene.h"
#include "Physics/Physics.h"
#include "Transform/Transform.h"


#define MAX_NUM_ACTOR_SHAPES = 128;

using namespace physx;
using namespace std;
class Object;
class Physics;
class PhysicsScene;

enum ObjectType
{
	DYNAMIC,
	STATIC
};
enum ShapeType
{
	BOX,
	PLANE,
	SPHERE
};

class PhysicsObject
{
public:
	PhysicsObject();
	PhysicsObject(PhysicsScene* scene, ObjectType type);

	void setShapePlane(glm::vec4 plane);
	void setShapeBox(glm::vec3 box = vec3(0.5));

	void setMass(float mass);
	void setTransform(const Transform& t);
	//void setTransform(glm::vec3 pos, glm::quat rot);

	void setPhysicsScene(PhysicsScene* scene);

	void synchronizePhysics();
	void attachObject(Object* obj);
	Object* getAttachedObject();

	glm::mat4 getPose();
	glm::quat getRotation();
	//glm::vec4 getRotation();
	glm::vec3 getPosition();

private:
	Object* attachedObject = NULL;

	Transform lastTrans;

	PxRigidActor* actor;
	PhysicsScene* scene;
	PxPhysics* physics;
};

