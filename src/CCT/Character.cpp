#include "Character.h"

void Character::createController(PxControllerManager* manager, const CtrlDesc& desc)
{
	PxCapsuleControllerDesc PxDesc;

	PxDesc.material = manager->getScene().getPhysics().createMaterial(0.5, 0.5, 0.6);
	PxDesc.position = PxExtendedVec3(desc.position.x, desc.position.y, desc.position.z);
	PxDesc.height = desc.height;
	PxDesc.radius = desc.radius;
	PxDesc.slopeLimit = desc.slopeLimit;
	PxDesc.contactOffset = desc.contactOffset;
	PxDesc.stepOffset = desc.stepOffset;
	PxCapsuleController* ctrl = static_cast<PxCapsuleController*>(manager->createController(PxDesc));
	setPxController(ctrl);
}

void Character::setPxController(PxController* ctrl)
{
	this->ctrl = ctrl;
	this->ctrl->getActor()->userData = this;
}

void Character::move(const vec3& move, float dt)
{
	cout << dt << endl;
	PxVec3 PxMove(move.x, move.y, move.z);
	ctrl->move(PxMove, 0, dt, filters);
}

void Character::syncPhysics(const Transform& t)
{
	transform.p = t.p;
}
