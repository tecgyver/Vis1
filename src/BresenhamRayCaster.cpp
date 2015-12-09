#include "BresenhamRayCaster.h"


BresenhamRayCaster::BresenhamRayCaster()
{
}


BresenhamRayCaster::~BresenhamRayCaster()
{
}

std::vector<float> BresenhamRayCaster::cast(QVector3D& location, QVector3D& direction, Volume& data, QVector2D& angle)
{
	std::vector<float> samples;

	float value = 0.0;
	QVector3D current = QVector3D(location);

	//Code to compute angle out of direction vector, now implemented as Parameter of this function, due computational expenses and accuraccy
	/*
	QVector2D xz_dir = QVector2D(direction.x(), direction.z());
	double xz_angle = QVector2D().dotProduct(xz_dir.normalized(), QVector2D(0, 1));
	xz_angle = acos(xz_angle) * 57.2957549;
	*/
	
	int width = data.width();
	int height = data.height();
	int depth = data.depth();

	float factorX = cos(angle.y() * 0.0174533);
	float factorZ = sin(angle.y() * 0.0174533);

	float factorX_Y = cos(angle.x() * 0.0174533);
	float factorX_Z = sin(angle.x() * 0.0174533);

	int steps;
	if (angle.x() > 0 || angle.y() > 0) 
	{
		QVector3D a = QVector3D(data.width() * -factorZ, data.height() * direction.y(), data.depth() * -factorX);
			QVector3D b = QVector3D(location.x() * -factorZ, location.y() * direction.y(), location.z() * -factorX);
		//QVector3D a = QVector3D(data.width() * direction.x(), data.height() * factorX_Z, data.depth() * factorX_Y);
		//QVector3D b = QVector3D(location.x() * direction.x(), location.y() * factorX_Z, location.z() * factorX_Y);
		steps = (a.length() + QVector2D(a - b).length()) / direction.length(); //nicht weit genug gesampelt?
	}
	else
	{
		steps = data.depth() / direction.length();
	}

	int i = 0;
	while (i < steps)
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