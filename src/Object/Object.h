#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "Transform/Transform.h"

#include "Shader/Shader.h"
#include "mTexture/mTexture.h"
#include "VAO/VAO.h"
#include "Model/Model.h"
#include "Object/RenderObjcect.h"
#include "Object/PhysicsObject.h"


class PhysicsObject;

class Object
{
public:
	Object();
	~Object();
	void setRenderObject(RenderObjcect* obj);
	void setPhysicsObject(PhysicsObject* obj);
	PhysicsObject* getPhysicsObject() { return physicsObject; }
	//void setTexture(unsigned int id);
	virtual void syncPhysics(const Transform& t);
	void setTransform(const Transform& t);
	//RETURN REFERENCE
	Transform& getTransform() { return transform; }
	//void setPosition(glm::vec3 position);
	//virtual void setRotation(glm::vec4 axisAngle);
	//virtual void setRotation(glm::quat q);

	void draw(Shader *shader);


protected:

	Transform transform;
	/*  Transform  */
	/*  Mesh  */
	RenderObjcect* renderObject = NULL;
	// Physics
	PhysicsObject* physicsObject = NULL;
};

