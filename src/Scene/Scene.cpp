#include "Scene.h"

Scene::Scene(Camera* camera)
{
	setCamera(camera);

	skyBox.load({
		"skyBox/right.jpg",
			"skyBox/left.jpg",
			"skyBox/top.jpg",
			"skyBox/bottom.jpg",
			"skyBox/front.jpg",
			"skyBox/back.jpg"
		});
}

Scene::~Scene()
{

	for (auto obj : objects)
	{
		delete obj.second;
	}
	objects.clear();
}

void Scene::addTexture(std::string name, mTexture* texture)
{
	textures.emplace(name, *texture);
}

void Scene::addShader(std::string name, Shader* shader)
{
	shaders.emplace(name, shader);
}

void Scene::addFrameBuffer(std::string name, FrameBuffer* fbo)
{
	frameBuffers.emplace("name", fbo);
}

void Scene::addObject(std::string name, Object* object)
{
	objects.emplace(name, object);

}

void Scene::addPortals(Portal* p1, Portal* p2)
{
	portals[0] = p1;
	portals[1] = p2;
	p1->setMeshes(meshes);
	p2->setMeshes(meshes);

	objects.emplace("portal1", p1);
	objects.emplace("portal2", p2);
}



void Scene::setMeshesData(Meshes* meshes)
{
	this->meshes = meshes;
}

template <class V>
void printVector(V v) {
	for (int i = 0; i < v.length(); i++)
		std::cout << v[i] << "\t";

	std::cout << "\n";
}
void Scene::draw(glm::mat4 projection, glm::mat4 view, float deltaTime, bool drawPortals)
{
	//=================================================================
	//															Physics
	physicsScene->Simulate(deltaTime);

	if (drawPortals)
	{
		//Сheck for drawing portals
		bool ShouldIdrawAPortal[2] = { false };
		for (int i = 0; i < 2; i++)
			ShouldIdrawAPortal[i] = glm::dot(camera->pos - portals[i]->getTransform().p, portals[i]->getNormal()) > 0;

		//Draw the Portal View
		for (int i = 0; i < 2; i++)
			if (ShouldIdrawAPortal[i])
<<<<<<< HEAD
				portals[i]->renderInsides(projection, view, 15, this, camera->fov);
=======
				portals[i]->renderInsides(projection, view, 5, this, camera->fov);
>>>>>>> bf762f326dfc36b9211e68c7770c01c3d1e7919e
		//Draw main scene
		drawMainScene(projection, view, ShouldIdrawAPortal[0], ShouldIdrawAPortal[1]);
	}
	else
	{
		drawNonPortals(projection, view);
	}

}

void Scene::drawMainScene(glm::mat4& projection, glm::mat4& view, bool portal1, bool portal2)
{
	if (portal1 || portal2)
	{
		glDisable(GL_STENCIL_TEST);
		glStencilMask(0x00);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glClear(GL_DEPTH_BUFFER_BIT);

		shaders["portal"]->use();
		shaders["portal"]->setMat4("projection", projection);
		shaders["portal"]->setMat4("view", view);
		for (int i = 0; i < 2; i++)
		{
			if ((portal1 && !i) || (portal2 && i))
			{
				glm::mat4 model2 = glm::translate(portals[i]->getTransform().getMatix(), glm::vec3(0, 0, -0.01));
				model2 = glm::scale(model2, glm::vec3(3, 6, 0.02));
				shaders["portal"]->setMat4("model", model2);
				(*meshes)["cubeNotTexture"]->draw();
				glm::mat4 modelSecPortal;
			}
		}
		//=================
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}


	drawNonPortals(projection, view);
}
void Scene::drawNonPortals(glm::mat4& projection, glm::mat4& view)
{
	sceneRender++;//Это просто счетчик
	//Usual routine
	shaders["standart_s"]->use();
	shaders["standart_s"]->setMat4("projection", projection);
	shaders["standart_s"]->setMat4("view", view);
	//--------------------------------------------
	for (auto obj : objects)
	{
		obj.second->draw(shaders["standart_s"]);
	}
	skyBox.draw(projection, view);
}

void Scene::setCamera(Camera* camera)
{
	this->camera = camera;
}