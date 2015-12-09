#include "RaycastRenderingWidget.h"
#include "RenderController.h"
#include <ctime>

using namespace engineTester;

RaycastRenderingWidget::RaycastRenderingWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
}


RaycastRenderingWidget::~RaycastRenderingWidget()
{
}

void RaycastRenderingWidget::initializeGL()
{
	glClearColor(0, 1, 0, 1);
	RenderController::init(this);
	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);*/
}

void RaycastRenderingWidget::setVolume(Volume* volume)
{
	m_volume = volume;
	RenderController::setVolume(volume);
}

void RaycastRenderingWidget::paintGL()
{
	long double currentTime = time(0);
	long double timeDiffMs = (m_lastCallTime - currentTime) * 1000;
	m_lastCallTime = currentTime;
	RenderController::run(timeDiffMs);
}

void RaycastRenderingWidget::resizeGL(int w, int h)
{
	// Not supported...
}