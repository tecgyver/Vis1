#pragma once

#include <vector>
#include <qvector3d.h>

#include "Volume.h"

class BresenhamRayCaster
{
public:
	BresenhamRayCaster();
	~BresenhamRayCaster();
	std::vector<float> cast(QVector3D& location, QVector3D& direction, Volume& data); //Parameters: start position, direction
};

