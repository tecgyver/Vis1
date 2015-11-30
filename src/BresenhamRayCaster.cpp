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

	float value = 0.0;
	QVector3D current = QVector3D(location);

	int width = data.width();
	int height = data.height();
	int depth = data.depth();
	int steps = direction.z() - location.z(); //sample size - offset der bildeben von den daten

	int i = 0;
	while (i < steps)
		//current.x() >= 0 && current.x() < width &&
		//current.y() >= 0 && current.y() < height &&
		//current.z() >= 0 && current.z() < depth)
	{
		if (current.x() < 0 || current.x() >= width ||
			current.y() < 0 || current.y() >= height ||
			current.z() < 0 || current.z() >= depth)
			samples.push_back(0);

		value = data.value((int)current.x(), (int)current.y(), (int)current.z());
		samples.push_back(value);
		current += direction;
		i++;
	}

	return samples;
}