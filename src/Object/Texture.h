#pragma once
struct Texture
{
	Texture() {}
	Texture(unsigned int id, std::string type = "texture_diffuse") :id(id), type(type) {}
	unsigned int id;
	std::string type;
	std::string path;  // ������ ���� � �������� ��� ���� ��������� �������� �������
};