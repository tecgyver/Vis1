#pragma once
#include <vector>

#include "VolumeShader.h"
#include "VolumeRenderEntity.h"
#include "Camera.h"

namespace renderEngine
{
	class VolumeRenderer
	{
	public:
		VolumeRenderer(shaders::VolumeShader& shader);
		~VolumeRenderer();

		void render(entities::Camera& camera, std::vector<VolumeRenderEntity*> VolumeRenderEntityList);

	private:
		shaders::VolumeShader& shader;

		void prepareVolumeRenderEntity(VolumeRenderEntity* VolumeRenderEntity);
		void unbindTexturedModel();
	};
}