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

		void loadTransformationMatrix(glm::mat4& matrix);
		void loadProjectionMatrix(glm::mat4& matrix);
		void loadViewMatrix(entities::Camera& camera);
		void loadModelView(glm::mat4& modelViewMatrix);
		void loadFocalLength(float focalLength);
		void loadWindowSize(glm::vec2& windowSize);
		void loadRayOrigin(glm::vec3& rayOrigin);

	protected:
		virtual void bindAttributes();
		virtual void getAllUniformLocations();

	private:
		static const std::string VERTEX_FILE;
		static const std::string FRAGMENT_FILE;

		int location_transformationMatrix;
		int location_projectionMatrix;
		int location_viewMatrix;
		int location_modelView;
		int location_focalLength;
		int location_windowSize;
		int location_rayOrigin;
	};
}
