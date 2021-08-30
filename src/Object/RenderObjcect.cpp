#include "RenderObjcect.h"

RenderObjcect::~RenderObjcect()
{
	//std::cout << "~RenderObject()\n";
}

RenderObjcect::RenderObjcect(Model* model)
{
	this->mesh = model->meshes[0];
	this->textures = model->textures_loaded;
}

RenderObjcect::RenderObjcect(GL::VAO* mesh, std::vector<Texture> textures)
{
	this->mesh = mesh;
	this->textures = textures;
}

RenderObjcect::RenderObjcect(GL::VAO* mesh, unsigned int textureId)
{
	this->mesh = mesh;
	textures.push_back(Texture(textureId));
}

void RenderObjcect::draw(Shader* shader, const glm::mat4& transMat)
{
	//Matrix
	shader->use();
	shader->setMat4("model", transMat);
	//Textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = textures[i].type;
		int id;
		if (name == "texture_diffuse")
			id = diffuseNr++;
		if (name == "texture_specular")
			id = specularNr++;

		shader->setInt(name + std::to_string(id), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	//VAO
	mesh->draw();
}
