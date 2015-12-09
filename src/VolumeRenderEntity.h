#pragma once
#include "Loader.h"
//#include "Entity.h"
#include "RawModel.h"
#include "Volume.h"

class VolumeRenderEntity
{
public:
	VolumeRenderEntity(Volume* volume, renderEngine::Loader& loader);
	~VolumeRenderEntity();

	models::RawModel* getModel();
	
	int getTextureID();
	void setTextureID(int texId);
	

private:
	static const int VERTEX_COUNT;
	models::RawModel* model;
	
	int textureID;
	
	models::RawModel* generateVolumeRenderEntity(Volume* volume, renderEngine::Loader& loader);
};
