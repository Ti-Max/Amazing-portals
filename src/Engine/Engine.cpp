#include "Engine.h"

#include "Model/Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VAO/VAO.h"
#include "Camera/Camera.h"
#include "mTexture/mTexture.h"
#include "FrameBuffer/FrameBuffer.h"
#include "FPS/FPS.h"
#include"Text/mText.h"

#include "../CCT/Character.h"
#include "../CCT/PlayerMovement.h"
//#include"Physics/Physics.h"
//#include "Physics/PhysicsScene.h"
//#include "Object/PhysicsObject.h"
//#include "Object/Object.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
Camera camera(glm::vec3(2, 3.3, 15));
PlayerMovement playerMovement;

Engine::Engine(const std::string& title, int width, int height)
{


	this->height = height;
	this->width = width;

	window = glfwCreateWindow(width, height+1, title.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, width / 2, height / 2);

	glfwSetWindowPos(window, 1920 - width, 200);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to connect GLEW" << std::endl;
	}

	//ViewPort
	int widthPX, heightPX;
	glfwGetFramebufferSize(window, &widthPX, &heightPX);
	glViewport(0, 0, widthPX, heightPX);

	//Вертикальная синхронизация, vsync
	glfwSwapInterval(1);
}
Engine::~Engine()
{
	glfwDestroyWindow(window);
}

float NEAR = 0.01f;
float FAR = 300.0f;
bool k1, k2, k3, k4, k5 = false;
bool press = false;
void Engine::loop()
{

	Physics* physics = new Physics;
	if (!physics->Init(true))
		cout << "PhysX — Что-то пошло не так!" << endl;
	physics->createScene();
	PhysicsScene* phScene = physics->getScene();

	//@@@@@@@@@@@@@@@@@@@@@@@@@@
	
	//// remove controller shape from scene query for standup overlap test
	//PxRigidDynamic* actor = ctrl->getActor();
	//
	//PxController* c = manager->createController(cDesc);
	//phScene->getPxScene()->addActor(*(c->getActor()));
	//@@@@@@@@@@@@@@@@@@@@@@@@@@

	Scene scene(&camera);
	scene.setPhysicsScene(phScene);
	//=============================================================================================
	//PHYSICS

	//=============================================================================================
	Meshes meshesData;
	meshesData.load();

	scene.setMeshesData(&meshesData);
	/****************************************************************************************************************/
	/*												Scene things													*/
	//Shaders
	Shader quadShader("quad");
	scene.addShader("standart_s", &quadShader);

	Shader fullScreenQuad("fullScreenQuad");
	scene.addShader("fullScreenQuad", &fullScreenQuad);

	Shader mirrorShader("mirror");
	scene.addShader("mirror", &mirrorShader);

	Shader portalShader("portal");
	scene.addShader("portal", &portalShader);

	Shader portal2Shader("portal2");
	scene.addShader("portal2", &portal2Shader);
	Shader PointShader("Points");

	//Textures
	mTexture floorT(GL_LINEAR, "floor.jpg");
	mTexture blue_wall(GL_LINEAR, "blue_wall.jpg");
	mTexture orange_wal(GL_LINEAR, "orange_wall.jpg");
	mTexture box(GL_LINEAR, "box.jpg");
	scene.addTexture("wood_floor", &floorT);
	scene.addTexture("orange_wall", &orange_wal);
	scene.addTexture("blue_wall", &blue_wall);
	scene.addTexture("box", &box);
	scene.textures["orange_wall"];
	//--------------------------------------------------
	//Objects

	Object* floor = new Object;

	PhysicsObject* floorPh = new PhysicsObject(phScene, STATIC);
	floorPh->setShapePlane(glm::vec4(0, 1, 0, 0));
	//floorPh->setTransform(floorPh->getPosition(), glm::quat(0, 0, 0, 1));
	floor->setPhysicsObject(floorPh);
	floor->setTransform(Transform(vec3(0, 0, 0), vec3(1, 200, 200), quat(0, 0.707, 0.707, 0)));

	///*---PHYSICS---*/
	RenderObjcect floor_RO(meshesData["floor"], floorT.id);
	floor->setRenderObject(&floor_RO);
	scene.addObject("floor", floor);

	int i = 0;
	for (int x = -4; x < 1; x+=1)
	{
		for (int y = 0; y < 2; y+=1)
		{
		//	for (int z = -2; z < 1; z+=1)
		//	{
				Object* cube = new Object;
				RenderObjcect* cubeRO = new RenderObjcect(meshesData["cube"], orange_wal.id);
				cube->setRenderObject(cubeRO);

				PhysicsObject* cubePh = new PhysicsObject(phScene, DYNAMIC);
				cubePh->setMass(10);
				cubePh->setShapeBox();
				cube->setPhysicsObject(cubePh);
				cube->setTransform(Transform(glm::vec3(x, (y+5), 4), vec3(1)));

				scene.addObject("cube_" + std::to_string(i++), cube);
			}
		//}
	}
	//Object* cube = new Object;
	//RenderObjcect cubeRO(meshesData["cube"], box.id);
	//cube->setRenderObject(&cubeRO);
	//cube->setPosition(glm::vec3(0, 5, 0));

	//PhysicsObject* cubePh = new PhysicsObject(mScene, DYNAMIC, glm::vec3(0, 5, 0));
	//cubePh->setShapeBox(glm::vec3(0.5));
	//cube->setPhysicsObject(cubePh);

	//scene.addObject("cube_", cube);

	//===============================================
	//PORTALS
	Model portal1_imp("res/models/portalO/Portal_Orange.obj");
	Model portal2_imp("res/models/portalB/Portal_Blue.obj");

	Portal* portal1 = new Portal;
	RenderObjcect portal1_RO(&portal1_imp);
	portal1->setRenderObject(&portal1_RO);
	portal1->setTransform(Transform(glm::vec3(-5, 3.3, 4), angleAxis(radians(90.f), vec3(0, 1, 0))));

	Portal* portal2 = new Portal;
	RenderObjcect bluePortal(&portal2_imp);
	portal2->setRenderObject(&bluePortal);
	portal2->setTransform(Transform(glm::vec3(11, 3.3, 0), angleAxis(radians(-90.f), vec3(0, 1, 0))));

	portal1->attachPortal(portal2);
	portal2->attachPortal(portal1);

	scene.addPortals(portal1, portal2);
	
	//Model Player_imp("res/models/Bean/Bean.obj");
	//Object* Player = new Object;
	//RenderObjcect* Player_RO = new RenderObjcect(&Player_imp);
	//Player->setRenderObject(Player_RO);
	//scene.addObject("Player", Player);
	//Player->setTransform(Transform(glm::vec3(0, 2, -2), glm::vec3(0.5)));
	//PhysicsObject* Player_Ph = new PhysicsObject(,);
	//Player->setPhysicsObject();

	Character* Player = new Character;
	Model Player_imp("res/models/Bean/Bean.obj");
	RenderObjcect* Player_RO = new RenderObjcect(&Player_imp);
	Player->setRenderObject(Player_RO);
	Player->setTransform(Transform(glm::vec3(0, 2, 7), glm::vec3(0.5)));

	PxControllerManager* manager = PxCreateControllerManager(*phScene->getPxScene());
	Player->createController(manager, CtrlDesc(glm::vec3(0, 2, -7), 1.5, 0.5, 0.0f));
	playerMovement.setCharacter(Player);
	scene.addObject("Player", Player);


	//Object* Environment = new Object;
	//RenderObjcect* EnvironmentRO = new RenderObjcect(meshesData["cube"], orange_wal.id);

	//Model Environment_imp("res/models/Environment/Environment.obj");
	//Environment->setRenderObject(EnvironmentRO);
	//Environment->setPhysicsObject(&Environment_imp);
	//Environment->setTransform(Transform(glm::vec3(0), vec3(1)));

	//scene.addObject("cube_" + std::to_string(i++), Environment);

	/*												Scene objects DONE												*/
	/****************************************************************************************************************/

	mText txt(width, height);
	Shader textShader("text");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	camera.setFolowedTransform(&(Player->getTransform()), vec3(0, 2, 4));

	FPS fps;
	float lastTime = glfwGetTime();
	std::cout << "Starting the game\n";
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		fps.count();
		glfwPollEvents();
		camera.do_movement();
		playerMovement.doMovement(deltaTime);
		/*##########################################################################*/
		/*									RENDER									*/	
		//Usual render
		glClearColor(0.1f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)width / (float)height, NEAR, FAR);
		glm::mat4 view = camera.getViewMat();
		scene.draw(projection, view, deltaTime, true);

		PointShader.setMat4("projection", projection);
		PointShader.setMat4("view", view);
		camera.points.draw();
		//=-=-=-=-=-=-=-=-x=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
													//	 Canvas
		txt.Write(textShader, std::to_string(fps.fps), (float)width - 105.f, (float)height - 43.f, 1.f, glm::vec3(0.3, 0.9f, 0.2f));
		txt.Write(textShader, std::to_string(scene.sceneRender), (float)width - 55.f, (float)height - 83.f, 1.f, glm::vec3(0.9, 0.1f, 0.1f));
		scene.sceneRender = 0;
		/*								 RENDER DONE								*/
		/*##########################################################################*/
		glfwSwapBuffers(window);	
		phScene->getPxScene()->fetchResults(true);

	}
	fps.raport();
}



int x, y, xPos, yPos;
void setFullScreenMode(GLFWwindow* window)
{
	if (glfwGetWindowMonitor(window))
	{
		glfwSetWindowMonitor(window, nullptr, xPos, yPos, x, y, NULL);
	}
	else
	{
		//backup
		glfwGetWindowSize(window, &x, &y);
		glfwGetWindowPos(window, &xPos, &yPos);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 1000, 300, mode->width, mode->height, mode->refreshRate);
	}
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
		setFullScreenMode(window);

	if (key == GLFW_KEY_UP &&action == GLFW_PRESS)
		k1 = true;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		k2 = true;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		k3 = true;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		k4 = true;
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		k5 = true;

	if (key == GLFW_KEY_UP &&action == GLFW_RELEASE)
		k1 = false;
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		k2 = false;
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		k3 = false;
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		k4 = false;



	//Portal Rotation
	if (key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera.pos.x += 0.001;
	if (key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		camera.pos.x -= 0.001;
	////Portal Pos
	if (key == GLFW_KEY_5 && (action == GLFW_PRESS))
		std::cout << camera.pos.x<<"\t" <<camera.pos.y<<"\t" <<camera.pos.z<<"\t" << std::endl;

	camera.checkKeys(key, action);
	playerMovement.checkKeys(key, action);

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.checkMouse((float)xpos, (float)ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.checkScroll((float)yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << width << "\n" << height << std::endl;
}