#include "Physics.h"

#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL;	}


Physics::~Physics()
{
    for (auto scene : scenes)
    {
        PxScene* s = scene->getPxScene();
        PX_RELEASE(s);
    }
    PX_RELEASE(mDispatcher);
    PX_RELEASE(mPhysics);
    if (mPvd)
    {
        PxPvdTransport* transport = mPvd->getTransport();
        mPvd->release();	mPvd = NULL;
        PX_RELEASE(transport);
    }
    PX_RELEASE(mFoundation);

    printf("~Physics()\n");

}

bool Physics::Init(bool connectToPvd)
{
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mAllocator, mErrorCallback);
    if (!mFoundation)
        return false;

    if (connectToPvd)
    {
        isConnectToPvd = true;
        mPvd = PxCreatePvd(*mFoundation);
        PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        mPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
    }
    //PHYSICS
    bool recordMemoryAllocations = true;

    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(), true, mPvd);
    if (!mPhysics)
        return false;

	return true;
}

void Physics::createScene(float gravity)
{
  
    PhysicsScene* scene = new PhysicsScene(this, gravity);

    scenes.push_back(scene);

    if (isConnectToPvd)
        connectToPvd();
}

void Physics::connectToPvd()
{

    PxPvdSceneClient* pvdClient = scenes.at(0)->getPxScene()->getScenePvdClient();
    if (pvdClient)
    {
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }
}

PhysicsScene* Physics::getScene(int sceneId)
{
    return scenes.at(sceneId);
}

