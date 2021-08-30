#pragma once
#include<GL/glew.h>
#include<iostream>
#include<vector>
#include "../../libs/others/stb_image.h"
class mTexture
{
public:
	unsigned int id;
	mTexture();
	mTexture(GLenum filteringType, const std::string& path);
	mTexture(std::vector<std::string> faces, GLenum filteringType = GL_LINEAR);
	void load(GLenum filteringType, const std::string& path);
private:
	void loadCubeMapTexture(GLenum filteringType, std::vector<std::string> faces);
	void loadTexture(GLenum filteringType, const std::string& path);
};

