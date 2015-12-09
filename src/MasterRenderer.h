#pragma once
#include <map>
#include <vector>

#include "Camera.h"
#include "VolumeShader.h"
#include "VolumeRenderer.h"
#include "VolumeRenderEntity.h"

namespace renderEngine
{
	class MasterRenderer
	{
	public:
		MasterRenderer(int width, int height);
		~MasterRenderer();

		static float zoomFactor;

		void cleanup();
		void prepare(); 
		void processVolumeRenderEntity(VolumeRenderEntity* VolumeRenderEntity);
		void render(entities::Camera& camera);

		static void enableCulling();
		static void disableCulling();
		shaders::VolumeShader* volumeShader;

	private:
		static const float FOV;
		static const float RED;
		static const float GREEN;
		static const float BLUE;

		int width;
		int height;
		glm::mat4 projectionMatrix;
		
		renderEngine::VolumeRenderer* volumeRenderer;
		std::vector<VolumeRenderEntity*> volumeRenderEntitysList;

		void createProjectionMatrix();
	};
}