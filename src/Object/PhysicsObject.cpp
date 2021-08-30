#include "PhysicsObject.h"
#include "Physics/PhysicsScene.h"



PhysicsObject::PhysicsObject(PhysicsScene* scene, ObjectType type)
{
	setPhysicsScene(scene);
	physics = &(scene->getPxScene()->getPhysics());
	switch (type)
	{
		case DYNAMIC:
		{
			actor = physics->createRigidDynamic(PxTransform(PxVec3(0, 0, 0)));
		}
			break;
	}

}

void PhysicsObject::setShapePlane(glm::vec4 plane)
{
	PxMaterial* gMaterial = physics->createMaterial(0.5f, 0.5f, 0.6f);
	actor = PxCreatePlane(*physics, PxPlane(plane.x, plane.y, plane.z, plane.w), *gMaterial);
	scene->getPxScene()->addActor(*actor);

}

void PhysicsObject::setShapeBox(glm::vec3 box)
{
	PxMaterial* gMaterial = physics->createMaterial(0.5f, 0.5f, 0.6f);
	PxRigidActorExt::createExclusiveShape(*actor, PxBoxGeometry(box.x, box.y, box.z), *gMaterial);
	scene->getPxScene()->addActor(*actor);

}

void PhysicsObject::setMass(float mass)
{
	PxRigidBodyExt::updateMassAndInertia(*(static_cast<PxRigidDynamic*>(actor)), mass);
}

void PhysicsObject::setTransform(const Transform& t)
{
	if (t.s != lastTrans.s)
	{
		PxU32 nb = actor->getNbShapes();
		PxShape* shapes[128];
		actor->getShapes(shapes, nb);
		for (int i = 0; i < nb; i++)
		{
			PxGeometryHolder geom = shapes[i]->getGeometry();
			switch (geom.getType())
			{
			case PxGeometryType::eSPHERE:
				geom.sphere().radius *= t.s.x;
				break;
			case PxGeometryType::eBOX:
				shapes[i]->setGeometry(PxBoxGeometry(t.s.x * 0.5, t.s.y * 0.5, t.s.z * 0.5));
				break;
			}
		}
	}
	

	actor->setGlobalPose(PxTransform(t.p.x, t.p.y, t.p.z, PxQuat(t.q.x, t.q.y, t.q.z, t.q.w)));
	lastTrans = t;
}

void PhysicsObject::setPhysicsScene(PhysicsScene* scene)
{
	this->scene = scene;
	scene->addObject(this);
}

void PhysicsObject::synchronizePhysics()
{
	//transform = 
	//glm::vec3 pos = getPosition();
	//glm::quat rot = getRotation();
	//getAttachedObject()->transform
	//getAttachedObject()->setRotation(rot);
}

void PhysicsObject::attachObject(Object* obj)
{
	setTransform(obj->getTransform());
	attachedObject = obj;
	actor->userData = attachedObject;
}

Object* PhysicsObject::getAttachedObject()
{
	return attachedObject;
}

glm::mat4 PhysicsObject::getPose()
{
	return glm::mat4();
}

glm::quat PhysicsObject::getRotation()
{
	PxQuat q = actor->getGlobalPose().q;

	return glm::quat(q.w, q.x, q.y, q.z);
}

glm::vec3 PhysicsObject::getPosition()
{
	PxVec3 p = actor->getGlobalPose().p;
	return glm::vec3(p.x, p.y, p.z);
}
