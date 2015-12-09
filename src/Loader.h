#pragma once

#include <vector>

#include "RawModel.h"
#include "Volume.h"

namespace renderEngine
{
	class Loader
	{
	public:
		Loader();
		~Loader();
		models::RawModel* loadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<int>& indices);
		void cleanup();
		int loadVolume(Volume* volume);

	private:
		std::vector<int> vaos;
		std::vector<int> vbos;
		std::vector<int> textures;

		int createVAO();
		void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data);
		void unbindVAO();
		void bindIndicesBuffer(std::vector<int>& indices);
	};
}