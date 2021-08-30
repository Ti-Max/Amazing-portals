#pragma once
#include <GL/glew.h>
#include <iostream>
class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(const int width, const int height);
	void bind(unsigned int fbo = 1);

	unsigned int colorTexture;
	void genFrameBuffer(const int width, const int height);
private:
	unsigned int fbo;
};

