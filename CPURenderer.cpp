#include "CPURenderer.h"


CPURenderer::CPURenderer()
{
}


CPURenderer::~CPURenderer()
{
}

void CPURenderer::render(QImage& target, Volume& data)
{
	target.fill(Qt::GlobalColor::red);
}