#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Debug/Points.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>
#include "Transform/Transform.h"

#define KEY_UP 0
#define KEY_LEFT 1
#define KEY_DOWN 2
#define KEY_RIGHT 3
#define KEY_SHIFT 4
#define KEY_SPACE 5
#define KEY_CONTROL 6
using namespace std;
class Camera
{
public:
	Camera();
	Camera(glm::vec3 pos);
	void checkKeys(int key, int action);
	void checkMouse(float xPos, float yPos);
	void checkScroll(float yoffset);
	void do_movement();
	glm::mat4 getViewMat();
	glm::mat4 getReflectionViewMat(glm::vec3 mPos, glm::vec3 n);
	glm::mat4 getPortalViewMat(glm::vec3 p1Pos, glm::vec3 p2Pos, glm::mat3 m1, glm::mat3 m2);
	glm::mat4 getProjectionClipMat(glm::vec4 clipPlane);

	float speed = 10;
	float fov = 70.0f;

	void setFolowedTransform(Transform* trans, vec3 offset);
	

	glm::vec3 posSecCam;

	glm::vec3 pos;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	Points points;
private:
	Transform* followedTransform;
	vec3 cameraoffset;
	float distans;
	float reflectionFov;
	float lastTime = 0.0f;
	bool keys[7];
	bool movingAfterCtrl = false;

	float yaw = -90.f;
	float pitch = -20.0f;
	float lastX, lastY =0;
	bool firstMouse = true;
};

