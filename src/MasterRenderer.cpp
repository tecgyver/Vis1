#include "MasterRenderer.h"
#include "glew.h"
#include "GLM/gtc/matrix_transform.hpp"

using namespace renderEngine;
using namespace shaders;
using namespace entities;


const float MasterRenderer::FOV = 70;
float MasterRenderer::zoomFactor = 1.f;
const float MasterRenderer::RED = 0.f;
const float MasterRenderer::GREEN = 0.f;
const float MasterRenderer::BLUE = 0.f;

MasterRenderer::MasterRenderer(int _width, int _height)
{
	enableCulling();
	width = _width;
	height = _height;

	volumeShader = new VolumeShader();
	volumeShader->init();

	volumeRenderer = new VolumeRenderer(*volumeShader);
}

MasterRenderer::~MasterRenderer()
{
	delete volumeShader;
	delete volumeRenderer;
}

void MasterRenderer::cleanup()
{
	volumeShader->cleanup();
}

void MasterRenderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(RED, GREEN, BLUE, 1);
}

void MasterRenderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::processVolumeRenderEntity(VolumeRenderEntity* VolumeRenderEntity)
{
	volumeRenderEntitysList.push_back(VolumeRenderEntity);
}

void MasterRenderer::render(Camera& camera)
{
	prepare();
	volumeShader->start();
	volumeShader->loadViewMatrix(camera);
	createProjectionMatrix();
	volumeShader->loadProjectionMatrix(projectionMatrix);
	volumeRenderer->render(camera, volumeRenderEntitysList);
	volumeShader->stop();

	volumeRenderEntitysList.clear();
}

void MasterRenderer::createProjectionMatrix()
{
	//projectionMatrix = glm::perspective(glm::radians(FOV), ((float)width) / height, NEAR_PLANE, FAR_PLANE);
	float aspectRatio = ((float)width) / height;
	float right, left, top, bottom;
	if (aspectRatio >= 1)
	{
		// sqrt(2) = max. Distanz zwischen Mitte der Bounding Box (0,0,0) und Rand.
		right = (1.f / zoomFactor) * aspectRatio * sqrt(2);
		left = (1.f / zoomFactor) * aspectRatio * (-sqrt(2));
		top = (1.f / zoomFactor) * sqrt(2);
		bottom = (1.f / zoomFactor) * (-sqrt(2));
	}
	else
	{
		// sqrt(2) = max. Distanz zwischen Mitte der Bounding Box (0,0,0) und Rand.
		right = (1.f / zoomFactor) * sqrt(2);
		left = (1.f / zoomFactor) * (-sqrt(2));
		top = (1.f / zoomFactor) * aspectRatio * sqrt(2);
		bottom = (1.f / zoomFactor) * aspectRatio * (-sqrt(2));
	}
	projectionMatrix = glm::mat4(	2.f / (right - left), 0.f, 0.f, -(right+left)/(right-left),
									0.f, 2.f / (top - bottom), 0.f, -(top+bottom)/(top-bottom),
									0.f, 0.f, 0.f, 0.f,
									0.f, 0.f, 0.f, 1.f);
}