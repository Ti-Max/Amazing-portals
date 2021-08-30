#include "Object.h"
#include "CCT/Character.h"

Object::Object()
{

}

Object::~Object()
{
	//if (*renderObject)
	//	delete renderObject; renderObject = NULL;
	//if (physicsObject != NULL)
	//	delete physicsObject; physicsObject = NULL;
	//std::cout << "~Object()\n";
}

void Object::setRenderObject(RenderObjcect* obj)
{
	renderObject = obj;
}

void Object::setPhysicsObject(PhysicsObject* obj)
{
	obj->attachObject(this);
	physicsObject = obj;
}


void Object::syncPhysics(const Transform& t) 
{
	transform = t;
}

void Object::setTransform(const Transform& t)
{
	transform = t;
	if (physicsObject)
	{
		physicsObject->setTransform(t);
	}
}


void Object::draw(Shader *shader)
{
	renderObject->draw(shader, transform.getMatix());
}
