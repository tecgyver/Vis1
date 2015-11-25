#include "BresenhamRayCaster.h"


BresenhamRayCaster::BresenhamRayCaster()
{
}


BresenhamRayCaster::~BresenhamRayCaster()
{
}

std::vector<float> BresenhamRayCaster::cast(QVector3D& location, QVector3D& direction, Volume& data)
{
	std::vector<float> samples;

	float value;
	QVector3D current = QVector3D(location);
	while (current.x() >= 0 && current.x() < data.width() &&
		current.y() >= 0 && current.y() < data.height() &&
		current.z() >= 0 && current.z() < data.depth())
	{
		value = data.voxel((int)current.x(), (int)current.y(), (int)current.z()).getValue();
		samples.push_back(value);
		current += direction;
	}
	return samples;
}