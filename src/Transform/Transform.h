#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Transform
{
public:
	Transform();
	Transform(const vec3 &pos, const quat &quat = quat(1, 0, 0, 0));
	Transform(const vec3 &pos, const vec3 &scale, const quat& quat = quat(1, 0, 0, 0));
	Transform(float px, float py, float pz, const quat &q =  quat(1, 0, 0, 0));
	Transform(float px, float py, float pz, float qx, float qy, float qz, float qw);
	Transform(float px, float py, float pz, float qx, float qy, float qz, float qw, vec3 s);
	Transform(float px, float py, float pz, float qx, float qy, float qz, float qw, float sx, float sy, float sz);

	mat4 getMatix();
	//Quaternion
	quat q;
	//Position
	vec3 p;
	//Scale
	vec3 s;

};

