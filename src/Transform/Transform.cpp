#include "Transform.h"


Transform::Transform()
{
	p = vec3(1);
	q = quat(1, 0, 0, 0);
	s = vec3(1);
}

Transform::Transform(const vec3& pos, const quat& quat)
{
	p = pos;
	q = quat;
	s = vec3(1);
}

Transform::Transform(const vec3& pos, const vec3& scale, const quat& quat)
{
	p = pos;
	q = quat;
	s = scale;

}

Transform::Transform(float px, float py, float pz, const quat& q)
{
	this->p = vec3(px, py, pz);
	this->q = quat(q.w, q.x, q.y, q.z);
	s = vec3(1);

}

Transform::Transform(float px, float py, float pz, float qx, float qy, float qz, float qw)
{
	this->p = vec3(px, py, pz);
	this->q = quat(qw, qx, qy, qz);
	s = vec3(1);

}

Transform::Transform(float px, float py, float pz, float qx, float qy, float qz, float qw, vec3 s)
{
	this->p = vec3(px, py, pz);
	this->q = quat(qw, qx, qy, qz);
	this->s = s;
}

Transform::Transform(float px, float py, float pz, float qx, float qy, float qz, float qw, float sx, float sy, float sz)
{
	this->p = vec3(px, py, pz);
	this->q = quat(qw, qx, qy, qz);
	s = vec3(sx, sy, sz);
}

mat4 Transform::getMatix()
{
	mat4 m = toMat4(q);
	m[3] = vec4(p, 1);
	m = scale(m, s);
	return m;
}
