#pragma once

#include <qopenglwidget.h>
#include <qwidget.h>
#include "Volume.h"

class RaycastRenderingWidget : public QOpenGLWidget
{
public:
	RaycastRenderingWidget(QWidget *parent = 0);
	~RaycastRenderingWidget();

	void setVolume(Volume* volume);

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	Volume* m_volume;
	long double m_lastCallTime;
};

