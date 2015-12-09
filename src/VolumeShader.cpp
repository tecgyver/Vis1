#include "VolumeShader.h"
#include "Maths.h"
#include "GLM/gtc/matrix_transform.hpp"

using namespace shaders;
using namespace entities;
using namespace toolbox;

const std::string VolumeShader::VERTEX_FILE = std::string("res/vertexShader.txt");
const std::string VolumeShader::FRAGMENT_FILE = std::string("res/fragmentShader.txt");
VolumeShader::VolumeShader()
	: ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
}


VolumeShader::~VolumeShader()
{
}

void VolumeShader::bindAttributes()
{
	bindAttribute(0, std::string("position"));
	bindAttribute(1, std::string("textureCoords"));
	bindAttribute(2, std::string("normal"));
}

void VolumeShader::getAllUniformLocations()
{
	location_projectionMatrix = getUniformLocation(std::string("projectionMatrix"));
	location_viewMatrix = getUniformLocation(std::string("viewMatrix"));
}

void VolumeShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void VolumeShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix;
	Maths::createViewMatrix(viewMatrix, camera);
	loadMatrix(location_viewMatrix, viewMatrix);
}