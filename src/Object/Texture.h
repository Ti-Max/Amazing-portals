#pragma once
struct Texture
{
	Texture() {}
	Texture(unsigned int id, std::string type = "texture_diffuse") :id(id), type(type) {}
	unsigned int id;
	std::string type;
	std::string path;  // храним путь к текстуре для нужд сравнения объектов текстур
};