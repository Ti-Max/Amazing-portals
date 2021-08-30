#pragma once
#include<iostream>
#include <GL/glew.h>
#include "Scene/Scene.h"
#include "Shader/Shader.h"

#include <GLFW/glfw3.h>

class Engine
{
public:
	Engine(const std::string& title, int width, int height);
	~Engine();
	void loop();

private:
	GLFWwindow* window;
	int height, width;
};

