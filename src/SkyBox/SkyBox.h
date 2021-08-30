#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "Shader/Shader.h"
#include "mTexture/mTexture.h"
#include "VAO/VAO.h"

class SkyBox
{
public:
	SkyBox();
	void load(std::vector<std::string>  faces, GLenum filteringType = GL_LINEAR);
	SkyBox(std::vector<std::string> faces, GLenum filteringType = GL_LINEAR);

	void draw(glm::mat4& projection, glm::mat4& view);
private:
	void loadSkyBox(std::vector<std::string>& faces, GLenum filteringType = GL_LINEAR);
	GL::VAO skyBox;
	unsigned int textureId;
	Shader shader;
};

