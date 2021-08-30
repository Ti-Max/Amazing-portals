#pragma once
#include<iostream>
#include<vector>
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include"Shader/Shader.h"
#include<string>
 
using namespace std;
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct Texture
{
	unsigned int id;
	string type;
    string path;  // храним путь к текстуре для нужд сравнения объектов тексту

};
class Mesh
{
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    /*  Functions  */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader *shader);
private:
    /*  Render data  */
    unsigned int VAO, VBO, EBO;
    //Создание VAO VBO EBO
    void setupMesh();
};