#pragma once

#include <QImage>

#include "Volume.h"
#include "BresenhamRayCaster.h"

class CPURenderer
{
private:
	BresenhamRayCaster* m_raycaster;
public:
	CPURenderer();
	~CPURenderer();

	void render(QImage& target, Volume& data);
};

