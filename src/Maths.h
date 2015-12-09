#pragma once
#include "GLM/glm.hpp"
#include "Camera.h"

namespace toolbox
{
	class Maths
	{
	public:
		Maths();
		~Maths();

		static void createTransformationMatrix(glm::mat4& matrix, glm::vec3& translation, float rx, float ry, float rz, float scale);
		static void createViewMatrix(glm::mat4& viewmatrix, entities::Camera& camera);
	};
}