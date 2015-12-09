#include "VolumeRenderer.h"
#include "glew.h"
#include "Maths.h"
#include "RawModel.h"

using namespace renderEngine;
using namespace toolbox;
using namespace entities;
using namespace models;

VolumeRenderer::VolumeRenderer(shaders::VolumeShader& _shader) : shader(_shader)
{
}


VolumeRenderer::~VolumeRenderer()
{
}


void VolumeRenderer::render(Camera& camera, std::vector<VolumeRenderEntity*> VolumeRenderEntityList)
{
	for (auto* VolumeRenderEntity : VolumeRenderEntityList)
	{
		prepareVolumeRenderEntity(VolumeRenderEntity);
		loadModelMatrix(VolumeRenderEntity);

		glm::mat4 viewMatrix;
		Maths::createViewMatrix(viewMatrix, camera);
		glm::mat4 modelViewMatrix = viewMatrix * glm::mat4();
		shader.loadModelView(modelViewMatrix);
		glm::vec4 rayOrigin(glm::transpose(modelViewMatrix) * glm::vec4(camera.position, 1.0f));
		shader.loadRayOrigin(glm::vec3(rayOrigin));
		glDrawElements(GL_TRIANGLES, VolumeRenderEntity->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
}

void VolumeRenderer::prepareVolumeRenderEntity(VolumeRenderEntity* VolumeRenderEntity)
{
	RawModel* rawModel = VolumeRenderEntity->getModel();
	glBindVertexArray(rawModel->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//ModelTexture* texture = VolumeRenderEntity->getTexture();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, VolumeRenderEntity->getTextureID());
}

void VolumeRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void VolumeRenderer::loadModelMatrix(VolumeRenderEntity* VolumeRenderEntity)
{
	glm::mat4 transformationMatrix;
	Maths::createTransformationMatrix(transformationMatrix, glm::vec3(0, 0, 0), 0, 0, 0, 1);
	shader.loadTransformationMatrix(transformationMatrix);
}