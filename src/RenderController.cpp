#include <cstdlib> 
#include <ctime>

#include "RenderController.h"
#include "DisplayManager.h"
#include "VolumeShader.h"
#include "MasterRenderer.h"
#include "VolumeRenderEntity.h"
#include "MainWindow.h"

using namespace engineTester;
using namespace renderEngine;
using namespace entities;


Loader RenderController::loader;
Camera RenderController::camera;
VolumeRenderEntity* RenderController::volumeRenderEntity = 0;
Volume* RenderController::volume = 0;
MasterRenderer* RenderController::renderer = 0;
bool RenderController::newVolume = false;
Ui_MainWindow* RenderController::m_Ui = 0;

RenderController::RenderController()
{
}


RenderController::~RenderController()
{
}

void RenderController::init(RaycastRenderingWidget* window)
{
	DisplayManager::createDisplay(window);
	renderer = new MasterRenderer(DisplayManager::width, DisplayManager::height);
}

void RenderController::reset()
{
	if (RenderController::volumeRenderEntity)
		delete RenderController::volumeRenderEntity;
	loader.cleanup();
}

void RenderController::setVolume(Volume* volume)
{
	reset();
	RenderController::volume = volume;
	newVolume = true;
	camera.yaw = 0;
}

void RenderController::run(long double timePassed)
{
	if (renderer && RenderController::volume)
	{
		if (newVolume)
		{
			volumeRenderEntity = new VolumeRenderEntity(RenderController::volume, loader);
			volumeRenderEntity->setTextureID(loader.loadVolume(RenderController::volume));
			MainWindow::m_Ui->sl_xTranslate->setMaximum(200);
			MainWindow::m_Ui->sl_xTranslate->setMinimum(-200);
			MainWindow::m_Ui->sl_xTranslate->setInvertedAppearance(true);
			MainWindow::m_Ui->sl_xTranslate->setValue(0);
			MainWindow::m_Ui->sl_yTranslate->setMaximum(200);
			MainWindow::m_Ui->sl_yTranslate->setMinimum(-200);
			MainWindow::m_Ui->sl_yTranslate->setValue(0);
			newVolume = false;
		}
		camera.position = glm::vec3(MainWindow::m_Ui->sl_xTranslate->value()/100.f, MainWindow::m_Ui->sl_yTranslate->value()/100.f, 0);
		//entity.increaseRotation(0, 0.03, 0);
		camera.yaw = 0.f;
		camera.move(timePassed);
		//logic
		renderer->processVolumeRenderEntity(RenderController::volumeRenderEntity);
		renderer->render(camera);

		DisplayManager::updateDisplay();
	}
}

void RenderController::cleanup()
{
	delete RenderController::volumeRenderEntity;
	renderer->cleanup();
}