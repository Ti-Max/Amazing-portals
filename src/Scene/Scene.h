#pragma once
#include<iostream>
#include <GL/glew.h>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "Shader/Shader.h"
#include "mTexture/mTexture.h"
#include "VAO/VAO.h"
#include "Model/Model.h"
#include "Camera/Camera.h"
#include "FrameBuffer/FrameBuffer.h"
#include "Portal/Portal.h"
#include "SkyBox/SkyBox.h"
#include "VAO/Meshes.h"
#include "Object/Object.h"

#include "PxPhysicsAPI.h"
#include "Physics/PhysicsScene.h"

class Portal;

class Scene
{
public:
	Scene() {};
	Scene(Camera* camera);
	~Scene();

	void setPhysicsScene(PhysicsScene* scene) {
		this->physicsScene = scene;
	}
	void addTexture(std::string name, mTexture* texture);
	void addShader(std::string name, Shader* shader);
	void addFrameBuffer(std::string name, FrameBuffer* fbo);
	void addObject(std::string name, Object* object);
	void addPortals(Portal* p1, Portal* p2);
	//void setCamera(Camera* camera) { this->camera = camera; }
	//void addModel(std::string name, Model* model);

	void setMeshesData(Meshes* meshes);
	void draw(glm::mat4 projection, glm::mat4 view, float deltaTime, bool drawPortals);
	
	//std::map<std::string, Model*> models;
	std::map<std::string, Object*> objects;

	Meshes* meshes;
	Portal* portals[2];
	std::map<std::string, Shader*> shaders;
	std::map<std::string, mTexture> textures;
	std::map<std::string, FrameBuffer*> frameBuffers;

	void setCamera(Camera* camera);
	int sceneRender = 0;

	void drawNonPortals(glm::mat4& projection, glm::mat4& view);
private:
	//void simulatePhysics(float dt);
	//void drawPortals(glm::mat4& projection, glm::mat4& view, int maxLevelRecursion, int levelRecursion, int selectedPortal);
	void drawMainScene(glm::mat4& projection, glm::mat4& view, bool portal1, bool portal2);

	//glm::mat4 getPotalView(const glm::mat4& m1, const glm::mat4& m2, const glm::mat4& v);
	//glm::mat4 getPotalProjection(const glm::mat4& m2, const glm::mat4& v);
	
	
	Camera* camera;
	SkyBox skyBox;
	// physics
	PhysicsScene* physicsScene = nullptr;
};

