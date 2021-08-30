#pragma once
#include <vector>
#include <string>

#include "Shader/Shader.h"
#include "VAO/VAO.h"
#include "Texture.h"
#include "Model/Model.h"

class RenderObjcect
{
public:
	RenderObjcect();
	~RenderObjcect();
	RenderObjcect(Model* model);
	RenderObjcect(GL::VAO* mesh, std::vector<Texture> textures);
	RenderObjcect(GL::VAO* mesh, unsigned int textureId);
	void setMesh(GL::VAO* mesh);
	void draw(Shader* shader, const glm::mat4& transMat);

private:
	GL::VAO* mesh;
	std::vector<Texture> textures;
};

