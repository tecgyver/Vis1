#include <iostream>

#include "Loader.h"
#include "glew.h"

using namespace renderEngine;
using namespace models;

Loader::Loader()
{
}


Loader::~Loader()
{
}

RawModel* Loader::loadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<int>& indices)
{
	int vaoID = createVAO();
	bindIndicesBuffer(indices);

	long counter = 0;
	glm::vec3 min = glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	glm::vec3 max = glm::vec3(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
	for (auto& position : positions)
	{
		switch (counter % 3)
		{
		case 0:
			min.x = glm::min(min.x, position);
			max.x = glm::max(max.x, position);
			break;
		case 1:
			min.y = glm::min(min.y, position);
			max.y = glm::max(max.y, position);
			break;
		case 2:
			min.z = glm::min(min.z, position);
			max.z = glm::max(max.z, position);
			break;
		}
		counter++;
	}
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	unbindVAO();
	auto* model = new RawModel(vaoID, indices.size());
	model->minValues = min;
	model->maxValues = max;
	return model;
}

int Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}


void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<int>& indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}


int Loader::loadVolume(Volume* volume)
{
	unsigned int width(0), height(0), depth(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;


	std::vector<float> voxelValues;

	//Maximale Größe berechnen und Quader daraus machen
	glm::vec3 textureSize = glm::vec3(glm::max(volume->width(), glm::max(volume->height(), volume->depth())));
	//Quader auf die nächst höhere "power of two" vergrößern (OpenGL-Bedingung)
	textureSize = glm::vec3(glm::pow(2.f, glm::ceil(glm::log2(textureSize.x))));
	glm::vec3 volumeSize = glm::vec3(volume->width(), volume->height(), volume->depth());
	glm::vec3 loopStart = glm::round(-glm::floor((textureSize - volumeSize) / 2.0f));
	glm::vec3 loopEnd = volumeSize - loopStart;

	for (int z = loopStart.z; z < loopEnd.z; z++)
	{
		for (int y = loopStart.y; y < loopEnd.y; y++)
		{
			for (int x = loopStart.x; x < loopEnd.x; x++)
			{
				voxelValues.push_back(volume->voxel(x, y, z).getValue());
			}
		}
	}
	//auto* voxels = volume->voxels();
	//for (int i = 0; i < volume->width() * volume->height() * volume->depth(); i++)
	//{
	//	voxelValues.push_back(voxels[i].getValue());
	//}
	float* bits = &voxelValues[0];
	//get the volume width, height and depth
	width = volume->width();
	height = volume->height();
	depth = volume->depth();

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	glActiveTexture(GL_TEXTURE0);
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_3D, gl_texID);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//store the texture data for OpenGL use
	glTexImage3D(GL_TEXTURE_3D, 0, GL_LUMINANCE, textureSize.x, textureSize.y, textureSize.z,
		0, GL_LUMINANCE, GL_FLOAT, bits);
	//glTexImage3D(GL_TEXTURE_3D, 0, GL_LUMINANCE, width, height, depth,
	//	0, GL_LUMINANCE, GL_FLOAT, bits);

	glGenerateMipmap(GL_TEXTURE_3D);

	textures.push_back(gl_texID);

	//return success
	return gl_texID;
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void Loader::cleanup()
{
	GLuint current;
	for (auto& vao : vaos)
	{
		current = vao;
		glDeleteVertexArrays(1, &current);
	}
	for (auto& vbo : vbos)
	{
		current = vbo;
		glDeleteBuffers(1, &current);
	}
	for (auto& texture : textures)
	{
		current = texture;
		glDeleteTextures(1, &current);
	}

	vaos.clear();
	vbos.clear();
	textures.clear();
}