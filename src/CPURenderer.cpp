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
	for (float y = 0; y < target.height()/2.f; y += 0.5f)
	{
		for (float x = 0; x < target.width()/2.f; x += 0.5f)
		{
			auto& samples = m_raycaster->cast(QVector3D(x, y, 0), QVector3D(0, 0, data.depth()/20.f), data);
			float max = 0;
			for (auto &sample : samples)
			{
				if (sample > max)
					max = sample;
			}
			target.setPixel(QPoint(x*2, y*2), QColor((int)(max * 255), (int)(max * 255), (int)(max * 255)).rgba());
		}
	}
}