#include "Maths.h"
#include "GLM/gtc/matrix_transform.hpp"

using namespace toolbox;
using namespace entities;

Maths::Maths()
{
}


Maths::~Maths()
{
}


void Maths::createTransformationMatrix(glm::mat4& matrix, glm::vec3& translation, float rx, float ry, float rz, float scale)
{
	matrix = glm::translate(matrix, translation);
	matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
}

void Maths::createViewMatrix(glm::mat4& viewmatrix, Camera& camera)
{
	viewmatrix = glm::rotate(viewmatrix, glm::radians(-camera.pitch), glm::vec3(1, 0, 0));
	viewmatrix = glm::rotate(viewmatrix, glm::radians(-camera.yaw), glm::vec3(0, 1, 0));
	viewmatrix = glm::rotate(viewmatrix, glm::radians(-camera.roll), glm::vec3(0, 0, 1));
	viewmatrix = glm::translate(viewmatrix, -camera.position);
}