#pragma once
#include <iostream>
#include <vector>
#include "PxPhysicsAPI.h"
#include "Physics/PhysicsScene.h"

using namespace physx;
using namespace std;

class PhysicsScene;
class PhysicsObject;

class Physics
{
public:
	~Physics();
	bool Init(bool connectToPvd = false);
	void createScene(float gravity = -9.81f);
	//Debug only
	void connectToPvd();

	PhysicsScene* getScene(int sceneId = 0);

	PxPhysics* getPhysics() 
	{
		return mPhysics;
	}
	PxCpuDispatcher* getCpuDispatcher() { return mDispatcher; }

private:
	vector<PhysicsScene*> scenes;

	//Startup
	PxDefaultAllocator		mAllocator;
	PxDefaultErrorCallback	mErrorCallback;

	PxFoundation* mFoundation = NULL;
	PxPhysics* mPhysics = NULL;

	PxDefaultCpuDispatcher* mDispatcher = NULL;

	PxPvd* mPvd = NULL;
	bool isConnectToPvd = false;
};

