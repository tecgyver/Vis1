#pragma once

#include "Loader.h"
#include "Camera.h"
#include "VolumeRenderEntity.h"
#include "MasterRenderer.h"
#include "Volume.h"

class Ui_MainWindow;
class RaycastRenderingWidget;

namespace engineTester
{
	class RenderController
	{
	public:
		RenderController();
		~RenderController();
		static void init(RaycastRenderingWidget* window);
		static void run(long double timePassed);
		static void reset();
		static void cleanup();
		static void setVolume(Volume* volume);

	private:
		static renderEngine::Loader loader;
		static entities::Camera camera;
		static VolumeRenderEntity* volumeRenderEntity;
		static Volume* volume;
		static renderEngine::MasterRenderer* renderer;
		static bool newVolume;
		static Ui_MainWindow* m_Ui;
	};
}