#pragma once
#include "KeyCode.h"

class Input
{
public:
	void updateInput(int glfwKey, int glwfAction);


	bool getKeyDown(KeyCode keyCode);
	bool getKeyUp(KeyCode keyCode);

};

