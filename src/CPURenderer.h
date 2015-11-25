#pragma once

#include <QImage>

#include "Volume.h"

class CPURenderer
{
public:
	CPURenderer();
	~CPURenderer();

	void render(QImage& target, Volume& data);
};

