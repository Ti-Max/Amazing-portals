#pragma once
#include "Character.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>


class PlayerMovement
{
public:
	float speed = 1;
	PlayerMovement();
	void checkKeys(int key, int action);
	void checkMouse(float xpos, float ypos);
	void doMovement(float dt);
	void setCharacter(Character* player) { this->player = player; }
private:
	vec2 getInputAxis(float dt);
	vec2 getInput();
	Character* player;
	bool keys[348];
	
	//костыли, но это не точно
	vec2 oldInput;
	//точно костыли
	int newestInput[2];

	//Mouse input
	float yaw = -90.f;
	float pitch = -20.0f;
	float lastX, lastY = 0;
	bool firstMouse = true;
};

