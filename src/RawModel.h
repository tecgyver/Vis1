#pragma once
#include "GLM/glm.hpp"

namespace models
{
	class RawModel
	{
	public:
		RawModel(int vaoID, int vertexCount);
		~RawModel();

		const int& getVaoID();
		const int& getVertexCount();
		glm::vec3 minValues;
		glm::vec3 maxValues;

	private:
		int vaoID;
		int vertexCount;
	};
}