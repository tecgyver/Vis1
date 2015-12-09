#include "CPURenderer.h"


CPURenderer::CPURenderer()
{
	m_raycaster = new BresenhamRayCaster();
	globalMax = 0;
}


CPURenderer::~CPURenderer()
{
}

void CPURenderer::preprocessData(Volume& data)
{
	/*
	for (int z = 0; z < data.depth; z++)
	{
		for (int y = 0; y < data.height; y++) 
		{
			for (int x = 0; x < data.width; x++)
			{
				//data.va
			}
		}
	}
	*/
}

void CPURenderer::sampleAndRender(QImage& target, Volume& data)
{
	int width = target.width();
	int height = target.height();
	float sampleDistance = data.depth() / sampleSize;
	//float sampleDistance = data.width() / sampleRate;
	//float sampleDistance = sqrt(data.width() * data.depth()) / sampleRate;

	/*
	for (float y = 0; y < height / 2.f; y += 0.5f)
	{
		for (float x = 0; x < width / 2.f; x += 0.5f)
		{
			//auto& samples = m_raycaster->cast(QVector3D(x, y, 0), QVector3D(0, 0, sampleDistance), data);
			auto& samples = m_raycaster->cast(QVector3D(x, y, 0), QVector3D(0, 0, sampleDistance), data);

			QRgb color;
			if (mipEnabled) 
				color = mip(samples);
			else if (alphaCompositingEnabled)
				color = alphaCompositing(samples, alphaCompositingTreshold / 100);

			target.setPixel(QPoint(x * 2, y * 2), color);
		}
	} 
	*/

	//int xOffset = width / 2.f - data.width() / 2.f;
	//int yOffset = height / 2.f - data.height() / 2.f;

	QVector2D angle = QVector2D(xRotateDeg, yRotateDeg);
	float factorX = cos(yRotateDeg * 0.0174533); // degrees to radiants
	float factorZ = sin(yRotateDeg * 0.0174533);

	float factorX_Y = cos(xRotateDeg * 0.0174533);
	float factorX_Z = sin(xRotateDeg * 0.0174533);

	int xOffset = (float)(width - data.width()) * ((float)xTranslate / 100.f);
	int yOffset = (float)(height - data.height()) * ((float)yTranslate / 100.f);

	for (float y = 0; y < height; y += 1)
	{
		for (float x = 0; x < width; x += 1)
		{
			//Rotation im Uhrzeigersinn um y-Achse. 
			std::vector<float>& samples = std::vector<float>(0);

			if (yRotateEnabled) {
				if (yRotateDeg < 90)
					samples = m_raycaster->cast(QVector3D((x - xOffset) * factorX, y - yOffset, x * -factorZ), QVector3D(sampleDistance * factorZ, 0, sampleDistance * factorX), data, angle);
				else if (yRotateDeg < 180)
					samples = m_raycaster->cast(QVector3D((x - xOffset) * -factorX, y - yOffset, (x - xOffset) * factorZ), QVector3D(sampleDistance * factorZ, 0, sampleDistance * -factorX), data, angle);
				else if (yRotateDeg < 270)
					samples = m_raycaster->cast(QVector3D((x - xOffset) * -factorX, y - yOffset, x * factorZ + data.depth()), QVector3D(sampleDistance * factorZ, 0, sampleDistance * factorX), data, angle);
				else
					samples = m_raycaster->cast(QVector3D(x * factorX + data.width(), y - yOffset, (x - xOffset) * -factorZ), QVector3D(sampleDistance * factorZ, 0, sampleDistance * factorX), data, angle);
			} 
			else if (xRotateEnabled) //xRotateEnabled
			{
				if (xRotateDeg < 90)
					samples = m_raycaster->cast(QVector3D(x - xOffset, (y - yOffset) * factorX_Y, x * factorX_Z), QVector3D(0, sampleDistance * factorX_Z, sampleDistance * factorX_Y), data, angle);
				else if (xRotateDeg < 180)
					samples = m_raycaster->cast(QVector3D(x - xOffset, y - yOffset, (x - xOffset) * factorZ), QVector3D(0, 0, sampleDistance * -factorX), data, angle);
				else if (xRotateDeg < 270)
					samples = m_raycaster->cast(QVector3D(x - xOffset, y - yOffset, x * factorZ + data.depth()), QVector3D(0, 0, sampleDistance * factorX), data, angle);
				else
					samples = m_raycaster->cast(QVector3D(x - xOffset, y - yOffset, (x - xOffset) * -factorZ), QVector3D(0, 0, sampleDistance * -factorX), data, angle);
			}
			else
			{
				samples = m_raycaster->cast(QVector3D(x - xOffset, y - yOffset, 0), QVector3D(0, 0, sampleDistance), data, QVector2D(0, 0));
			}


			//auto& samples = m_raycaster->cast(QVector3D(x - xOffset, y - yOffset, 0), QVector3D(0, 0, sampleDistance), data);

			QRgb color;
			if (mipEnabled)
				color = mip(samples);
			else if (alphaCompositingEnabled)
				color = alphaCompositing(samples, alphaCompositingTreshold / 100);

			target.setPixel(QPoint(x, y), color);
		}
	}
}

QRgb CPURenderer::mip(std::vector<float> samples)
{
	float max = 0;
	for (auto &sample : samples)
		max = fmax(max, sample);

	return QColor((int)(max * 255), (int)(max * 255), (int)(max * 255)).rgb();
}

QRgb CPURenderer::alphaCompositing(std::vector<float> samples, float treshold)
{
	float sample;
	QColor color;
	QColor colorAccumulated;

	float r = 0;
	float g = 0;
	float b = 0;

	float alpha01 = 0;
	float alpha02 = 0;
	float alpha03 = 0;

	int i = 0;
	while (i < samples.size() && (alpha01 <= 1.0 || alpha02 <= 1.0))
	{
		sample = samples.at(i);

		if (sample > globalMax) 
			globalMax = sample;


		if (sample < treshold)
		{
			alpha01 += sample;
		}
		else 
		{
			alpha02 += sample;
		}

		i++;
	}


	alpha01 = fmin(alpha01, 1.0);
	alpha02 = fmin(alpha02, 1.0);
	alpha03 = fmin(alpha03, 1.0);

	float alphaBG = fmin(1 - alpha01, alpha02);
	
	int red = alpha01 * 255 + alphaBG * 255;
	int green = alpha01 * 255;
	int blue = 0;


	return QColor(red, green, blue).rgb();
}