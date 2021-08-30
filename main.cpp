#include <iostream>
#include "Engine/Engine.h"
#include "GLFW/GLFW.h"



int main() {
	GLFW glfw;
	Engine engine("Non Euclidian Engine", 1280, 720);
	engine.loop();
//adaw
	return 0;
}