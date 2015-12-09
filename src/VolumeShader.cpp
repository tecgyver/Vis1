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
	location_transformationMatrix = getUniformLocation(std::string("transformationMatrix"));
	location_projectionMatrix = getUniformLocation(std::string("projectionMatrix"));
	location_viewMatrix = getUniformLocation(std::string("viewMatrix"));
	location_modelView = getUniformLocation(std::string("modelView"));
	location_focalLength = getUniformLocation(std::string("focalLength"));
	location_windowSize = getUniformLocation(std::string("windowSize"));
	location_rayOrigin = getUniformLocation(std::string("rayOrigin"));
}

void VolumeShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
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

void VolumeShader::loadModelView(glm::mat4& modelViewMatrix)
{
	loadMatrix(location_modelView, modelViewMatrix);
}

void VolumeShader::loadFocalLength(float focalLength)
{
	loadFloat(location_focalLength, focalLength);
}

void VolumeShader::loadWindowSize(glm::vec2& windowSize)
{
	loadVector(location_windowSize, windowSize);
}

void VolumeShader::loadRayOrigin(glm::vec3& rayOrigin)
{
	loadVector(location_rayOrigin, rayOrigin);
}