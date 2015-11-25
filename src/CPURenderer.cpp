#include "CPURenderer.h"


CPURenderer::CPURenderer()
{
	m_raycaster = new BresenhamRayCaster();
}


CPURenderer::~CPURenderer()
{
}

void CPURenderer::render(QImage& target, Volume& data)
{
	int width = target.width();
	int height = target.height();
	for (int y = 0; y < target.height(); y++)
	{
		for (int x = 0; x < target.width(); x++)
		{
			auto& samples = m_raycaster->cast(QVector3D(x, 0, y), QVector3D(0, 1, 0), data);
			float max = 0;
			for (auto &sample : samples)
			{
				if (sample > max)
					max = sample;
			}
			target.setPixel(QPoint(x, y), QColor((int)(max * 255), (int)(max * 255), (int)(max * 255)).rgba());
		}
	}
}