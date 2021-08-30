#include "Meshes.h"

Meshes::Meshes()
{
}

void Meshes::load()
{
	//------------------------------------------
	//									   floor
	floor.addBufferData({
		{ 0.0f, - 0.5f, -0.5f},
		{ 0.0f, 0.5f, -0.5f},
		{ 0.0f, 0.5f, 0.5f},
		{ 0.0f, -0.5f, 0.5f}
		});
	floor.addBufferData({
		{0.0, 0.0},
		{25.0, 0.0},
		{25.0, 25.0},
		{0.0, 25.0}
		});
	floor.addEBO({
		0, 1, 2,
		2, 3, 0
		});

	meshes.emplace("floor", &floor);
	//------------------------------------------
	//								 mirrorPlane
	mirrorPlane.addBufferData({
		{-1.5f, -3.f,  0.0f},
		{ 1.5f, -3.f,  0.0f},
		{ 1.5f,  3.f,  0.0f},
		{-1.5f,  3.f,  0.0f}
		});
	mirrorPlane.addBufferData({
		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0}
		});
	mirrorPlane.addEBO({
		0, 1, 2,
		2, 3, 0
		});

	meshes.emplace("mirrorPlane", &mirrorPlane);
	//------------------------------------------
	//							  fullScreenQuad
	fullScreenQuad.addBufferData({
		{-1.f, -1.f, 1.f},
		{ 1.f, -1.f, 1.f},
		{ 1.f,  1.f, 1.f},
		{-1.f,  1.f, 1.f}
		});
	fullScreenQuad.addEBO({
		0, 1, 2,
		2, 3, 0
		});

	meshes.emplace("fullScreenQuad", &fullScreenQuad);
	//------------------------------------------
	//										cube
	cube.addBufferData({
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
	cube.addBufferData({
		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0},

		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0},

		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0},

		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0},

		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0},

		{0.0, 0.0},
		{1.0, 0.0},
		{1.0, 1.0},
		{0.0, 1.0}
		});
	cube.addEBO({
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

	meshes.emplace("cube", &cube);
	//------------------------------------------
	//							CubeNotTexcoords
	cubeNotTexture.addBufferData({
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
	cubeNotTexture.addEBO({
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

	meshes.emplace("cubeNotTexture", &cubeNotTexture);
}


GL::VAO* Meshes::operator[](const char* name)
{
	return meshes[name];
}