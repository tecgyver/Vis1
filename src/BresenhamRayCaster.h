#pragma once

#include <vector>
#include <cmath>
#include <qvector3d.h>
#include <qvector2d.h>

#include "Volume.h"

class BresenhamRayCaster
{
public:
	BresenhamRayCaster();
	~BresenhamRayCaster();
	std::vector<float> cast(QVector3D& location, QVector3D& direction, Volume& data, QVector2D& angle); //Parameters: start position, direction, angle of Rotation
};

