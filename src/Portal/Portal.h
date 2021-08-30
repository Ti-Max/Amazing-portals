#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Object/Object.h"
#include "VAO/Meshes.h"
#include "Shader/Shader.h"
#include "Scene/Scene.h"
using namespace glm;
class Scene;

class Portal : public Object
{
public:
	Portal();
	~Portal();

	void renderInsides(glm::mat4& projection, glm::mat4& view, int maxLevelRecursion, Scene* scene, float fov);


	void attachPortal(Portal* p);
	void setMeshes(Meshes* m);
	mat4 getMat3();
	vec3 getNormal();
	glm::vec3 getIitialNormal();

private:

	void drawRecursive(glm::mat4& projection, glm::mat4& view, int maxLevelRecursion, int levelRecursion, Scene* scene);

	glm::mat4 getPotalView(const glm::mat4& m1, const  glm::mat4& m2, const glm::mat4& v);
	glm::mat4 getPotalProjection(const glm::mat4& m2, const glm::mat4& v);

	glm::mat4 getProjectionClipMat(glm::vec4 clipPlane);

	void setInitialNormal(vec3 n);

	Portal* secPortal;
	Meshes* meshes;
	Shader* nonColorShader;
	
	vec3 normal;
	vec3 initialNormal;


	float fov;
};

