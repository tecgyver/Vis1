#include "VolumeRenderEntity.h"


using namespace models;
using namespace renderEngine;
//using namespace entities;

const int VolumeRenderEntity::VERTEX_COUNT = 128;

VolumeRenderEntity::VolumeRenderEntity(Volume* volume, Loader& loader)
{
	model = generateVolumeRenderEntity(volume, loader);
}

VolumeRenderEntity::~VolumeRenderEntity()
{
}

models::RawModel* VolumeRenderEntity::getModel()
{
	return model;
}


int VolumeRenderEntity::getTextureID()
{
	return textureID;
}

void VolumeRenderEntity::setTextureID(int texId)
{
	textureID = texId;
}

RawModel* VolumeRenderEntity::generateVolumeRenderEntity(Volume* volume, Loader& loader)
{
	//TODO: Generate Bounding Box
	std::vector<float> vertices = {
		//Back
		-1.f, -1.f, -1.f,
		-1.f, 1.f, -1.f,
		1.f, 1.f, -1.f,
		1.f, -1.f, -1.f,

		//Front
		-1.f, -1.f, 1.f,
		1.f, -1.f, 1.f,
		1.f, 1.f, 1.f,
		-1.f, 1.f, 1.f,

		//Top
		1.f, 1.f, 1.f,
		1.f, 1.f, -1.f,
		-1.f, 1.f, -1.f,
		-1.f, 1.f, 1.f,

		//Bottom
		1.f, -1.f, 1.f,
		-1.f, -1.f, 1.f,
		-1.f, -1.f, -1.f,
		1.f, -1.f, -1.f,

		//Right
		1.f, 1.f, 1.f,
		1.f, -1.f, 1.f,
		1.f, -1.f, -1.f,
		1.f, 1.f, -1.f,

		//Left
		-1.f, 1.f, 1.f,
		-1.f, 1.f, -1.f,
		-1.f, -1.f, -1.f,
		-1.f, -1.f, 1.f
	};

	std::vector<int> indices = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	std::vector<float> normals = {
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
	};

	std::vector<float> textureCoords = {
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

	};

	return loader.loadToVAO(vertices, textureCoords, normals, indices);
}