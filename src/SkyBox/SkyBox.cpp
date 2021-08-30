#include "SkyBox.h"

SkyBox::SkyBox()
{
}

void SkyBox::load(std::vector<std::string> faces, GLenum filteringType)
{
	loadSkyBox(faces, filteringType);
}

SkyBox::SkyBox(std::vector<std::string> faces, GLenum filteringType)
{
	loadSkyBox(faces, filteringType);
}

void SkyBox::draw(glm::mat4& projection, glm::mat4& view)
{
	glDepthFunc(GL_LEQUAL);
	shader.use();
	glm::mat4 skyBoxView = glm::mat4(glm::mat3(view));
	shader.setMat4("view", skyBoxView);
	shader.setMat4("projection", projection);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	skyBox.draw();
	glDepthFunc(GL_LESS);
}

void SkyBox::loadSkyBox(std::vector<std::string>& faces, GLenum filteringType)
{
	//Textures
	mTexture skyboxTex(faces);
	textureId = skyboxTex.id;
	//Shader
	shader.load("skyBox");
	//VAO
	skyBox.addBufferData({
		{-0.5f, -0.5f,  0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},

		{ 0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},

		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{ 0.5f,  0.5f,  0.5f},

		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f, -0.5f},

		{-0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{ 0.5f,  0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f},

		{-0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f, -0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{-0.5f, -0.5f,  0.5f}
		});
	skyBox.addEBO({
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20
		});
}
