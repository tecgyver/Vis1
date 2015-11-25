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
			auto& samples = m_raycaster->cast(QVector3D(x, y, 0), QVector3D(0, 0, 1), data);
			float max = -1;
			for (auto &sample : samples)
			{
				if (sample > max)
					max = sample;
			}
			target.setPixel(QPoint(x, y), QColor(max * 255, max * 255, max * 255).rgb());
		}
	}
}