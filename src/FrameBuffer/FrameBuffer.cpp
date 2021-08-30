#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::FrameBuffer(const int width, const int height)
{
	genFrameBuffer(width, height);
}

void FrameBuffer::bind(unsigned int fbo)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo? this->fbo : fbo);
}

void FrameBuffer::genFrameBuffer(const int width, const int height)
{
	glGenFramebuffers(1, &fbo);
	bind();
	//---------------------------------------------------------------------------------------------------
	// создание текстурного объекта
	colorTexture;
	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// присоедиение текстуры к объекту текущего кадрового буфера
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
	//---------------------------------------------------------------------------------------------------
	// создание текстурного объекта глубины
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//---------------------------------------------------------------------------------------------------
	//Проверка
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	bind(0);
}
