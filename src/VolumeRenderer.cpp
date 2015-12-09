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

		glm::mat4 viewMatrix;
		Maths::createViewMatrix(viewMatrix, camera);
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