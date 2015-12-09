#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include <vector>

namespace shaders
{
	class VolumeShader :
		public ShaderProgram
	{
	public:
		VolumeShader();
		~VolumeShader();

		void loadProjectionMatrix(glm::mat4& matrix);
		void loadViewMatrix(entities::Camera& camera);

	protected:
		virtual void bindAttributes();
		virtual void getAllUniformLocations();

	private:
		static const std::string VERTEX_FILE;
		static const std::string FRAGMENT_FILE;

		int location_projectionMatrix;
		int location_viewMatrix;
	};
}
