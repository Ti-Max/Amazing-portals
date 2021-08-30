#include "PhysicsScene.h"

PhysicsScene::PhysicsScene(Physics* physics, float gravity)
{

	PxSceneDesc sceneDesc(physics->getPhysics()->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, gravity, 0.0f);

	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(4);
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	scene = physics->getPhysics()->createScene(sceneDesc);
	scene->setFlag(PxSceneFlag::eENABLE_ACTIVE_ACTORS, true);
}

PhysicsScene::~PhysicsScene()
{
	for (auto obj :objects)
	{
		if (obj != nullptr)
			delete obj; obj = nullptr;
	}
	objects.clear();

	scene->release();
}

void PhysicsScene::addObject(PhysicsObject* obj)
{
	objects.push_back(obj);
}

Transform PhysicsTransToMyTrans(const PxTransform& t, vec3 scale)
{
	return Transform(t.p.x, t.p.y, t.p.z, t.q.x, t.q.y, t.q.z, t.q.w, scale);
}

void PhysicsScene::Simulate(float dt)
{
	

	PxU32 nbActiveActors;
	PxActor** activeActors = scene->getActiveActors(nbActiveActors);

	for (PxU32 i = 0; i < nbActiveActors; ++i)
	{
		Object* realObject = static_cast<Object*>(activeActors[i]->userData);
		if (realObject) {
			if (activeActors[i]->getType() == PxActorType::eRIGID_DYNAMIC)
				realObject->syncPhysics(PhysicsTransToMyTrans((static_cast<PxRigidDynamic*>(activeActors[i]))->getGlobalPose(), realObject->getTransform().s));
			else if (activeActors[i]->getType() == PxActorType::eRIGID_STATIC) 
				realObject->syncPhysics(PhysicsTransToMyTrans((static_cast<PxRigidStatic*>(activeActors[i]))->getGlobalPose(), realObject->getTransform().s));
		}
	}
	scene->simulate(dt);

}
