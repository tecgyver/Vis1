#pragma once

#include <QImage>
#include <cmath>

#include "Volume.h"
#include "BresenhamRayCaster.h"

class CPURenderer
{
private:
	BresenhamRayCaster* m_raycaster;

	QRgb mip(std::vector<float> samples);
	QRgb alphaCompositing(std::vector<float> samples, float treshold);

	int sampleRate;
	float globalMax;
public:
	CPURenderer();
	~CPURenderer();

	bool mipEnabled;
	bool alphaCompositingEnabled;

	int sampleSize;

	float alphaCompositingTreshold;
	int xTranslate;
	int yTranslate;

	bool xRotateEnabled;
	bool yRotateEnabled;
	int xRotateDeg;
	int yRotateDeg;

	void preprocessData(Volume& data);
	//void sample(Volume& data, int width, int height);
	void sampleAndRender(QImage& target, Volume& data);
	//void render(QImage& target);
};

