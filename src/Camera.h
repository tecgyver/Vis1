#pragma once
#include "GLM/glm.hpp"

namespace entities
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		glm::vec3 position;
		float pitch;
		float yaw;
		float roll;
	};
}