#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
class FPS
{
	int fpsNow = 0;
	int totalFps = 0;
	int totalFpsInt = 0;
	double lastTime=0;

	int average=0;
	int min = 0;
	int max = 0;
public:

	int fps = 0;

	FPS();


	void count();
	void raport();
	float GetrRenderTime();
	//int min();
	//int max();
	//int averge();
};

